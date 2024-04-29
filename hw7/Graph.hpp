#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <limits>
#include <algorithm>
#include <stdexcept>

#include <vector>
#include <set>
#include <queue>
#include <stack>

#include "traits.hpp"
#include "MinQueue.hpp"

/*
 * CPSC 223 Spring 2024
 * Assignment 7: Graphs
 *
 * Contains the interface and implementation for the Graph class, including
 *  inner structs for Vertex, Edge, and Path.
 *
 * Author: Nate Ly
 */

namespace g
{
    using namespace std;

    /**
     * Type of a graph with vertices of type V and edges with label of type E
     *  and weight of type W. The graph is represented by an adjacency list.
     * To construct a graph, type V and E must be constructible from a string or
     *  overload the input operator>> and W must be an arithmetic type.
     *
     * @tparam V the type of the vertices' labels
     * @tparam E the type of the edges' labels
     * @tparam W the type of the edges' weights
     * @see Vertex the inner struct representing a vertex
     * @see Edge the inner struct representing an edge
     */
    template <typename V = string,
              typename E = string,
              typename W = unsigned int>
    class Graph
    {
    public:
        /**
         * Some useful constants for the graph.
         */
        using size_type = unsigned int;
        static constexpr W W_MAX =
            numeric_limits<W>::max();
        static constexpr W W_MIN =
            numeric_limits<W>::min();
        static constexpr size_type SIZE_MAX =
            numeric_limits<size_type>::max();

        /*
         * Type traits for the template parameters V, E, and W. The following
         *  must hold:
         *  - V and E must be constructible from a string or have an input
         *      operator
         *  - E must be an arithmetic type and have an input operator
         */
        static_assert(is_string_constructible<V>::value ||
                          has_input_operator<V>::value,
                      "V must be constructible from a string or have an input "
                      "operator");
        static_assert(is_string_constructible<E>::value ||
                          has_input_operator<E>::value,
                      "E must be constructible from a string or have an input "
                      "operator");
        static_assert(is_arithmetic<W>::value && has_input_operator<W>::value,
                      "W must be an arithmetic type");

        /**
         * Inner struct representing a vertex in the graph. The vertex has an
         *  index field of type size_type and a label field of type V.
         */
        struct Vertex
        {
            size_type index;
            V label;

            /**
             * Default constructor for a vertex. The index is set to SIZE_MAX
             *  and the label is set to the default value of type V.
             */
            Vertex() : index(SIZE_MAX), label() {}

            /**
             * Constructs a vertex with the given index. The label is set to the
             *  label of the index as a string (which is converted to a V).
             *
             * @param idx the index of the vertex
             */
            Vertex(size_type idx) : Vertex(idx, to_string(idx)) {}

            /**
             * Constructs a vertex with the given index and label. The label is
             *  directly initialized from lbl if possible, otherwise it is read
             *  from a stringstream. (This is conditionally compiled based on
             *  whether V is constructible from a string.)
             *
             * @param idx the index of the vertex
             * @param lbl the label of the vertex
             */
            template <typename T = V,
                      enable_if_t<is_string_constructible<T>::value, int> = 0>
            Vertex(size_type idx, string lbl) : index(idx),
                                                label(lbl) {}
            template <typename T = V,
                      enable_if_t<!is_string_constructible<T>::value, int> = 0>
            Vertex(size_type idx, string lbl) : index(idx), label()
            {
                istringstream iss(lbl);
                iss >> label;
            }

            /**
             * Comparison operator== for a vertex. Two vertices are equal if
             *  their indexes are the same and their labels are the same.
             *
             * Defining this explicitly prevents an implicit conversion to
             *  size_type when comparing vertices for equality, but still
             *  permits the vertex to be used as an index.
             *
             * @param other the other vertex to compare to
             */
            bool operator==(const Vertex &other) const
            {
                return index == other.index && label == other.label;
            }

            /**
             * Comparison operator!= for a vertex. Two vertices are unequal if
             *  their indexes are different or their labels are different.
             *
             * Defining this explicitly prevents an implicit conversion to
             *  size_type when comparing vertices for inequality, but still
             *  permits the vertex to be used as an index.
             *
             * @param other the other vertex to compare to
             */
            bool operator!=(const Vertex &other) const
            {
                return index != other.index || label != other.label;
            }

