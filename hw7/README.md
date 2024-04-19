# PSET 7: Graphs
### CPSC 223, Spring 2024
### Alan Weide & Ozan Erat
### Due: Friday Apr 26 at 11:59 PM NHT

## Introduction

In this assignment, you will implement a `Graph` interface similar to the one we have explored in class, except you are tasked with implementing it using an **adjacency list** rather than the adjacency matrix we have demonstrated in lectures.
The other major difference is that vertices and edges in *this* graph can have arbitrary labels and weights!

This assignment is one of the "Small Psets" of the semester (as opposed to the "Big Psets" such as Hookbook, Blotto, and Trees).
In other words, it is designed to take you approximately **one week** to complete (8-10 hours).

### Academic Honesty

As a reminder, you are restricted in the external resources you are permitted to use on assignments in this course.

* Other than the linked websites in this document and the course syllabus, the internet is not permitted as a resource
* Collaboration with classmates at the source code level is prohibited, though *conceptual* discussions are permitted and even encouraged!
* Generative AI is not permitted as a tool for completing assignments in this course.
    Such tools include but are not limited to ChatGPT, Microsoft CoPilot, and Google Gemini.

Every submission is assessed for similarity with:

* Other submissions to this assignmnent from your classmates
* Past submissions to this assignment, here and at other institutions with similar assignments
* The staff solution to this assignment
* Solutions to this assignment that are available on the internet
* Solutions to this assignment that were created by AI tools

Submissions with high similarity to any of these are flagged and may be referred to the Excecutive Committee.

## Starter Code

### `Graph.hpp`

The `Graph` class is a three-argument template class that contains a variety of inner classes (which themselves are templates), each of which is nontrivial.
Implementing the graph will provide realistic experience in writing code for a reusable, object-oriented software component.
You should start this assignment by reading the comments for the provided scaffolding and understanding how `Vertex`, `Edge`, and `Path` work.
Next, examine the input `operator>>` overload and `istream` constructor for `Graph` to help you concretize the input format.
Then&mdash;and only then!&mdash;should you begin writing code.

For this assignment, you are given an interface in `Graph.hpp` that you must implement.
Since `Graph` is a template class, you must implement each function in the header file (this is why we have modified the file extension to be `.hpp` rather than `.h`).
The tasks you are required to complete are identified by `TODO` messages in the same manner as the previous assignment.
There are **12** required tasks and one optional one:

1. Add private member variables to the `Graph` class that model the graph as an **adjacency list**.
2. Complete the default constructor for `Graph`, which must initialize every private member of `Graph`.
3. Implement the function `vector<Vertex> vertices()`
4. Implement the function `set<Edge> edges()`
5. Implement the function `vector<Vertex> neighbors_of(const Vertex &v)`
6. Implement the function `Edge edge(const Vertex &v, const Vertex &v)`
7. Implement the function `void bfs(const Vertex &s)`
8. Implement the function `void dfs(const Vertex &s)`
9.  Implement the function `void dijkstra(const Vertex &s)`
10. Implement the function `Path shortest_path(const Vertex &s, const Vertex &t)`
    > **Note**: This function *does not* assume the edge weights are positive!
11. Implement the function `void add_vertex(Vertex v)`
12. Implement the function `void add_edge(Edge e)`

Optionally, implement **private** helper method(s) and write a comment explaining their behavior.

> **IMPORTANT**: The search functions `bfs`, `dfs`, `djikstra`, and `shortest_path` each dictate the order in which "equivalent" vertices must be visited.
> **You must adhere to this order for full credit on this assignment.**

#### Other Notes

The `Graph` class may seem complex.
That's because it is!
But it is not needlessly so.
The scaffolding we have provided within the `Graph` class enables you to think and program almost entirely in terms of objects of type `Vertex` and of type `Edge`.
You will rarely (but not never!) use objects of the template parameter types `V`, `E`, and `W`.

The generality of the graph you are implementing makes it reusable to solve many problems that can be modeled as a graph (not just the search algorithms that you are implementing).
For example, the [supplemental exercise](sixdegrees.md) asks you to use the `Graph` to write a program that computes the "Bacon Number" for a series of actors and actresses based on an input file representing the graph of all movies the actors and actresses have been in together.
It also showcases many advanced C++ language features that you ought to know about as you progress through your computer science education and into your career, and we have tried our best to demonstrate best practices.
These features include:
* Template type parameters
* Type traits
* Template metaprogramming
* Iterators
* C++ Standard Template Library
* Inner structs/classes
* Operator overloading
* IO stream manipulation
* Type inheritance
* Default parameters
* The `auto` keyword for type inference
* Exception handling

This is just scratching the surface of C++!
Here are a few of the features that we do *not* showcase in this starter code:
* Smart pointers
* Move semantics
* Polymorphism
* Parallel programming
* Functional programming

### `main.cpp`

