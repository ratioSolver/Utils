#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace utils
{
  template <typename Tp>
  class node
  {
  public:
    virtual ~node() = default;

    /**
     * Computes and returns the cost metric for this node (or path), optionally
     * relative to a specified goal node.
     *
     * @tparam Tp Numeric type used for the cost value.
     * @param goal Optional pointer to the goal node; if nullptr, the implementation
     *             may compute an intrinsic or heuristic cost independent of a goal.
     * @return The computed cost as a value of type Tp.
     */
    [[nodiscard]] virtual Tp cost(std::shared_ptr<node<Tp>> goal = nullptr) const noexcept = 0;
    /**
     * Returns the successor nodes of the current node along with their associated transition costs.
     *
     * This method must be implemented by derived classes to expose the adjacency information needed
     * by A* (or similar graph search algorithms). Each entry in the returned map represents a directed
     * edge from the current node to a successor:
     *  - key: a shared pointer to the successor node
     *  - value: the cost (edge weight) to move from the current node to that successor
     *
     * Requirements and notes:
     *  - The returned container should include all valid successors reachable in one step.
     *  - Costs should be finite and represent non-negative traversal weights if the search algorithm
     *    assumes monotonicity; negative weights are typically unsupported by A*.
     *  - Use of shared_ptr implies shared ownership of node instances across the graph; implementations
     *    should ensure consistent identity and lifetime management of nodes.
     *
     * @return A map where each key is a shared pointer to a successor node and the corresponding value is the cost to reach that node.
     */
    [[nodiscard]] virtual std::unordered_map<std::shared_ptr<node<Tp>>, Tp> get_successors() = 0;
    /**
     * Checks whether the current search node/state satisfies the goal condition.
     *
     * This method is invoked by the A* search to determine if the algorithm
     * should terminate with the current node as the solution. Implementations
     * must provide the specific goal criterion for the problem domain.
     *
     * @return true if the current node represents a goal state; false otherwise.
     */
    [[nodiscard]] virtual bool is_goal() const noexcept = 0;
  };

  template <typename Tp>
  class a_star
  {
    struct pq_elem
    {
      std::shared_ptr<node<Tp>> n;
      Tp f_cost;

      bool operator>(const pq_elem &other) const noexcept { return f_cost > other.f_cost; }
    };

  public:
    a_star(std::shared_ptr<node<Tp>> root) noexcept
    {
      c_node = root;
      open_list.push({root, root->cost()});
      came_from[root] = nullptr;
      g_score[root] = 0;
    }
    virtual ~a_star() = default;

    [[nodiscard]] std::shared_ptr<node<Tp>> search(std::shared_ptr<node<Tp>> goal = nullptr) noexcept
    {
      while (!open_list.empty())
      {
        auto current = open_list.top().n;
        open_list.pop();

        if (closed_list.count(current))
          continue; // Node already processed with a better or equal cost

#ifdef UTILS_A_STAR_ENABLE_NAVIGATION
        backtrack_to(find_common_ancestor(c_node, current));
        if (!advance_to(*current))
        { // Conflict detected, backtrack..
#ifdef UTILS_A_STAR_ENABLE_LISTENERS
          inconsistent_node(*current);
#endif
          continue;
        }
#endif

        if (current->is_goal() || (goal && current == goal))
        {
          c_node = current;
#ifdef UTILS_A_STAR_ENABLE_LISTENERS
          current_node(*c_node);
#endif
          return current;
        }

        closed_list.insert(current);

        for (const auto &[neighbor, cost] : current->get_successors())
        {
          if (closed_list.count(neighbor))
            continue; // Skip neighbors that are already evaluated

          Tp tentative_g_score = g_score.at(current) + cost;

          if (!g_score.count(neighbor) || tentative_g_score < g_score.at(neighbor))
          {
            came_from[neighbor] = current;
            g_score[neighbor] = tentative_g_score;
            Tp f_cost = tentative_g_score + neighbor->cost(goal);
            open_list.push({neighbor, f_cost});
          }
        }
      }
      return nullptr; // No path found
    }

  protected:
    std::shared_ptr<node<Tp>> find_common_ancestor(std::shared_ptr<node<Tp>> a, std::shared_ptr<node<Tp>> b) const
    {
      std::unordered_set<std::shared_ptr<node<Tp>>> ancestors;
      while (a)
      {
        ancestors.insert(a);
        a = came_from.at(a);
      }
      while (b)
      {
        if (ancestors.count(b))
          return b;
        b = came_from.at(b);
      }
      return nullptr;
    }

    void backtrack_to(std::shared_ptr<node<Tp>> n) noexcept
    {
      while (c_node != n)
      {
        retract(*c_node);
        c_node = came_from.at(c_node);
#ifdef UTILS_A_STAR_ENABLE_LISTENERS
        current_node(*c_node);
#endif
      }
    }

    bool advance_to(const node<Tp> &target) noexcept
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
        if (!expand(**it))
          return false;
        c_node = (*it)->get_parent();
#ifdef UTILS_A_STAR_ENABLE_LISTENERS
        current_node(*c_node);
#endif
      }
      return true;
    }

    [[nodiscard]] std::vector<std::shared_ptr<node<Tp>>> get_path() const noexcept
    {
      std::vector<std::shared_ptr<node<Tp>>> path;
      auto current = c_node;
      while (current)
      {
        path.push_back(current);
        auto it = came_from.find(current);
        if (it == came_from.end() || it->second == nullptr)
          break;
        current = it->second;
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    [[nodiscard]] node<Tp> &get_current_node() noexcept { return *c_node; }
    [[nodiscard]] const node<Tp> &get_current_node() const noexcept { return *c_node; }

    [[nodiscard]] std::vector<std::shared_ptr<const node<Tp>>> get_all_nodes() const noexcept
    {
      std::vector<std::shared_ptr<const node<Tp>>> nodes;
      for (const auto &n : closed_list)
        nodes.push_back(n);
      auto temp_open = open_list;
      while (!temp_open.empty())
      {
        nodes.push_back(temp_open.top().n);
        temp_open.pop();
      }
      return nodes;
    }

  private:
    virtual void retract(const node<Tp> &) noexcept {}
    virtual bool expand(node<Tp> &) noexcept { return true; }

#ifdef UTILS_A_STAR_ENABLE_LISTENERS
    virtual void current_node(const node<Tp> &) {}
    virtual void inconsistent_node(const node<Tp> &) {}
#endif

  private:
    std::shared_ptr<node<Tp>> c_node;                                                         // Current node being processed
    std::priority_queue<pq_elem, std::vector<pq_elem>, std::greater<>> open_list;             // Priority queue of nodes to explore
    std::unordered_map<std::shared_ptr<const node<Tp>>, std::shared_ptr<node<Tp>>> came_from; // Best path to each node
    std::unordered_map<std::shared_ptr<const node<Tp>>, Tp> g_score;                          // Cost from start to each node
    std::unordered_set<std::shared_ptr<const node<Tp>>> closed_list;                          // Set of nodes already evaluated
  };
} // namespace utils
