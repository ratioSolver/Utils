#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace utils
{
  template <typename Tp>
  class node
  {
  public:
    [[nodiscard]] virtual Tp cost(std::shared_ptr<node<Tp>> goal = nullptr) const noexcept = 0;
    [[nodiscard]] virtual std::unordered_map<std::shared_ptr<node<Tp>>, Tp> get_successors() = 0;
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

    [[nodiscard]] std::shared_ptr<node<Tp>> search(std::shared_ptr<node<Tp>> goal = nullptr) noexcept
    {
      while (!open_list.empty())
      {
        auto current = open_list.top().n;
        open_list.pop();

        if (closed_list.contains(current))
          continue; // Node already processed with a better or equal cost

        if (current->is_goal() || (goal && current == goal))
        {
          c_node = current;
          return current;
        }

        closed_list.insert(current);

        for (const auto &[neighbor, cost] : current->get_successors())
        {
          if (closed_list.contains(neighbor))
            continue; // Skip neighbors that are already evaluated

          Tp tentative_g_score = g_score.at(current) + cost;

          if (!g_score.contains(neighbor) || tentative_g_score < g_score.at(neighbor))
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

  private:
    std::shared_ptr<node<Tp>> c_node;                                                         // Current node being processed
    std::priority_queue<pq_elem, std::vector<pq_elem>, std::greater<>> open_list;             // Priority queue of nodes to explore
    std::unordered_map<std::shared_ptr<const node<Tp>>, std::shared_ptr<node<Tp>>> came_from; // Best path to each node
    std::unordered_map<std::shared_ptr<const node<Tp>>, Tp> g_score;                          // Cost from start to each node
    std::unordered_set<std::shared_ptr<const node<Tp>>> closed_list;                          // Set of nodes already evaluated
  };
} // namespace utils