            /**
             * Implicit conversion to the vertex's index. Permits a vertex to be
             *  used as an index.
             *
             * @return the index of the vertex
             */
            operator size_type() const { return index; }

            /**
             * Overloads the output operator<< for a vertex. The vertex is
             *  printed as its label surrounded by parentheses.
             *
             * @param os the output stream
             * @param vertex the vertex to print
             */
            friend ostream &operator<<(ostream &os, const Vertex &vertex)
            {
                return os << "(" << vertex.label << ")";
            }
        };

        /**
         * Inner struct representing an edge in the graph. The edge has a source
         *  Vertex, a target Vertex, a label of type E, and a weight of type W.
         */
        struct Edge
        {
            Vertex source;
            Vertex target;
            E label;
            W weight;

            /**
             * Default constructor for an edge. The source and target vertices
             *  are set to the default vertex, the label is set to the default
             *  value of type E, and the weight is set to the default value of
             *  type W.
             */
            Edge() = default;

            /**
             * Constructs an edge with the given source, target, label, and
             *  weight. The weight is set to 1 if not given.
             *
             * @param source the source vertex
             * @param target the target vertex
             * @param label the label of the edge
             * @param weight the weight of the edge, defaulting to 1
             */
            Edge(Vertex source, Vertex target, E label, W weight = W(1))
                : source(source),
                  target(target),
                  label(label),
                  weight(weight) {}

            /**
             * Constructs an edge from a string label. The label is directly
             *  initialized from label if possible, otherwise it is read from a
             *  stringstream. (This is conditionally compiled based on whether E
             *  is constructible from a string.)
             *
             * @param source the source vertex
             * @param target the target vertex
             * @param label the label of the edge
             * @param weight the weight of the edge
             */
            template <typename T = E,
                      enable_if_t<is_string_constructible<T>::value, int> = 0>
            Edge(Vertex source,
                 Vertex target,
                 string label,
                 W weight) : source(source),
                             target(target),
                             label(label),
                             weight(weight) {}
            template <typename T = E,
                      enable_if_t<!is_string_constructible<T>::value, int> = 0>
            Edge(Vertex source,
                 Vertex target,
                 string label,
                 W weight) : source(source),
                             target(target),
                             label(),
                             weight(weight)
            {
                istringstream iss(label);
                iss >> label;
            }

            /**
             * Implicit conversion to the weight type of the edge.
             */
            operator W() const { return weight; }

            /**
             * Implicit conversion to a boolean. The edge is true if its weight
             *  is not zero.
             */
            operator bool() const { return weight != W(); }

            /**
             * Overloads the comparison operator< for an edge. The edge is
             *  compared by weight, then label, then source, then target.
             *
             * Defining this explicitly prevents implicit conversion to W when
             *  comparing edges for less-than.
             *
             * @param other the other edge to compare to
             */
            bool operator<(const Edge &other) const
            {
                if (weight != other.weight)
                {
                    return weight < other.weight;
                }
                if (label != other.label)
                {
                    return label < other.label;
                }
                if (source != other.source)
                {
                    return source < other.source;
                }
                return target < other.target;
            }

            /**
             * Overload for operator~ for an edge, which reverses source and
             *  target. The label and weight are preserved.
             */
            Edge operator~() const
            {
                return Edge(target, source, label, weight);
            }

            /**
             * Overloads the output operator<< for an edge. The edge is printed
             *  as (source)---<label>---(target) or (source)    x    (target) if
             *  the edge does not exist.
             *
             * @param os the output stream
             * @param edge the edge to print
             */
            friend ostream &operator<<(ostream &os, const Edge &edge)
            {
                if (!edge)
                {
                    return os << edge.source << "    x    " << edge.target;
                }
                constexpr int EDGE_LENGTH = 9;
                stringstream ss;
                ss << "<" << edge.label << ">";
                string edgeLabel = ss.str();
                int lpad = (EDGE_LENGTH - edgeLabel.size()) / 2;
                int rpad = EDGE_LENGTH - edgeLabel.size() - lpad;
                return os << edge.source
                          << setw(lpad) << setfill('-') << ""
                          << edgeLabel
                          << setw(rpad) << setfill('-') << ""
                          << edge.target;
            }
        };

