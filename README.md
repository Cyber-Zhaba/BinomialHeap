# Binomial Heap

<img src="https://neerc.ifmo.ru/wiki/images/thumb/b/b3/BinHeapExample.png/488px-BinHeapExample.png" alt="drawing" width="300"/>

This project implements a **Binomial Heap** data structure in C++. The goal is to manage multiple heaps and perform various operations efficiently without using any standard library functions. The code is optimized for handling a series of heap-based operations as described below.

## Task Overview

The task involves implementing a binomial heap that supports the following operations:

1. **Add Element** (`0 a x`): Adds an element `x` to the heap numbered `a`. Each added element is assigned a unique index, equal to the sequential number of the operation (starting from 1).
2. **Merge Heaps** (`1 a b`): Moves all elements from heap `a` to heap `b`, leaving heap `a` empty.
3. **Delete Element by Index** (`2 i`): Removes the element with the specified index `i`.
4. **Update Element by Index** (`3 i x`): Assigns a new value `x` to the element with the specified index `i`.
5. **Get Minimum Element** (`4 a`): Outputs the minimum element from heap `a`. Guaranteed to have \(O(1)\) time complexity.
6. **Delete Minimum Element** (`5 a`): Deletes the minimum element from heap `a`. If multiple elements have the same minimum value, the one with the smallest index is removed.

### Input/Output

The program processes commands in sequence:
- **Input**: First line specifies two integers, `n` (number of heaps) and `q` (number of queries).
- **Commands**: A series of commands as per the above operations.
- **Output**: Based on the commands, the program outputs the results of `4 a` operations (minimum values).

### Example

#### Input
```
3 19
0 1 10
4 1
0 2 5
0 2 7
4 2
3 2 20
4 2
1 2 1
4 1
5 1
4 1
3 2 3
4 1
2 2
4 1
0 1 9
1 1 3
0 3 8
4 3
```

#### Output
```
10
5
7
7
10
3
10
8
```

## Code Description

The code defines a `BinomialHeap` class that supports binomial tree structures, where each node can have multiple children but maintains a specific heap ordering.

### Class Structure

- **`BinomialHeap::Tree`**: Represents each node in the binomial tree with properties:
  - `data`: Stores the element's value.
  - `degree`: Degree of the tree rooted at this node.
  - `id`: Unique identifier (index).
  - `parent`, `child`, `sibling`: Pointers to related nodes in the tree structure.

- **`BinomialHeap`**: Contains the main operations for managing binomial heaps:
  - **`Insert(int key, int x)`**: Adds a new element `x` to the heap `key`.
  - **`Move(int key1, int key2)`**: Merges heap `key1` into heap `key2`.
  - **`ExtractMin(size_t key)`**: Removes the minimum element from heap `key`.
  - **`DeleteElement(int id)`**: Deletes the element with the specified index.
  - **`UpdateElement(int id, int new_value)`**: Updates the value of the element at `id` to `new_value`.
  - **`GetMin(int key)`**: Retrieves the minimum element from heap `key` with \(O(1)\) complexity.

### Private Methods

- **`Merge(Tree* tree1, Tree* tree2)`**: Merges two trees with the same degree.
- **`Union(std::vector<Tree*>& heap1, std::vector<Tree*>& heap2)`**: Unites two binomial heaps.
- **`SiftUp(Tree* node)`** and **`SiftDown(Tree* node)`**: Adjust the heap structure to maintain the minimum heap property.

### Main Function

The `main()` function initializes a binomial heap and processes input commands, calling the relevant methods based on the command type.

### Complexity

The solution is optimized for efficient merging and retrieval:
- **Insert and Merge**: $\mathcal{O}(\log n)$.
- **GetMin**: Guaranteed $\mathcal{O}(1)$.
- **Delete and Update**: $\mathcal{O}(\log n)$.

## Usage

To compile and run the program:

```bash
g++ -o binomial_heap main.cpp
./binomial_heap
```

Provide the input in the specified format, and the program will output the results of `4 a` commands.

## Limitations

This implementation is designed with assumptions based on the task requirements:
- Each element has a unique index.
- Heaps are numbered sequentially and accessed by their numbers.
- No standard library functions are used for heap operations, which are implemented manually.