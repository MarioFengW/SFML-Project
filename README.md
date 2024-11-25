# Data Structures and Algorithms Visualizer using SFML

This C++ project leverages the SFML library to provide an interactive graphical representation of various algorithms and data structures. The program aims to help users understand the inner workings of these algorithms through visual and interactive animations.

---

## Objectives

- **Visualize:** Understand the behavior of fundamental search and sorting algorithms, as well as data structures.
- **Interact:** Provide custom inputs and observe real-time animations of each algorithm.
- **Learn:** Gain insights into algorithm complexity through step-by-step graphical demonstrations.

---

## Features Overview

### 1. Search Algorithms

#### Linear Search (Sequential Search)
- **Description:** Iterates through the array element by element until the target value is found.
- **Time Complexity:** O(n)
- **Space Complexity:** O(1)

**Visualization:**
- Highlights each element visited during the search.
- Permanently highlights the found element.

**Interaction:**
- Users define the number of elements and their values.
- Input the target value to search.
- Observe real-time progress through visual animations.

#### Binary Search
- **Description:** Works on sorted arrays, dividing the array into halves to locate the target value.
- **Time Complexity:** O(log n)
- **Space Complexity:** O(1)

**Visualization:**
- Highlights the current search range and the middle element at each step.
- Shows how the range narrows progressively.

**Interaction:**
- Users define the number of elements and their values.
- Select the value to search.
- Watch each step of the search through an animated display.

---

### 2. Sorting Algorithms

#### Bubble Sort
- **Description:** Repeatedly compares and swaps adjacent elements if they are in the wrong order.
- **Time Complexity:** O(n^2)
- **Space Complexity:** O(1)

**Visualization:**
- Highlights elements being compared.
- Animates swaps to show each step clearly.

#### Selection Sort
- **Description:** Selects the minimum element in each iteration and places it in its correct position.
- **Time Complexity:** O(n^2)
- **Space Complexity:** O(1)

**Visualization:**
- Highlights the minimum element found in each iteration.
- Visualizes the swapping process.

#### Insertion Sort
- **Description:** Constructs a sorted subarray one element at a time by inserting elements into their correct position.
- **Time Complexity:** O(n^2)
- **Space Complexity:** O(1)

**Visualization:**
- Highlights the element being inserted.
- Shows how elements shift to accommodate the new element.

#### Merge Sort
- **Description:** Recursively divides the array into halves and merges sorted subarrays.
- **Time Complexity:** O(n log n)
- **Space Complexity:** O(n)

**Visualization:**
- Highlights subarrays during the division process.
- Animates the merging of sorted subarrays.

#### Quick Sort
- **Description:** Uses a pivot to partition the array into elements smaller and larger than the pivot, sorting them recursively.
- **Time Complexity:** O(n log n) on average; O(n^2) in the worst case
- **Space Complexity:** O(log n)

**Visualization:**
- Highlights the pivot and partitions.
- Shows the rearrangement of elements around the pivot.

---

### 3. Linear Data Structures

#### Stacks (LIFO)
- **Description:** Implements push and pop operations based on the Last-In, First-Out principle.
- **Time Complexity:** O(1) per operation
- **Space Complexity:** O(n)

**Visualization:**
- Displays the stack structure, highlighting elements during push and pop operations.

#### Queues (FIFO)
- **Description:** Implements enqueue and dequeue operations following the First-In, First-Out principle.
- **Time Complexity:** O(1) per operation
- **Space Complexity:** O(n)

**Visualization:**
- Shows elements moving through the queue with visual indications of front and rear positions.

#### Linked Lists
- **Description:** Consists of nodes connected via pointers, supporting insertion, deletion, and search operations.
- **Time Complexity:** O(n) for search; O(1) for insertion/deletion at the head
- **Space Complexity:** O(n)

**Visualization:**
- Displays nodes as boxes connected by arrows, animating pointer changes during insertion or deletion.

---

### 4. Non-Linear Data Structures

#### AVL Trees (Self-balancing Binary Search Trees)
- **Description:** Automatically balances after insertions and deletions to maintain optimal height.
- **Time Complexity:** O(log n) for insertion, deletion, and search
- **Space Complexity:** O(n)

**Visualization:**
- Illustrates tree rotations and balancing operations.
- Displays the AVL tree structure dynamically.

#### Graph Algorithms

**Dijkstra's Algorithm**
- **Description:** Computes the shortest paths from a source node to all other nodes in a weighted graph.
- **Time Complexity:** O(V^2) or O(E + V log V) with a priority queue
- **Space Complexity:** O(V)

**Visualization:**
- Animates the step-by-step execution of Dijkstra’s algorithm.
- Highlights the pathfinding process.

**Interaction:**
- Users select the start and end nodes to observe the shortest path computation.

#### DFS (Depth-First Search)
- **Description:** Explores each branch of a graph deeply before backtracking.
- **Time Complexity:** O(V + E)
- **Space Complexity:** O(V) (due to recursion or stack usage)

**Visualization:**
- Highlights nodes and edges in the order of traversal.

**Interaction:**
- Users select the starting node.
- Animations show the traversal process in real time.

#### BFS (Breadth-First Search)
- **Description:** Traverses a graph level by level, visiting all neighbors before deeper levels.
- **Time Complexity:** O(V + E)
- **Space Complexity:** O(V) (uses a queue)

**Visualization:**
- Highlights nodes and edges in the order of traversal.

**Interaction:**
- Users select the starting node.
- Animations display the BFS progression step-by-step.

---

## Dependencies
- **SFML Library:** Facilitates graphical visualization and event handling.

---

## To Execute

### Compilation (PowerShell)

1. **Compile the source files:**
   ```powershell
   g++ -O3 -c *.cpp -I<your-SFML-include-path>

Link the object files and build the executable:
   ```powershell
  g++ -O3 -o main-app *.o -L<your-SFML-lib-path> -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Run the Program (Bash)
  ```powershell
  export PATH=$PATH:<your-SFML-bin-path> ./main-app

