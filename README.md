# ADS GROUP PROJECT
## PROJECT NAME: STUDENT ID SEARCH

| NAME | ID |
|------|-----------|
|FARISYA ADREA BINTI MOHAMMAD AMIN|22011796|
|NURIN EMELIN BINTI MARHISYAM|24006706|
|MUHAMMAD AFIQ DANIAL BIN DALI|24006309|
|AHMAD AZRI BIN IBRAHIM|24006756|
|ARIQ DANISH BIN NOR RAZAK|24006796|
|MUHAMMAD LUQMAN HAKIM BIN MOHAMAD 'ASRI|24000087|

Project Overviews

1. Baseline Approach (Unsorted)
Data Structure: `std::vector` (Unsorted). New students are added to the end.
Search Algorithm:Linear Search. Checks every student one by one.
Complexity: `O(n)`.
Verdict: Simple to implement, but very slow for large databases.

2. Optimized Approach (Sorted Array)
Data Structure: `std::vector` (Sorted). Maintained using Ordered Insertion.
Search Algorithm: Binary Search. Intelligently discards half the data at each step.
Complexity: `O(log n)` for search.
Verdict:** Extremely fast search, ideal for read-heavy systems.

3. Alternative Optimized Approach (BST)
Data Structure: Binary Search Tree (BST). Students are stored in a linked tree structure.
Search Algorithm: BST Search. Similar logic to Binary Search but using pointers.
Complexity: `O(log n)` on average.
Verdict: Excellent for both searching and dynamic insertion.

-----------------------------------------------------------------------------------------------

How to Compile and Run

This program is written in C++. You will need a compiler like `g++`.

1. Run the Baseline Version

`cd Project`
`g++ baseline1.cpp`
`./a.out`

2. Run the Optimized Sorted Array Version

`cd Project`
`g++ optimized1.cpp`
`./a.out`

3. Run the BST Version

`cd Project`
`g++ optimized_bst.cpp`
`./a.out`
