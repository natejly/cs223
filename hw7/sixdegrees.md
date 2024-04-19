# Extra Practice

If you're as excited about Graphs as we are, you may be thinking, "but what else can I do with graphs?"
Look no further!
Here is a fun application of a graph we borrowed from a friend of ours.
You may complete these tasks for your own benefit, but:

> **Doing so will not affect your grade and you should not submit any files related to this exercise with your submission of Pset 7 to Gradescope.**

This exercise will help you explore how to modify "generic" graph search algorithms to fit into different domains.
As you work on this exercise, think about ways to further parameterize the `Graph` class to make it even more reusable!

### The Activity

Ever heard of the game *Six Degrees of Kevin Bacon*?
(Play the game online: it is fun and counts as serious academic work.)
Your task is to make a program that plays the game.
Specifically, it should accept queries in the form of the names of two actors, and report:
1. the "*costar distance*" and
2. a shortest path to get from the first actor to the second

The "Six Degrees" program relies on an undirected, unweighted graph whose vertices and edges are `strings`.
Every actor from an input file `actors.txt` becomes a vertex of the graph.
There is an edge between two actors if they have appeared in a movie together.
If the actors have appeared in multiple movies together, only one edge exists (it does not matter which of the movies is represented on the edge).
For each edge, the print format should be: `[Vertex] was in [Edge] with [Vertex]`, and is ended by a newline. For example:

```
Jeff Bridges was in The Big Lebowski with John Goodman
```

## SixDegrees class

This class is responsible for the `Graph` itself, and for interacting with the user. 
It should have a `Graph` with `string` vertices and edges as its only attribute.

Implement the following functions in the `SixDegrees`:

- A constructor that takes a `string` argument that is interpreted as the name of the actors input file.
  The constructor should open a stream to that file and then populate the graph based on its contents.
  Before returning, the constructor should close the file stream.
- A function to populate the graph from an "actors" input file. 
  The format of this file is explained [below](#input-file) (it is different than the input format expected by the `Graph` constructor!).
  You should add an edge between two actors if they appeared in a movie together (remember that if two actors participated in more than one movie together you still only have one edge. 
  You can store any of the movie titles).
  You can assume that the actors file exists and is in the correct format (but it need not be equal to the sample one we provide)
- A function with the signature `void run(istream &in, ostream &out)`.
  This function is called from the driver. 
  It should repeatedly prompt for the names of two actors, separated by a newline. 
  It should call the `unweighted_shortest_path` function described below and print the connections between the two actors.
  The input comes from the `istream` indicated by `in`, and the output is printed to the `ostream` indicated by `out`. 
  If either actor is not found in the graph, then print to `out` the text `Sorry, [actor name] is not in the list.`.
  The algorithm must be case sensitive.
  That is, if the user queries `uma thurman`, she would not be found (because the file contains `Uma Thurman`). 
  If the second actor is not on the list then keep asking until you get a second valid actor (and pair with the first valid actor).
- A function with the signature `Graph::Path unweighted_shortest_path(Graph::Vertex s, Graph::Vertex t)`.
  This function should return the shortest path between two actor vertices, so that the `run` function can display it.
  It should use a modified **breadth-first-search** algorithm to track the shortest path and terminate when the target is found.

### Input File

The actors' input file has the following format:

    Actor name
    Movie
    Movie 
    Movie
    *
    Actor name
    Movie
    Movie
    *

You do not know in advance how many movies a given actor has appeared in.
Instead, use the delimiter (`*`) to distinguish between one actor and the next.
You may want to use `getline` for reading from this file, because actors and movies have varying-length names.

> **Hint**: this input format differs in an important way from the `Graph` input in the primary assignment, which is that the edges (i.e., movie names) appear for one actor potentially long before they appear for another actor.
> How can you track the movies an actor has been in so that when a repeated movie comes up with a later actor, you can query it and match the second actor with the first?
> What data structures do you know that can do this?
> Could you define an extra class to encapsulate this functionality?


### The Driver

To get the "six degrees" game started, you should write a driver with the following main function, which accepts a single command-line argument which is the name of the actors' input file:

```
int main(int argc, char *argv[])
{

    SixDegrees sd(argv[1]);
    sd.run(std::cin, std::cout);

    return 0;
}
```

The driver is invoked by a command such as:

```
$ ./sixdegrees actors.txt
```

When the user runs the driver, then the names of two actors to look for comes via `stdin` and the name of the actors input file is the first command-line argument.
A sample interaction with the program might look like this:

    Enter two actor names separated by a new line. Press `ctrl-D` to quit
    John Goodman
    Meryl Streep
    John Goodman and Meryl Streep have a costar distance of 4
    John Goodman was in The Big Lebowski with Sam Elliott
    Sam Elliott was in Ghost Rider with Wes Bentley
    Wes Bentley was in The Hunger Games with Stanley Tucci
    Stanley Tucci was in Julie & Julia with Meryl Streep

If you don't want to run in this "interactive" mode and you have a file consisting of pairs of actor names that you'd like to query about, you can redirect `stdin` using a command such as:

```
$ ./sixdegrees actors.txt < test_input.txt
```

You can also redirect `stdout` to a file by appending `> my_output.txt` to either of the above commands.