The driver for this assignment is quite simple: it reads a graph from standard input, prints it, then runs various graph algorithms on the vertices identified by the command-line arguments.
The command line arguments are a series of nonnegative integers, which are the vertices of the graph from which you want to start the searches.
For example, to run the driver (after compiling to `graph-main`) on the sample input `k5.txt` and each of the 5 vertices in the graph, you would execute the following command and see the following output:

```
$ ./graph-main 0 1 2 3 4 < k5.txt
The graph is UNDIRECTED
Vertices (5):
(0) (1) (2) (3) (4) 
Edges (20):
(0)---<1>---(1)
(0)---<1>---(2)
(0)---<1>---(3)
(0)---<1>---(4)
(1)---<1>---(0)
(1)---<1>---(2)
(1)---<1>---(3)
(1)---<1>---(4)
(2)---<1>---(0)
(2)---<1>---(1)
(2)---<1>---(3)
(2)---<1>---(4)
(3)---<1>---(0)
(3)---<1>---(1)
(3)---<1>---(2)
(3)---<1>---(4)
(4)---<1>---(0)
(4)---<1>---(1)
(4)---<1>---(2)
(4)---<1>---(3)

------ BEGIN (0) ------

Breadth-first search:
(0)
(1)
(2)
(3)
(4)

Depth-first search:
(0)
(4)
(3)
(2)
(1)

Dijkstra's algorithm:
(0)
(1)
(2)
(3)
(4)

Shortest paths:
(0)~~~<0>~~~(0): (0)---<0>---(0)
(0)~~~<1>~~~(1): (0)---<1>---(1)
(0)~~~<1>~~~(2): (0)---<1>---(2)
(0)~~~<1>~~~(3): (0)---<1>---(3)
(0)~~~<1>~~~(4): (0)---<1>---(4)

-------- END (0) ------

------ BEGIN (1) ------
... and so on 
```

Feel free to modify it at will.

### Other C++ Files

In addition to `main.cpp` and `Graph.hpp`, you are also given two other helper files: `MinQueue.hpp` and `traits.hpp`, each of which encapsulate some useful functionality.

`MinQueue.hpp` contains the implementation of a priority queue of key/value pairs, organized as a min-heap over the key values.
You may find it useful when implementing the weighted-graph search algorithms such as `Graph::dijkstra`, though you are by no means required to use it.
(You are required to submit it with your project, however, because the autograder build script relies on its presence.)

