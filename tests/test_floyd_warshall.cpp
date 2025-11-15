#include "floyd_warshall.hpp"
#include <iostream>

int main()
{
    utils::floyd_warshall<double, 4> fw;
    fw.add_edge(0, 1, 5.0);
    fw.add_edge(1, 2, 3.0);
    fw.add_edge(2, 3, 1.0);
    fw.add_edge(0, 3, 10.0);

    fw.compute_all_pairs_shortest_paths();

    std::cout << fw << std::endl;

    return 0;
}
