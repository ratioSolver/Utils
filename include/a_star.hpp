#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <unordered_set>

namespace utils
{
  template <typename Tp>
  class node
  {
  public:
    node(std::weak_ptr<node<Tp>> parent, const Tp &g_cost) noexcept : parent_node(std::move(parent)), g(g_cost) {}
    virtual ~node() = default;

    /**
     * @brief Returns a unique identifier for the node.
     *
     * This function provides a way to uniquely identify each node instance.
     * The identifier is derived from the memory address of the node object.
     *
     * @return A uintptr_t representing the unique identifier of the node.
     */
    [[nodiscard]] uintptr_t get_id() const noexcept { return reinterpret_cast<uintptr_t>(this); }

    /**
     * @brief Returns a shared pointer to the parent node.
     *
     * This function provides access to the parent node of the current node in the search tree.
     *
     * @return A shared pointer to the parent node, or nullptr if there is no parent.
     */
    [[nodiscard]] std::shared_ptr<node<Tp>> get_parent() const noexcept { return parent_node.lock(); }

    /**
     * @brief Returns the cost from the start node to the current node (g-cost).
     *
     * This function provides access to the g-cost, which represents the cumulative cost
     * incurred from the starting point to the current node in the A* search algorithm.
     *
     * @return The g-cost as a constant reference.
     */
    [[nodiscard]] const Tp &g_cost() const noexcept { return g; }

    /**
     * @brief Calculates the heuristic cost for the current state.
     *
     * This pure virtual function should be implemented by derived classes to provide
     * the heuristic cost estimation used in A* search algorithms. The returned value
     * represents the estimated cost from the current state to the goal.
     *
     * @return The heuristic cost as a Tp value.
     */
    [[nodiscard]] virtual Tp h_cost() const noexcept = 0;

    /**
     * @brief Calculates the total estimated cost (f-cost) for the current node.
     *
     * The f-cost is computed as the sum of the actual cost from the start node (g)
     * and the heuristic estimated cost to the goal (h_cost).
     *
     * @return The total estimated cost (f-cost) as a Tp value.
     */
    [[nodiscard]] Tp f_cost() const noexcept { return g + h_cost(); }

    /**
     * @brief Generates the successor nodes from the current node.
     *
     * This pure virtual function should be implemented to return a list of successor nodes
     * that can be reached from the current node in the search space. Each successor is
     * represented as a shared pointer to a node.
     *
     * @return A vector of shared pointers to the successor nodes.
     */
    [[nodiscard]] virtual std::vector<std::shared_ptr<node<Tp>>> generate_successors() const = 0;

    /**
     * @brief Checks if the current node represents a goal state.
     *
     * This pure virtual function should be implemented to determine whether the current
     * node corresponds to a goal state in the search problem.
     *
     * @return True if the current node is a goal state, false otherwise.
     */
    [[nodiscard]] virtual bool is_goal() const noexcept = 0;

  private:
    std::weak_ptr<node<Tp>> parent_node; // Reference to the parent node
    Tp g;                                // Cost from start to current node
  };

  template <typename Tp>
  class a_star
  {
    struct node_cmp
    {
      bool operator()(const std::shared_ptr<node<Tp>> &a, const std::shared_ptr<node<Tp>> &b) const { return a->f_cost() > b->f_cost(); }
    };

  public:
    a_star(std::shared_ptr<node<Tp>> root) noexcept { open_list.push(root); }
    virtual ~a_star() = default;

    /**
     * @brief Performs the A* search algorithm to find a goal node.
     *
     * This function iteratively explores nodes from the open list, expanding the most promising node
     * (according to the priority queue). For each node, it checks if the goal condition is met.
     * If so, it returns the goal node. Otherwise, it generates successors, adds unexplored ones to
     * the open list, and marks the current node as explored by inserting it into the closed list.
     *
     * @return std::shared_ptr<node<Tp>> Pointer to the goal node if found; nullptr otherwise.
     */
    [[nodiscard]] std::shared_ptr<node<Tp>> search()
    {
      while (!open_list.empty())
      {
        auto c_node = open_list.top();
#ifdef BUILD_LISTENERS
        current_node(*c_node);
#endif
        open_list.pop();

        if (c_node->is_goal())
          return c_node;

        closed_list.insert(c_node);

        for (const auto &successor : c_node->generate_successors())
          if (closed_list.find(successor) != closed_list.end())
            continue;
          else
            open_list.push(successor);
      }

      return nullptr; // No solution found
    }

#ifdef BUILD_LISTENERS
    virtual void current_node(const node<Tp> &c_node) {}
#endif

  private:
    std::priority_queue<std::shared_ptr<node<Tp>>, std::vector<std::shared_ptr<node<Tp>>>, node_cmp> open_list;
    std::unordered_set<std::shared_ptr<const node<Tp>>> closed_list;
  };
} // namespace utils
