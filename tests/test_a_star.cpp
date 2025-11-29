#include "a_star.hpp"

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

class test_node final : public utils::node<int>
{
public:
    test_node(std::string name, bool goal = false, int heuristic = 0) : id(std::move(name)), goal(goal), heuristic(heuristic) {}

    void add_neighbor(const std::shared_ptr<test_node> &neighbor, int cost) { neighbors[neighbor] = cost; }

    [[nodiscard]] int cost(std::shared_ptr<utils::node<int>> = nullptr) const noexcept override { return heuristic; }
    [[nodiscard]] std::unordered_map<std::shared_ptr<utils::node<int>>, int> get_successors() override { return neighbors; }
    [[nodiscard]] bool is_goal() const noexcept override { return goal; }

private:
    std::string id;
    bool goal;
    int heuristic;
    std::unordered_map<std::shared_ptr<utils::node<int>>, int> neighbors;
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

int main()
{
    test_finds_goal_with_shortest_path();
    test_returns_null_when_unreachable();

    return 0;
}
