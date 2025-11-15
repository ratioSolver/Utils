#pragma once

#include <array>
#include <limits>
#include <ostream>

namespace utils
{
  /**
   * @brief A class to compute the shortest paths between all pairs of nodes in a graph.
   *
   * This class implements the Floyd-Warshall algorithm to compute the shortest paths
   * between all pairs of nodes in a weighted graph. The algorithm runs in O(T^3)
   * time complexity, where T is the number of nodes in the graph.
   *
   * @tparam Tp The type of the weights of the edges in the graph.
   * @tparam T The number of nodes in the graph.
   */
  template <typename Tp, std::size_t T>
  class floyd_warshall
  {
  public:
    floyd_warshall()
    {
      for (std::size_t i = 0; i < T; i++)
        for (std::size_t j = 0; j < T; j++)
          dist[i][j] = i == j ? 0 : std::numeric_limits<Tp>::infinity();
    }

    /**
     * @brief Adds an edge to the graph with a specified weight.
     *
     * This function updates the distance matrix to reflect the addition of an edge
     * from vertex `u` to vertex `v` with weight `w`.
     *
     * @param u The starting vertex of the edge.
     * @param v The ending vertex of the edge.
     * @param w The weight of the edge.
     */
    void add_edge(std::size_t u, std::size_t v, Tp w) { dist[u][v] = w; }

    /**
     * @brief Computes the shortest paths between all pairs of nodes in a graph.
     *
     * This function implements the Floyd-Warshall algorithm to find the shortest
     * paths between all pairs of nodes in a weighted graph. It updates the
     * distance matrix `dist` such that `dist[i][j]` contains the shortest
     * distance from node `i` to node `j`.
     *
     * The algorithm runs in O(T^3) time complexity, where T is the number of nodes
     * in the graph.
     *
     * @note The distance matrix `dist` should be initialized with the direct
     * distances between nodes, where `dist[i][j]` is the direct distance from
     * node `i` to node `j`. If there is no direct edge between nodes `i` and `j`,
     * `dist[i][j]` should be set to a large value (representing infinity).
     */
    void compute_all_pairs_shortest_paths()
    {
      for (std::size_t k = 0; k < T; k++)
        for (std::size_t i = 0; i < T; i++)
          for (std::size_t j = 0; j < T; j++)
            if (dist[i][k] + dist[k][j] < dist[i][j])
              dist[i][j] = dist[i][k] + dist[k][j];
    }

    /**
     * @brief Retrieves the distance between two nodes in the graph.
     *
     * @param u The index of the starting node.
     * @param v The index of the ending node.
     * @return Tp The distance between node u and node v.
     */
    Tp get_distance(std::size_t u, std::size_t v) const { return dist[u][v]; }

    friend std::ostream &operator<<(std::ostream &stream, const floyd_warshall &fw)
    {
      for (std::size_t i = 0; i < T; i++)
      {
        for (std::size_t j = 0; j < T; j++)
          if (fw.dist[i][j] == std::numeric_limits<Tp>::infinity())
            stream << "inf ";
          else
            stream << fw.dist[i][j] << " ";
        stream << std::endl;
      }
      return stream;
    }

  private:
    std::array<std::array<Tp, T>, T> dist;
  };
} // namespace utils
