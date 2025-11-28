#include "a_star.hpp"
#include <iostream>
#include <cassert>

class my_node : public utils::node<int>, public std::enable_shared_from_this<my_node>
{
public:
    my_node(std::weak_ptr<my_node> parent, const int &g_cost) noexcept : utils::node<int>(std::move(parent), g_cost) {}
    ~my_node() override = default;

    [[nodiscard]] int h_cost() const noexcept override { return 0; }

    [[nodiscard]] std::vector<std::shared_ptr<utils::node<int>>> generate_successors() override
    {
        std::vector<std::shared_ptr<utils::node<int>>> successors;
        if (g_cost() < 10)
        {
            auto succ = std::make_shared<my_node>(shared_from_this(), g_cost() + 1);
            successors.push_back(succ);
        }
        return successors;
    }

    [[nodiscard]] bool is_goal() const noexcept override { return g_cost() >= 10; }
};

int main()
{
    auto root = std::make_shared<my_node>(std::weak_ptr<my_node>(), 0);
    utils::a_star<int> astar(root);
    auto goal_node = astar.search();
    assert(goal_node);
    assert(goal_node->g_cost() == 10);
    return 0;
}
