#include <iostream>
#include <vector>
#include <string>

#include "Graph.hpp"

/*
 * CPSC 223, Spring 2024
 * Pset 7 : Graphs
 * (c)2024 Alan Weide
 */

using std::string;

using Graph = g::Graph<string, string, unsigned int>;
using Vertex = Graph::Vertex;
using Edge = Graph::Edge;

/**
 * Simple driver for observing the behavior of the Graph class.
 *
 * Reads a graph from standard input, then performs breadth-first search,
 *  depth-first search, Dijkstra's algorithm, and shortest path calculations
 *  for each vertex specified on the command line, printing the results of each
 *  computation.
 *
 * The command-line arguments are a series of nonnegative integers, each of
 *  which is the index of a vertex in the graph.
 *
 * @param argc the number of command-line arguments
 * @param argv the command-line arguments
 */
int main(int argc, char *argv[])
{
    Graph g(std::cin);
    std::cout << g;

    auto vertices = g.vertices();
    for (int i = 1; i < argc; i++)
    {
        Vertex v = vertices[atoi(argv[i])];

        std::cout << std::endl
                  << "------ BEGIN " << v << " ------"
                  << std::endl
                  << std::endl;

        std::cout << "Breadth-first search:" << std::endl;
        g.bfs(v);
        std::cout << std::endl;

        std::cout << "Depth-first search:" << std::endl;
        g.dfs(v);
        std::cout << std::endl;

        std::cout << "Dijkstra's algorithm:" << std::endl;
        g.dijkstra(v);
        std::cout << std::endl;

        std::cout << "Shortest paths:" << std::endl;
        for (auto u : vertices)
        {
            try
            {
                std::cout << g.shortest_path(v, u) << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        std::cout << std::endl
                  << "-------- END " << v << " ------"
                  << std::endl;
    }
}
