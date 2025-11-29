#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

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
    [[nodiscard]] virtual std::vector<std::shared_ptr<node<Tp>>> get_successors() = 0;

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
        auto next = open_list.top();
#ifdef BUILD_NAVIGATION
        backtrack_to(find_common_ancestor(*c_node, *next));
        if (!go_to(*next))
        { // Conflict detected, backtrack..
#ifdef BUILD_LISTENERS
          inconsistent_node(*next);
#endif
          continue;
        }
#else
        c_node = next;
#ifdef BUILD_LISTENERS
        current_node(*c_node);
#endif
#endif
        if (c_node->is_goal())
          return c_node;
        open_list.pop();

        for (auto &succ : c_node->get_successors())
        {
          if (auto closed_it = visited_nodes.find(succ); closed_it != visited_nodes.end())
          {
            if (succ->g_cost() >= closed_it->second)
              continue;                     // Skip already explored with lower cost
            visited_nodes.erase(closed_it); // Remove from closed list for re-exploration
          }

          open_list.push(succ);
        }
        visited_nodes.emplace(c_node, c_node->g_cost());
      }

      return nullptr; // No solution found
    }

  protected:
    const node<Tp> &find_common_ancestor(const node<Tp> &a, const node<Tp> &b) const
    {
      std::unordered_set<const node<Tp> *> ancestors;
      auto c_a = &a;
      while (c_a)
      {
        ancestors.insert(c_a);
        c_a = c_a->get_parent() ? c_a->get_parent().get() : nullptr;
      }
      auto c_b = &b;
      while (c_b)
      {
        if (ancestors.count(c_b))
          return *c_b;
        c_b = c_b->get_parent() ? c_b->get_parent().get() : nullptr;
      }
      throw std::runtime_error("No common ancestor found");
    }

    void backtrack_to(const node<Tp> &n) noexcept
    {
      while (c_node.get() != &n)
      {
        retract(*c_node);
        c_node = c_node->get_parent();
#ifdef BUILD_LISTENERS
        current_node(*c_node);
#endif
      }
    }

    bool go_to(node<Tp> &target) noexcept
    {
      std::vector<node<Tp> *> path;
      auto temp_node = &target;
      while (temp_node != c_node.get())
      {
        path.push_back(temp_node);
        temp_node = temp_node->get_parent().get();
      }
      for (auto it = path.rbegin(); it != path.rend(); ++it)
      {
        if (!apply_transition(**it))
          return false;
        c_node = (*it)->get_parent();
#ifdef BUILD_LISTENERS
        current_node(*c_node);
#endif
      }
      return true;
    }

    [[nodiscard]] node<Tp> &get_current_node() noexcept { return *c_node; }
    [[nodiscard]] const node<Tp> &get_current_node() const noexcept { return *c_node; }

    /**
     * @brief Retrieves all nodes from both the closed list and open list.
     *
     * This method collects all nodes that have been processed (in the closed list)
     * and all nodes that are currently queued for processing (in the open list).
     * The open list is copied to avoid modifying the original priority queue.
     *
     * @return A vector containing shared pointers to all nodes in both lists.
     */
    [[nodiscard]] std::vector<std::shared_ptr<const node<Tp>>> get_all_nodes() const noexcept
    {
      std::vector<std::shared_ptr<const node<Tp>>> nodes;
      for (const auto &n : visited_nodes)
        nodes.push_back(n.first);
      auto temp_open = open_list;
      while (!temp_open.empty())
      {
        nodes.push_back(temp_open.top());
        temp_open.pop();
      }
      return nodes;
    }

  private:
    virtual void retract(const node<Tp> &) noexcept {}
    virtual bool apply_transition(node<Tp> &) noexcept { return true; }

#ifdef BUILD_LISTENERS
    virtual void current_node(const node<Tp> &n) {}
    virtual void inconsistent_node(const node<Tp> &n) {}
#endif

  private:
    std::shared_ptr<node<Tp>> c_node;
    std::priority_queue<std::shared_ptr<node<Tp>>, std::vector<std::shared_ptr<node<Tp>>>, node_cmp> open_list;
    std::unordered_map<std::shared_ptr<const node<Tp>>, Tp> visited_nodes;
  };
} // namespace utils