        /**
         * Inner struct representing a (simple) path in the graph. The path is a
         *  vector of vertices, with the following fields:
         *  - g: the graph from which the path was constructed
         *  - source: the source vertex of the path
         *  - target: the target vertex of the path
         *  - distance: the total weight of the path
         *  - path_exists: a boolean indicating whether the path exists (false
         *      if there is no path between source and target in g)
         */
        struct Path : public vector<Vertex>
        {
            const Graph &g;
            Vertex source;
            Vertex target;
            W distance;
            bool path_exists;

            /**
             * Default constructor for a path. The graph is set to a default,
             *  the source and target vertices are set to the default vertex,
             *  the distance is set to W_MAX, and path_exists is set to false.
             */
            Path() : g(Graph()),
                     source(),
                     target(),
                     distance(W_MAX),
                     path_exists() {}

            /**
             * Constructs the path from the source to the target vertex using
             *  the given parents vector. The path is stored in the vector of
             *  vertices and the distance is calculated by querying edges from
             *  g. If the parent chain from t does not reach s, then path_exists
             *  is set to false. (This is decided by querying t's parent. There
             *  can be no partial chain from t in the parents vector. If there
             *  is such a partial chain, this constructor will throw an error.)
             *
             * @param g the graph
             * @param s the source vertex
             * @param t the target vertex
             * @param parents the vector of parents for each vertex in the path
             */
            Path(const Graph &g,
                 Vertex s,
                 Vertex t,
                 vector<Vertex> &parents) : vector<Vertex>(),
                                            g(g),
                                            source(s),
                                            target(t),
                                            distance(W_MAX),
                                            path_exists(s == t ||
                                                        parents[t] != Vertex())
            {
                if (path_exists)
                {
                    this->distance = W();
                    if (s == t)
                    {
                        this->push_back(t);
                        this->push_back(s);
                    }
                    else
                    {
                        Vertex u = t;
                        while (u != s && u != Vertex())
                        {
                            this->push_back(u);
                            Vertex v = parents[u];
                            this->distance += this->g.edge(v, u).weight;
                            u = v;
                        }
                        if (u != s)
                        {
                            throw runtime_error("Invalid parent chain");
                        }
                        this->push_back(s);
                    }
                    reverse(this->begin(), this->end());
                }
            }

            /**
             * Overloads the output operator<< for a path. path is printed as
             *
             * (s)~~~<d>~~~(t): (s)---<w>---(v1)---<w2>---(v2)--- ... <wt>---(t)
             *
             * Prints "No path found" if there is no
             *  path between source and target.
             *
             * @param os the output stream
             * @param path the path to print
             */
            friend ostream &operator<<(ostream &os, const Path &path)
            {
                if (!path.path_exists)
                {
                    return os << path.source << "    x    " << path.target
                              << ": No path found";
                }

                constexpr int EDGE_LENGTH = 9;
                stringstream ss;
                ss << "<" << path.distance << ">";
                string distanceLabel = ss.str();
                int lpad = (EDGE_LENGTH - distanceLabel.size()) / 2;
                int rpad = EDGE_LENGTH - distanceLabel.size() - lpad;
                os << path.source
                   << setw(lpad) << setfill('~') << ""
                   << distanceLabel
                   << setw(rpad) << setfill('~') << ""
                   << path.target << ": ";

                for (size_type i = 0; i < path.size() - 1; i++)
                {
                    Edge e = path.g.edge(path[i], path[i + 1]);
                    Vertex v = e ? e.source : path.source;
                    stringstream ss;
                    ss << "<" << e.weight << ">";
                    string weightLabel = ss.str();
                    int lpad = (EDGE_LENGTH - weightLabel.size()) / 2;
                    int rpad = EDGE_LENGTH - weightLabel.size() - lpad;
                    os << v
                       << setw(lpad) << setfill('-') << ""
                       << weightLabel
                       << setw(rpad) << setfill('-') << "";
                }
                return os << path.target;
            }
        };

        /**
         * Constructs an empty graph. The graph is directed by default.
         *
         * This constructor is incomplete. YOU MUST COMPLETE IT using either an
         *  initializer list or by initializing the fields in the constructor
         *  body.
         * You must intialize all members of class Graph.
         */
        Graph()
        {
            directed = true;
            vlst;
            alst;
        }