The second file, `traits.hpp`, contains the definition of several [type traits](https://www.oreilly.com/library/view/c-in-a/059600298X/ch08s04.html) that are helpful to give more concise compiler error messages to you as you muck about in the `Graph` code.
C++ templates generate notoriously verbose warnings and errors, so we've done our best to include as many static and runtime assertions as we can to reduce the bloat.

#### Reading Compiler Error Messages

Despite our best efforts to soften the blow, you will still probably encounter horrifyingly long compiler errors.
When you do, take a step back, take a deep breath, and **start at the top**.

Look for the first line of compiler output that says "`error`" and navigate to that line in your source code.
You may immediately see the problem.
If so, great!
If not, no worries: work *backwards* from the end of that message.

For example, if I accidentally mistype `edge.label` as `edge.lable`, I get the following compiler error from my solution:

```
In file included from main.cpp:5:
Graph.hpp: In instantiation of ‘std::ostream& g::operator<<(std::ostream&, const Graph<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, unsigned int>::Edge&)’:
Graph.hpp:652:20:   required from ‘std::ostream& g::operator<<(std::ostream&, const Graph<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, unsigned int>&)’
main.cpp:30:18:   required from here
Graph.hpp:306:35: error: ‘const struct g::Graph<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, unsigned int>::Edge’ has no member named ‘lable’; did you mean ‘label’?
  306 |                 ss << "<" << edge.lable << ">";
      |                              ~~~~~^~~~~
      |                              label
```

The bits at the top about `std::ostream& g::operator<<(std::ostream&, const Graph<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, unsigned int>::Edge&)` are nigh impossible to parse, so I'll scan the output for "error".
I see that something happened on line 306 of `Graph.hpp`, but still I have a long template instantiation to read through.
However, at the end of that line I have the very helpful message, "... has no member named 'lable'; did you mean 'label'?" followed by a rendering of the offending line of code with the problematic characters underlined.
By going one token back from the readable part of the message I see that this is coming from the `Edge` type (the rest of the template nonsense is just scoping information I can usually ignore or, at worst, skim).
When I change the spelling 

### `makefile`

The default target in the provided `makefile` compiles an executable named `graph-main` that runs the driver code in `main.cpp`.
You may add to the `makefile` as you see fit, but you must preserve the provided target (`graph-main`) and compiler flags.

### Text files

To get you started on your testing, we have included with the starter code several small graph input files, most of which come directly from the examples in our lecture slides.
Before you get too far into the programming, you should draw each of the graphs by to ensure you understand how the input corresponds to a graph.

It may also be a good idea to remind yourself of the operation of BFS, DFS, Dijkstra's algorithm, and the Bellman-Ford algorithm before implementing them.
Trace the operation of those algorithms on the provided graphs (and some of your own!) before sitting down to write code.

> **Think**: What happens when you run the provided driver with the graph file `negative_weight.txt`?
> Does the output look right?
> Why, or why not?
> If not, what should you change to fix it?
> (Remember: you may not modify the `Graph` functions that you are given.)

### Reference executable

We have included with the starter code a reference executable named `ref-main` that you can use to assert that your program's output conforms exactly to the expected output for this assignment.
You should run it just like your own driver.

### Modification Restrictions on Starter Code

Modification restrictions are somewhat more relaxed than in previous assignments.
Generally speaking, other than `Graph.hpp` you may modify the starter code as you see fit.

#### Modification Restrictions on `Graph.hpp`

Any changes you make to `Graph.hpp` **must preserve the public interface** for `Graph`.
That is...

* You may *only* add members (member variables and member functions) in the `private` section
* You may not remove or modify any of the public struct definitions or function headers that are already implemented or that you are required to implement
* You may not modify any functions that are implemented for you in `Graph.hpp`
* You may not modify the `Graph` class definition or remove any assertions or constants that are part of the `Graph` class

## C++ Library Usage

The `Graph.hpp` file contains a litany of `#include` statements.
You may use definitions from any of the included library headers, but you may not add additional includes without written approval from Alan or Ozan.
If you would like to include additional header files **from the standard library**, make a *public* post on `Ed` describing a limitation of the provided includes or starter code and how your proposed module would help.
(Note that because the post must be public, it may not contain any of your code!)

Documentation for the various types and headers of the standard library is readily available at [cppreference.com](https://en.cppreference.com/w/cpp/header).

Under no circumstances may you include non-standard library headers.
For example, there is a `graph` component in the well-known [Boost C++ library](https://github.com/boostorg/graph) that includes&mdash;among other things&mdash;an implementation of each of the graph algorithms you are required to implement for this assignment.
We encourage you to explore its source code, but you may not include it in your project!

## Abstraction

The `Graph` type presents a thoroughly abstracted interface.
Use it!
The abstraction provided by the graph permits you to implement many of the required functions even before adding private members, and some of those implementations will essentially be the pseudocode we discussed in class, just "C++ified".
(Your code won't *run* until you have private members, of course, but you can write and compile some implementations and *reason about* their behavior in the abstract.)

> **Think**: There are limits to the generality of the particular graph interface you are implementing.
> Can you think of any problems that would require modifying the graph's implementation directly?
> How could you improve the interface to support these problems?

## Testing

As with all of the assignments this semester, the autograder will have a series of test cases that will exercise your code.
We have provided some of them to you in the form of the graph input files, which you can explore by using them as input to the provided driver function, like so:

```
$ ./graph-main 0 < k5.txt
The graph is UNDIRECTED
Vertices (5):
(0) (1) (2) (3) (4) 
Edges (20):
(0)---<1>---(1)
(0)---<1>---(2)
(0)---<1>---(3)
(0)---<1>---(4)
(1)---<1>---(0)
(1)---<1>---(2)
(1)---<1>---(3)
(1)---<1>---(4)
(2)---<1>---(0)
(2)---<1>---(1)
(2)---<1>---(3)
(2)---<1>---(4)
(3)---<1>---(0)
(3)---<1>---(1)
(3)---<1>---(2)
(3)---<1>---(4)
(4)---<1>---(0)
(4)---<1>---(1)
(4)---<1>---(2)
(4)---<1>---(3)

------ BEGIN (0) ------

Breadth-first search:
(0)
(1)
(2)
(3)
(4)

Depth-first search:
(0)
(4)
(3)
(2)
(1)

Dijkstra's algorithm:
(0)
(1)
(2)
(3)
(4)

Shortest paths:
(0)~~~<0>~~~(0): (0)---<0>---(0)
(0)~~~<1>~~~(1): (0)---<1>---(1)
(0)~~~<1>~~~(2): (0)---<1>---(2)
(0)~~~<1>~~~(3): (0)---<1>---(3)
(0)~~~<1>~~~(4): (0)---<1>---(4)

-------- END (0) ------
```

In addition to running the provided driver on your code, we will also run **unit tests** on each of the functions you are required to implement.
We strongly encourage you to write your *own* unit tests because as you do so, it's highly likely that you will devise situations that are not encountered in running the driver as given.

> **Think**: What happens if you add an edge or vertex to a graph that is already built?
> How should the vertex vector change?
> What about the edge set?

## Submitting

Upload to Gradescope before the deadline.
Do not upload object (`.o`) files or executables (such as `graph-main`), but do include all source and header files needed to compile your code along with your `makefile` (or `Makefile`).
At a minimum, you must submit the following files:

* `main.cpp`
* `Graph.hpp`
* `MinQueue.hpp`
* `traits.hpp`
* `makefile` (or `Makefile`)

## Extra Practice: Six Degrees of Insert Name Here

We have provided the instructions for some extra graph and C++ practice exercises in [`sixdegrees.md`](sixdegrees.md).
You are encouraged to attempt these exercises for your own benefit, although completing these activities will not affect your grade.

&copy; 2024 Alan Weide
