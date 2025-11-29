#include "a_star.hpp"
#include <iostream>
#include <cassert>

class my_node : public utils::node<int>
{
private:
    std::unordered_map<std::shared_ptr<utils::node<int>>, int> neighbors;
};

int main()
{
    return 0;
}
