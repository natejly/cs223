# Pset 6
## CPSC 223
## Due Date: 11:59 PM NHT on Friday Apr 12, 2024

## Introduction

In this assignment, you will devise an implementation of each of three kinds of Binary Search Trees:

1. A naive Binary Search Tree
2. An AVL Tree
3. A Red-Black Tree

A **binary search tree** has the invariant that all nodes to the left of a node are smaller in value, and all nodes to the right are larger in value.
Every AVL Tree and Red-Black Tree is a "self-balancing" binary search tree.

Why is balancing a BST important?
If a binary search tree is balanced (or close to being balanced), it has a logarithmic runtime for the following functions:

* `minimum_value()`
* `maximum_value()`
* `contains(value)`
* `insert(value)`
* `remove(value)`
* a few others

However, if the binary search tree is *not* balanced, the runtime for these operations could be linear in the number of nodes in the tree!

## Makefiles

As with Pset 5, the makefile is given.
You may not change the makefile.
Type `make` to compile the code you write.
Run the program(s) with `./bst`, `./avlt`, or `./rbt`.
Each individual executable can be compiled in isolation with `make bst`, `make avlt`, or `make rbt`.

## Starter Code

You may not modify the driver(s) for this assignment (in files `main_*.cpp`).
In addition to the driver(s), you are given an extra function that can be used to print out your trees (because it's kind of a pain to write such a thing from scratch!).
Looking at the trees that print (after doing operations such as `insert`, `remove`, *etc.*) can be a good way to check the correctness of your code.
A *better* way to check correctness of your code is to use the provided `BSTNodeChecker` class functions `is_bst`, `is_avlt`, and `is_rbt`, which are used by the public `is_valid` function in each of `BSTree`, `AVLTree`, and `RBTree`.

## The Assignment

For this assignment, we provide the header files (`BSTree.h`, `AVLTree.h`, and `RBTree.h`) file and most of the implementations in `BSTree.cpp`, `AVLTree.cpp`, and `RBTree.cpp`, which call corresponding functions on the tree's `root`, which is a `BSTNode`.
You are responsible for writing many of the implementation functions in `BSTNode.cpp`, although we have provided you with some of the functions already.

Remember, self-balancing trees are a subset of binary search trees.
That means that your AVL Trees and Red-Black trees must maintain the binary search tree invariant that all values in the left subtree of any node are less than the node and all values in the right subtree are greater than the node.
They must *additionally* maintain the invariants enforcing balance, so be careful!
We have thoroughly commented the header files (interfaces), so please refer to those for specific information.

You are not allowed to change the header or functionality of the public functions.
What you *can* do is to add extra functions and attributes to your code to better modularize the program.
These functions and attributes are to be added only under the `private` section of your code in the header files or, in the case of a function that does not require you to access the tree itself, as a separate function defined only in the `.cpp` file.

You are responsible for implementing all or part of the following functions, within the listed time bounds:

### In `BSTree.cpp`, `AVLTree.cpp`, and `RBTree.cpp`

* The assignment operator overload in each, which must run in $O(n)$ time

### In `BSTNode.cpp`

#### Public Functions

* `BSTNode::BSTNode(const BSTNode &source)`, the copy constructor
  * $O(n)$
* `BSTNode::~BSTNode()`, the destructor
  * $O(n)$
* `const BSTNode* BSTNode::minimum_value() const`
  * $O([\textit{height of this}])$
* `const BSTNode* BSTNode::maximum_value() const`
  * $O([\textit{height of this}])$
* `const BSTNode* BSTNode::search(int value) const`
  * $O([\textit{height of this}])$
* `BSTNode *BSTNode::bst_insert(int value)`
  * $O([\textit{height of this}])$
* `BSTNode *BSTNode::avl_insert(int value)`
  * $O(\log n)$
* `void BSTNode::bst_remove(int value)`
  * $O([\textit{height of this}])$
* `void BSTNode::avl_remove(int value)`
  * $O(\log n)$
* `int BSTNode::node_count() const`
  * $O(n)$
* `int BSTNode::count_total() const`
  * $O(n)$

#### Private Functions

* `BSTNode *BSTNode::right_rotate()`
  * $O(1)$
* `BSTNode *BSTNode::left_rotate()`
  * $O(1)$
* `BSTNode *BSTNode::avl_balance()`
  * $O(1)$
* `BSTNode *BSTNode::rbt_insert_helper(int value)`
  * $O(\log n)$
* `BSTNode *BSTNode::rbt_eliminate_red_red_violation()`
  * $O(1)$

> **Note**: This may seem like a lot, but observe that many of the implementations share much of their body, and even more of them have remarkably similar structure!
> It's likely you will be copy-pasting significant chunks of your code, so as you do so think about ways in which you can eliminate duplicate code without copy-pasting.

The `BSTNode` class has private members including the tree's height and color.
Not all of those fields are useful for every tree kind.
For example, your naive BST and AVL tree implementations should *not* use the `mColor` field (you'll notice the output of the reference implementation shows every node in those trees as `BLACK`).
The naive BST and Red-Black tree implementations are unlikely to need the `mHeight` field.

We will run performance tests on each of these functions to assert that they conform to the required time bounds.

## Notes about the starter code

### Pre-implemented Functions

Many of the pre-implemented functions are convenience functions that might help you keep your code concise, but are not fundamental to the behavior of a binary search tree.
However, one major function that is implemented for you is `rb_remove`.
We encourage you to study that implementation because it is interesting, but you are not responsible for understanding the Red-Black tree deletion algorithm for this course.
Because that function is implemented for you, however, it means that the driver's output is not particularly helpful as it pertains to your own code for Red-Black trees.
You must write unit tests for your `rb_insert` function to ensure that it appropriately maintains the Red-Black tree invariants&mdash;the driver only displays the tree after *all* insertions are complete, which is not enough to guarantee the invariants always hold.

### Private Fields and Getters

The `BSTNode` class defines 7 private fields:

* `int mData;`
* `int mCount;`
* `int mHeight;`
* `Color mColor;`
* `BSTNode *mLeft;`
* `BSTNode *mRight;`
* `BSTNode *mParent;`

Many of these private fields are matched to a corresponding **getter function**:

* `int data() const`
* `int count() const`
* `int height() const`
* `BSTNode *left_child() const`
* `BSTNode *right_child() const`

Within your `BSTNode` methods (both public and private methods, as well as friend functions), you can access the private fields and methods of a `BSTNode` directly, such as in `return this->mData;` or `this->mLeft->mParent = this;`.
*Outside* of the member and friend functions, however, direct access to the fields is a compile-time error.

#### Why no getter for `mColor` or `mParent`?

This is an example of **information hiding**, a powerful tool to aid object-oriented programmers in enforcing their abstractions.
In this case, the abstract view of a `BSTNode` as the collection of the node itself and its subtrees suggests that the parent of a node is rarely of importance.
Only in the implementation of the private functions is the idea of a node's parent useful.

Similarly, the color of a node is not pertinent to the abstract view of a tree.

#### Why no setters?

Each instance of the `BSTNode` class has an **invariant** that if it has nonempty children, then the data in its left child is less than its data, and that the data in its right child is greater than its data.
There is also an invariant that a `BSTNode` is part of a binary tree (this relates the `left` and `right` children and the `parent`s of nodes), and that its `height` is equal to the length of the longest path from it to a leaf in its tree.
Moreover, AVL trees and red-black trees have even stronger invariants relating the `height`s and `color`s of nodes.

Providing a setter for any of these fields would permit a client of our `BSTNode` class to break these invariants.
For example, one could, given the appropriate setter function, write the code:
```
root->set_left(root);
```
This would set a node's left child to itself!!
This clearly breaks the invariant that a `BSTNode` is part of a tree.
Instead, we only permit a client to mutate the tree through the **interface**, which is specified such that every function **maintains the invariants** of a `BSTNode`.

This kind of component design is emblematic of **object-oriented programming**, which is a way of structuring programs such that everything a client does with an object is in terms of its **abstract value**.
Structuring the code in this manner permits us to more easily reason about our software that uses interfaces because the client need not rely on understanding (potentially complicated) representations of objects; instead, they can think in terms of the interface.

### Friends in C++

In C++, a `friend` function is a non-member function within which access to private members (fields and methods) is permitted.
A `friend` class is a class with the same permission.

The `BSTNode` class has several `friend`s:
```
/**
 * Returns the direction opposite dir, or ROOT if dir is ROOT.
 */
friend Direction opposite_direction(Direction dir);

friend class BSTNodePrinter;
friend class BSTNodeChecker;
```

The `opposite_direction` function is used in some of the starter code that is implemented for you, and you may use it in your code if you like (though it's unlikely to be necessary).
The friend classes are implemented for you and use the private fields of the tree nodes to check properties about them and to print them in a readable manner.

### Modification Restrictions and Style

Except for the assignment operator overloads in `BSTree.cpp`, `AVLTree.cpp`, and `RBTree.cpp`, the only starter code file you may modify is `BSTNode.cpp` (or its corresponding `.h` file, in the case that you add private members or functions to it&mdash;you may only add to it, and may not change or remove anything that is already there).
Any style violations in starter code are intentional, generally to exhibit alternate code styles.
All code that *you* write must conform to the style guide.

### "Assumes" Clauses

Many of the functions you are required to implement have specifications that include an "Assumes" clause.
These are facts that the function body is allowed to assume are true; their behavior if that assumption is violated is undefined.
Your implementation does not need to handle any cases that violate the assumptions since we will not run unit tests that violate those things.
Instead, it is the responsibility of the *caller* of the function to ensure the assumption holds true.
This could be done by explicit checks, or it could be implicit (for example, the assumption by `minimum_value` that the tree is non-empty could be guaranteed by the fact that all paths through the calling code insert some items into the tree before calling it).
In general, explicit checks should be used sparingly, and you should strive to write code that implicitly guarantees the assumptions hold true at the point of each call.

### TODO markers

Each function you are required or encouraged to implement is marked with the following line of code or similar:
```C++
#pragma message "TODO: Implement this function"
```

This generates a compiler message that looks like the following for each of them:
```
BSTNode.cpp:134:17: note: ‘#pragma message: TODO: Implement this function’
  134 | #pragma message "TODO: Implement this function"
      |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

Each time you implement a required function, you should remove this line from that function.
If you compile your program and there are still such notes, *you are not yet done*!
You must implement all functions marked with these TODO messages.

## The Reference Executables

We will provide three compiled binaries that run the same driver you have been given, named `the_bst`, `the_avlt`, and `the_rbt`, which were compiled and will run on the Zoo (but probably not your personal computer).
We encourage you to study their output carefully; it’s quite an interesting end product that you’ll end up with!
Pay careful attention to the format of the output.
Assessment of your submission will be automated, so even small errors in spacing can have an impact on your grade.
Fortunately, most of the output formatting is performed by code that was written for you, so as long as you do not modify `main_*.cpp` or `pretty_print.cpp` (you are not supposed to, anyway!), the output spacing should conform to expectations.
You can also verify that your code is correct by executing `diff` on the output obtained by the reference implementation (an empty diff is a good diff).

## Testing

In addition to performance tests that validate your algorithms' asymptotic complexity, the autograder on gradescope will include a number of diff tests (not all of which are visible to you) and some unit tests (again, not all of which are visible).
The suite of visible test cases will, as usual, not be complete but we will drop hints here and there about what kinds of things you should look for in your testing.

> In fact, we'll start those recommendations now!
> 
> 1. Pay careful attention to your implementation's handling of duplicate entries.
> 2. Consider the worst-case scenario for inserting a bunch of values into a naive BST. How does your AVL tree handle it? Your Red-Black tree?
> 3. What does a newly-created tree look like? A newly-destroyed one?
> 4. What happens if you don't put anything at all into your tree and try to call the various functions?
>   * Are there any functions that are meaningless to test in this situation?
> 5. How big can you make your tree before things start to noticeably slow down? Does this limit change depending on the self-balancing algorithm used?

In addition to these tips, we have also provided an implemented class, `BSTNodeChecker`, that defines and implement three public functions:

* `bool is_bst(BSTNode *root)`
* `bool is_avlt(BSTNode *root)`
* `bool is_rbt(BSTNode *root)`

These three functions can be used to help you assert the correctness of your insert/remove functions for each of `BSTree`, `AVLTree` and `RBTree`.
Be warned, however, that each of them runs in $O(n)$ time, so you *should not* include calls to these functions in your submitted code lest you run afoul of efficiency requirements.

Remember `unittest.cpp` from the last pset?
We strongly encourage you to create a version of that with your own unit tests for the `BSTree`, `AVLTree`, and `RBTree` implementations.
Ask one of the course staff if you'd like some guidance on how to get started.
Here are some resources to give you a better overview of unit testing in general:

* [Programming: Principles and Practice Using C++](https://learning.oreilly.com/library/view/programming-principles-and/9780133796759/), Chapter 26: "Testing"
* [Googletest](https://google.github.io/googletest/)
  * **Note**: Googletest (aka gtest) relies on toolchains we haven't discussed in class (and won't!) but it's an industry standard unit testing framework for C and C++ code and it's probably worth an hour or two of your time to get it set up and familiarize yourself with its basics

## Tips and Hints

Before you write any code at all, familiarize yourself with the interface(s) for the classes you are asked to implement.
In particular, study and digest the detailed comments in the `BSTNode.h` interface file, which describes the behavior of a `BSTNode`.
After you are comfortable with the interface(s), study the pre-implemented functions to solidify your sense of how the representation maps to an abstract state (in other words, internalize the *abstraction function* for a `BSTNode`).
Next, study the output of the reference executable and ensure you understand exactly how the tree gets from one value to the next.
Only then should you start writing code.

You are asked to implement many functions for this assignment.
We suggest you start by implementing the functions needed for the naive binary search tree (`BSTree`) before moving on to the self-balancing trees.
That is, you should start in the `BSTNode` class with `minimum_value`, `maximum_value`, `search`, `bst_insert`, `bst_remove`, `node_count`, and `count_total`.
There is a naive Binary Search Tree implementation in the demo code from lecture, although it does not deal with duplicate entries and has a slightly different abstraction function than the one you are asked to implement here (in the lecture code, an empty tree is represented by a `nullptr` node; in this assignment, an empty tree is a non-null node with height `-1`).
Use that as a jumping-off point for your implementations in this assignment.
As you implement functions, you'll undoubtedly recognize patterns emerge, so use those patterns to reduce your work by leveraging implementations from one function in another function.

As you implement each of the self-balancing functions `avl_balance` and `eliminate_red_red_violation`, ensure that you conform *exactly* to the specified behavior.
The specifications for required functions are written such that they solve a **local** problem that can be leveraged to solve a **global** problem by repeated invocation of those functions.
They *do not* solve the global problem on their own.
Each relies on some facts about the tree being true before calling (their assumptions), which enables them to guarantee the invariants hold after the function.
For example, the function `avl_balance` assumes that the tree is "almost balanced" (that the height difference between its left and right children is no greater than 2) and `rb_eliminate_red_red_violation` assumes that within the tree rooted at `this`, the only violation (if there is one) is in the neighborhood of `this`.

It's likely that the most challenging function you write is `rb_eliminate_red_red_violation`.
Make sure you budget significant time for that function, because it does not follow the same pattern as other functions you're required to implement.

## Submitting

Upload to Gradescope before the deadline.
Do not upload object (`.o`) files or executables (such as `bst`, `avlt`, `rbt`, `the_bst`, `the_avlt`, or `the_rbt`), but do include all source and header files needed to compile your code along with your `makefile` (or `Makefile`).
At a minimum, you must submit all files included in the starter code, which are:

* `AVLTree.cpp`
* `AVLTree.h`
* `BSTNode.cpp`
* `BSTNode.h`
* `BSTNodeChecker.cpp`
* `BSTNodeChecker.h`
* `BSTNodePrinter.cpp`
* `BSTNodePrinter.h`
* `BSTree.cpp`
* `BSTree.h`
* `main_avlt.cpp`
* `main_bst.cpp`
* `main_rbt.cpp`
* `makefile`
* `RBTree.cpp`
* `RBTree.h`

## Further Reading

### For somewhat interested students

When you try to make a copy of an object, the copy constructor or assignment operator overload gets called, depending on the situation.
Why? The C++ compiler only makes shallow copies automatically&mdash;all the data is copied exactly from one object to the other.
This is fine for fundamental types (`int`, `bool`, `float` *etc.*).
But pointer types are also copied to the new object (so the new object points to the same location)!
This leads to aliasing of values referred to by pointer members.
We need to make a *deep* copy of the object (in this case, a new BST, AVL Tree, or Red-Black tree that is identical to the original one is created at a *different* location in memory so any modification to one of the trees is not reflected in the others).

There is nothing magical about either a copy constructor or an assignment operator overload, but it does take some time to learn how to write them.
The structure is (almost) always the same, however, so you should be able to follow the code on the page below to write the ones for this assignment.
Read the following article if you want more information on those two operations: http://www.cplusplus.com/articles/y8hv0pDG/.

### For interested students

Trees can contain elements of any kind&mdash;not just `int`s!
In C, we implemented a generic `gmap` type using `void *` and a variety of function pointers.
In C++, generics are implemented using [templates](https://en.cppreference.com/w/cpp/language/templates).
Rewrite your `BSTNode` class to be a template class as follows:

```
template <typename T> class BSTNode
{...}
```

Here, the template argument `T` is the type of the item in the tree.
Observe that to use `T` in the tree, you must be able to compare values of type `T` (otherwise, how would you know which direction to go to find a value?).
In your implementation, you should use the `<` operator to compare values, which can be overloaded in the class `T` just like the assignment operator.
If a client attempts to use your templated `BSTNode<T>` class with a type that does not overload the `<` operator, they will receive a compile-time error.

What changes do you need to make to `BSTree`, `AVLTree`, and `RBTree` to accommodate the templated `BSTNode` class?
Could you go further and template *those* classes, too?
What would happen?

### For very interested students

Deep copying can be expensive.
The C++11 standard introduced *move semantics* to help with this.
Move semantics *transfer ownership* of a value from one variable to another, which prevents the aliasing problem mentioned above and makes it "cheap" to assign a value to a new variable.
A good introduction to move semantics is available at https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/.
(As a bonus, that tutorial *also* provides an introduction to "smart pointers", a beautiful construct in C++ to help us manage memory.)
We encourage you to implement a move constructor and overload the moving assignment operator for your `BSTree`, `AVLTree`, and `RBTree` classes.

### For extremely interested students

A Binary Search Tree could be considered a **subtype** of a "[Multiset](https://en.wikipedia.org/wiki/Multiset)" type.
In turn, AVL Trees and Red-Black Trees are each a subtype of a Binary Search Tree.
That is, a client interacts with a naive BST, an AVL Tree, and a Red-Black Tree in exactly the same manner as one another, which is as if it is a set of (possibly duplicated) things!
This **shared interface** can be codified in C++ by defining an [abstract class](https://en.cppreference.com/w/cpp/language/abstract_class) called `Multiset`, containing the following virtual functions:

* `virtual int count_of(int value)`
* `virtual void insert(int value)`
* `virtual void remove(int value)`
* `virtual int some_value()`, which returns an arbitrary element of `this`
* `virtual void size(int value)`

Implementing `Multiset` in the context of this assignment would probably require significant restructuring of your code and *you should not implement it for this assignment*.
If you are "extremely interested", come talk to one of us and we can have a conversation about polymorphism and subtyping in C++.

> Note the similarities to and differences from the provided interface in `AVLTree.h` and `RBTree.h`.
> Think about why these differences exist and how you could write an implementation for this hypothetical `Multiset` class using a Binary Search Tree (or AVL or Red-Black Tree) as a representation, and how to extend this typing relationship between naive BSTs and self-balancing trees.

### For ridiculously interested students

The three BST implementations share an enormous amount of code between them, but there is no obvious way to implement these things without duplicating the code.
That is not to say there is *not* a way to do so.
One way to do so would be to leverage the [Curiously Recurring Template Pattern](https://en.cppreference.com/w/cpp/language/crtp), which lets one implementation for a function be shared among many implementations of a type, each of which returns a different type of thing (which is then used to, e.g., make a recursive call, or assign to a variable of derived type).
Doing so would require a tremendous restructuring of your code and *you should not implement it for this assignment*.
If you are "ridiculously interested", come talk to one of us and we can have a conversation about this clever use of C++ template classes.

---
&copy; 2024 Alan Weide and Ozan Erat
