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

        if (closed_list.count(current))
          continue; // Node already processed with a better or equal cost

#ifdef UTILS_A_STAR_ENABLE_NAVIGATION
        backtrack_to(find_common_ancestor(c_node, current));
        if (!advance_to(*current))
        { // Conflict detected, backtrack..
#ifdef BUILD_LISTENERS
          inconsistent_node(*current);
#endif
          continue;
        }
#endif

        if (current->is_goal() || (goal && current == goal))
        {
          c_node = current;
#ifdef BUILD_LISTENERS
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
#ifdef BUILD_LISTENERS
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
#ifdef BUILD_LISTENERS
        current_node(*c_node);
#endif
      }
      return true;
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

#ifdef BUILD_LISTENERS
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