        /**
         * Constructs a graph from the given input stream. If the graph is
         *  undirected, then the edge (s, t, w) implies the edge (t, s, w) as
         *  well.
         *
         * The input stream must be formatted as follows:
         *  - The first line contains the number of vertices in the graph, n
         *      - n is a positive integer less than UINT_MAX
         *  - n is followed by a whitespace and then a single character that
         *      indicates the directedness of the graph:
         *      - 'D' or 'd' (for a directed graph) or
         *      - 'U' or 'u' (for an undirected graph)
         *  - The next nonempty lines contain the labels of the vertices, with
         *      one on each line, in order of their indices
         *      - If there are fewer than n non-empty lines, the remaining
         *          vertices are given default labels (0, 1, 2, ..., n-1)
         *      - Vertex labels should be unique for readability but it is not a
         *          requirement for well-formedness of the input
         *      - If there are more than n non-empty lines, the input is
         *          considered ill-formed
         *  - The vertex label list is followed by at least one empty line
         *  - The rest of the file contains the edges of the graph, each
         *      represented by the following fields, in order, each separated by
         *      whitespace:
         *      - two integers, which are the source index, the target index
         *      - a value of type W, the weight of the edge
         *      - (optionally) a value of type E, the label of the edge
         *          - If there is no label, the edge's label is its weight
         *  - The edges are given in any order, but the following conditions
         *      hold:
         *      - There is one edge per line of input
         *      - No edge will be represented more than once
         *      - If an edge is represented with a weight of 0, the edge is not
         *          added to the graph.
         *      - The weight of each edge is of type W and is strictly between
         *          W_MIN and W_MAX
         *      - Every simple (i.e. noncyclic) path in the graph has total
         *          distance less than W_MAX
         *      - Every simple (i.e. noncyclic) path in the graph has total
         *          distance greater than W_MIN
         *
         * @param input the input stream, which must be correctly formatted
         *
         * @assumes the input stream is in the correct format
         */
        Graph(istream &input)
        {
            input >> *this;
        }

        /**
         * Overloads the input operator>> for a graph. The graph is read from
         *  the input stream as described in the constructor. The graph is made
         *  empty before reading from input.
         *
         * Throws a runtime error if the input is invalid.
         *
         * @param input the input stream
         * @param graph the graph to read into
         *
         * @assumes the input stream is in the correct format
         */
        friend istream &operator>>(istream &input, Graph &graph)
        {
            // Clear the graph
            graph = Graph();

            // Read the graph from input. If we detect invalid input at any
            //  point, throw an error.

            // Read the vertices
            size_type num_vertices;
            input >> num_vertices;
            if (input.fail())
            {
                throw runtime_error("Failed to read number of vertices");
            }
            if (num_vertices <= 0 || num_vertices >= SIZE_MAX)
            {
                throw runtime_error("Invalid number of vertices " +
                                    to_string(num_vertices));
            }

            // Ignore whitespace before the directedness
            input >> std::ws;

            // Read and interpret the directedness
            char direction = toupper(input.get());
            if (direction != 'D' && direction != 'U')
            {
                throw runtime_error(
                    "Invalid input format: unexpected directedness indicator " +
                    direction);
            }
            graph.directed = (direction == 'D');

            // Go to the next line
            input.ignore(numeric_limits<streamsize>::max(), '\n');

            // Read vertex labels up to an empty line. If we read n vertices and
            //  the next line is not empty, throw an error.
            string line;
            getline(input, line);
            while (graph.vertices().size() < num_vertices && !line.empty())
            {
                graph.add_vertex(Vertex(0, line));
                getline(input, line);
            }
            if (!line.empty())
            {
                throw runtime_error("Invalid input format: too many vertex "
                                    "labels (expected " +
                                    to_string(num_vertices) + ")");
            }

            // Fill in any remaining vertices with default label (each vertex's
            //  index)
            while (graph.vertices().size() < num_vertices)
            {
                graph.add_vertex(Vertex(graph.vertices().size()));
            }

            // Read the edges
            size_type s, t;
            while (input >> s >> t)
            {
                Vertex source = graph.vertices()[s];
                Vertex target = graph.vertices()[t];

                // ignore whitespace before the weight
                input >> std::ws;

                // Get the rest of the line so we can "backtrack" if there is no
                //  edge label
                string line;
                getline(input, line);
                istringstream wstream(line);

                // Get the weight
                W weight;
                wstream >> weight;
                if (wstream.fail())
                {
                    throw runtime_error("Failed to read edge weight");
                }
                if (weight == W_MIN || weight == W_MAX)
                {
                    stringstream ss;
                    ss << "Edge weight " << weight << " is out of bounds";
                    throw runtime_error(ss.str());
                }

                // If there is a label on this line, read it. Otherwise, the
                //  label is the weight.
                string label;
                if (wstream >> std::ws)
                {
                    getline(wstream, label);
                }
                else
                {
                    label = line;
                }

                graph.add_edge(Edge(source, target, label, weight));
            }

            // If we failed to read an edge, throw an error
            if (input.fail() && !input.eof())
            {
                throw runtime_error("Failed to read edges");
            }
            return input;
        }

