#include "a_star.hpp"

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class test_node final : public utils::node<int>
{
public:
    test_node(std::string name, bool goal = false, int heuristic = 0) : id(std::move(name)), goal(goal), heuristic(heuristic) {}

    void add_neighbor(const std::shared_ptr<test_node> &neighbor, int cost) { neighbors.emplace_back(neighbor, cost); }

    [[nodiscard]] int cost(std::shared_ptr<utils::node<int>> = nullptr) const noexcept override { return heuristic; }
    [[nodiscard]] std::unordered_map<std::shared_ptr<utils::node<int>>, int> get_successors() override
    {
        std::unordered_map<std::shared_ptr<utils::node<int>>, int> successors;
        successors.reserve(neighbors.size());

        for (auto it = neighbors.begin(); it != neighbors.end();)
            if (auto locked = it->first.lock())
            {
                successors.emplace(std::move(locked), it->second);
                ++it;
            }
            else
                it = neighbors.erase(it); // Drop edges to expired nodes.

        return successors;
    }
    [[nodiscard]] bool is_goal() const noexcept override { return goal; }

private:
    std::string id;
    bool goal;
    int heuristic;
    std::vector<std::pair<std::weak_ptr<utils::node<int>>, int>> neighbors;
};

void test_finds_goal_with_shortest_path()
{
    auto start = std::make_shared<test_node>("start", false, 4);
    auto branch_one = std::make_shared<test_node>("branch_one", false, 2);
    auto branch_two = std::make_shared<test_node>("branch_two", false, 1);
    auto goal = std::make_shared<test_node>("goal", true, 0);

    start->add_neighbor(branch_one, 2);
    start->add_neighbor(branch_two, 5);
    branch_one->add_neighbor(goal, 1);
    branch_two->add_neighbor(goal, 10);

    utils::a_star<int> solver(start);
    auto result = solver.search(goal);

    assert(result == goal);
}

void test_returns_null_when_unreachable()
{
    auto start = std::make_shared<test_node>("start", false, 1);
    auto dead_end = std::make_shared<test_node>("dead_end", false, 0);
    auto goal = std::make_shared<test_node>("goal", true, 0);

    start->add_neighbor(dead_end, 1);

    utils::a_star<int> solver(start);
    auto result = solver.search(goal);

    assert(result == nullptr);
}

void test_handles_cycles_without_infinite_loop()
{
    auto start = std::make_shared<test_node>("start", false, 3);
    auto cycle_a = std::make_shared<test_node>("cycle_a", false, 2);
    auto cycle_b = std::make_shared<test_node>("cycle_b", false, 1);
    auto goal = std::make_shared<test_node>("goal", true, 0);

    start->add_neighbor(cycle_a, 1);
    cycle_a->add_neighbor(cycle_b, 1);
    cycle_b->add_neighbor(cycle_a, 1); // Forms the cycle
    cycle_b->add_neighbor(goal, 1);

    utils::a_star<int> solver(start);
    auto result = solver.search(goal);

    assert(result == goal);
}

int main()
{
    test_finds_goal_with_shortest_path();
    test_returns_null_when_unreachable();
    test_handles_cycles_without_infinite_loop();

    return 0;
}