        /**
         * Overloads the output operator<< for a graph. The graph is printed as
         *  a list of vertices followed by a list of edges. Vertices are printed
         *  in order of their indices, but there is no order defined among the
         *  edges.
         *
         * @param os the output stream
         * @param graph the graph to print
         */
        friend ostream &operator<<(ostream &os, const Graph &graph)
        {
            os << "The graph is "
               << (graph.directed ? "DIRECTED" : "UNDIRECTED")
               << endl;
            auto vertices = graph.vertices();
            os << "Vertices (" << vertices.size() << "):" << endl;
            for (Vertex v : vertices)
            {
                os << v << ' ';
            }
            os << endl;

            auto edges = graph.edges();
            os << "Edges (" << edges.size() << "):" << endl;
            for (Edge e : edges)
            {
                os << e << endl;
            }
            return os;
        }

        /**
         * Reports whether this graph is directed.
         */
        bool is_directed() const { return this->directed; }

        /**
         * Returns a vector of all vertices in the graph, in increasing order of
         *  their indices.
         */
        vector<Vertex> vertices() const
        {
            return vlst;
        }

        /**
         * Returns a set of all edges in the graph. If this is undirected, then
         *  both (s, t, w) and (t, s, w) are included.
         */
        set<Edge> edges() const
        {
            set<Edge> edges;
            //edges stored in alst so iterating through and insert 
            for (size_type i = 0; i < alst.size(); i++)
            {
                for (size_type j = 0; j < alst[i].size(); j++)
                {
                    edges.insert(alst[i][j]);
                }
            }
            return edges;
        }

        /**
         * Returns a vector of all neighbors of the given vertex. The indexes of
         *  the vertices in the returned vector are in increasing order.
         *
         * @param v the vertex
         */
        vector<Vertex> neighbors_of(const Vertex &v) const
        {
            vector<Vertex> neighbors;
            //add all edges with starting at v
            for (size_type i = 0; i < alst[v].size(); i++)
            {
                neighbors.push_back(alst[v][i].target);
            }
            // sort the whole list
            sort(neighbors.begin(), neighbors.end());
            return neighbors;
        }

        /**
         * Returns the edge from vertex s to vertex t. If there is no edge from
         *  s to t, the returned edge is equal to Edge().
         *
         * @param s the source vertex
         * @param t the target vertex
         */
        Edge edge(const Vertex &s, const Vertex &t) const
        {
            //going through edges that start at s
            for (size_type i = 0; i < alst[s].size(); i++)
            {
                Edge e = alst[s][i];
                //if there exists the target vertex then we have found the edge
                if (e.target == t)
                {
                    return e;
                }
            }
            //else return default
            return Edge();
        }

        /**
         * Performs a breadth-first search starting from the given vertex. The
         *  function visits each vertex in the graph at most once (it visits
         *  exactly those that are reachable from the starting vertex).
         *
         * Whenever there are two or more vertices to visit, the function visits
         *  them in increasing order of their indices.
         *
         * @param s the starting vertex
         */
        void bfs(const Vertex &s) const
        // referenced code on canvas
        {
            vector<bool> visited(vlst.size());
            vector<Vertex> neighborslst;
            queue<Vertex> q;
            Vertex current;
            Vertex neighbor;
            // visit starting vertex and put in q
            visit(s);
            visited[s] = true;
            q.push(s);
            // go untill q empty
            while (q.empty() == false)
            {
                current = q.front();
                q.pop();
                // get neighbors of first in q
                neighborslst = neighbors_of(current);
                for (size_type i = 0; i < neighborslst.size(); i++)
                {
                    neighbor = neighborslst[i];
                    // if neighbor not already visited visit and add to q
                    if (visited[neighbor] == false)
                    {
                        visit(neighbor);
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }

        /**
         * Performs a depth-first search starting from the given vertex. The
         *  function visits each vertex in the graph at most once (it visits
         *  exactly those that are reachable from the starting vertex).
         *
         * Whenever there are two or more vertices to visit, the function visits
         *  them in increasing order of their indices.
         *
         * @param s the starting vertex
         */
        void dfs(const Vertex &s) const
        {
            vector<bool> visited(vlst.size());
            dfs_recursive(s, visited);
        }

        /**
         * Performs Dijkstra's algorithm starting from the given vertex. The
         *  function visits each vertex in the graph at most once (it visits
         *  exactly those that are reachable from the starting vertex).
         *
         * Whenever there are two or more vertices to visit with the same
         *  distance, the function visits them in increasing order of their
         *  indices.
         *
         * @param s the starting vertex
         *
         * @assumes the graph has no negative edge weights
         */
        void dijkstra(const Vertex &s) const
        {
            MinQueue<W, Vertex> q;
            vector<bool> visited(vlst.size());
            vector<W> weightlst(vlst.size(), W_MAX);
            vector<Vertex> neighborslst;
            W weight;
            //set start to 0
            weightlst[s.index] = 0;
            q.insert(0, s);
            while (q.empty() == false)
            {
                // smallest weight vertex
                Vertex current = q.remove_min();
                if (visited[current.index])
                {
                    continue;
                }
                visit(current);
                visited[current.index] = true;
                neighborslst = neighbors_of(current);
                for (size_type i = 0; i < neighborslst.size(); i++)
                {
                    Vertex neighbor = neighborslst[i];
                    if (visited[neighbor])
                    {
                        continue;
                    }
                    // make sure we aren't overflowing
                    if (weightlst[current.index] == W_MAX)
                    {
                        weight = W_MAX;
                    }
                    else
                    {
                        weight = weightlst[current.index] + edge(current, neighbor).weight;
                    }
                    if (weightlst[neighbor] > weight)
                    {
                        // replace if found a shorter path
                        weightlst[neighbor] = weight;
                    }
                    q.insert(weight, neighbor);
                }
            }
        }

        /**
         * Finds and returns the shortest path between the given vertices (or a
         *  nonexistent path if there is no path from s to t, that is, a path p
         *  such that p.path_exists is false).
         *
         * If there is a negative-weight cycle in the graph, throws a runtime
         *  error.
         *
         * Whenever there are two or more vertices to visit with the same
         *  distance, the function visits them in increasing order of their
         *  indices.
         *
         * @param s the starting vertex
         * @param t the target vertex
         */
        Path shortest_path(const Vertex &s, const Vertex &t) const
        {
            //refrenced from Bellman-Ford pseudocode on canvas
            vector<Vertex> parents(vertices().size());
            vector<W> weightlst(vlst.size(), W_MAX);
            vector<Vertex> neighborlst;
            weightlst[s.index] = 0;
            parents[s.index] = s;
            W weight;
            vector<Vertex> neighborslst;
            for (size_type i = 0; i < vlst.size() - 1; i++)
            {
                //go through vertices
                for (size_type j = 0; j < vlst.size(); j++)
                {
                    Vertex current = vlst[j];
                    if (weightlst[j] != W_MAX)
                    {
                        neighborlst = neighbors_of(current);
                        //go through edges and relax
                        for (size_type k = 0; k < neighborlst.size(); k++)
                        {
                            Vertex neighbor = neighborlst[k];
                            if (weightlst[current.index] == W_MAX)
                            {
                                weight = W_MAX;
                            }
                            else
                            {
                                weight = weightlst[current.index] + edge(current, neighbor).weight;
                            }
                            if (weightlst[neighbor.index] > weight)
                            {
                                // replace if found a shorter path
                                weightlst[neighbor.index] = weight;
                                parents[neighbor.index] = current;
                                break;
                            }
                        }
                    }
                }
            }
            //negative weight cycle
            set<Edge> edgelst = edges();
            for (Edge e : edgelst)
            {
                if (weightlst[e.source] == W_MAX)
                {
                    weight = W_MAX;
                }
                else
                {
                    weight = weightlst[e.source] + e.weight;
                }
                // if wehave an improved weight after traversing V vertices
                //then we have completed a cycle of negative weight
                if (weightlst[e.target] > weight)
                {
                    throw runtime_error("Negative weight cycle");
                }
            }
            return Path(*this, s, t, parents);
        }

        /**
         * Adds a vertex to the graph at the next available index. Before
         *  insertion, the vertex's index is set to the current number of
         *  vertices in the graph.
         *
         * @param v the new vertex
         */
        void add_vertex(Vertex v)
        {
            // Set the vertex's index
            v.index = this->vertices().size();

            // Do the insertion
            vlst.push_back(v);
            alst.push_back(vector<Edge>());
        }

        /**
         * Adds an edge to the graph. If the edge already exists, it is
         *  replaced.
         *
         * If this is undirected, add the given edge and its reverse.
         * If weight == zero, do nothing.
         *
         * @param e the edge
         *
         * @assumes the source and target vertices are in the graph
         */
        void add_edge(Edge e)
        {
            // Validate assumptions. If any of these fail, throw an error.
            if (e.source < 0 || e.source >= this->vertices().size())
            {
                throw runtime_error("Invalid source vertex index " +
                                    to_string(e.source.index));
            }
            if (e.target < 0 || e.target >= this->vertices().size())
            {
                throw runtime_error("Invalid target vertex index " +
                                    to_string(e.target.index));
            }
            if (this->vertices()[e.source] != e.source)
            {
                stringstream ss;
                ss << "Invalid source vertex " << e.source;
                throw runtime_error(ss.str());
            }
            if (this->vertices()[e.target] != e.target)
            {
                stringstream ss;
                ss << "Invalid target vertex " << e.target;
                throw runtime_error(ss.str());
            }

            // Do the edge insertion
            if (e.weight == 0)
            {
                return;
            }

            for (size_type i = 0; i < alst[e.source].size(); i++)
            {
                // replace edge if exists
                if (alst[e.source][i].target == e.target)
                {
                    alst[e.source][i].weight = e.weight;
                    alst[e.source][i].label = e.label;
                    return;
                }
            }
            // else add it to alist
            alst[e.source].push_back(e);
            if (!directed)
            // repeat in other way if undirected
            {
                Edge e2 = ~e;

                for (size_type i = 0; i < alst[e2.source].size(); i++)
                {
                    // replace edge if exists
                    if (alst[e2.source][i].target == e2.target)
                    {
                        alst[e2.source][i].weight = e2.weight;
                        alst[e2.source][i].label = e2.label;
                        return;
                    }
                }
                alst[e.target].push_back(e2);
            }
        }

    private:
        /*
         * Tracks whether the graph is directed. You should not change this
         *  member variable's name or type.
         */
        bool directed;
        vector<Vertex> vlst;
        vector<vector<Edge>> alst;

        /**
         * "Visits" the given vertex. By default, prints the vertex to cout.
         *
         * @param vertex the vertex to visit
         */
        void visit(Vertex vertex) const
        {
            cout << vertex << endl;
        }
        /**
         * Recursive helper for dfs
         * Refrenced from implementation on canvas
         * @param current current vertex
         * @param visited the list of visited vertices
         */
        vector<bool> dfs_recursive(const Vertex &current, vector<bool> &visited) const
        {
            visit(current);
            visited[current] = true;
            // get list of neighbors
            vector<Vertex> neighborslst = neighbors_of(current);
            for (size_type i = 0; i < neighborslst.size(); i++)
            {
                Vertex neighbor = neighborslst[i];
                // if not already visited then recurse on neighbor
                if (visited[neighbor] == false)
                {
                    visited = dfs_recursive(neighbor, visited);
                }
            }
            return visited;
        }
    };
}