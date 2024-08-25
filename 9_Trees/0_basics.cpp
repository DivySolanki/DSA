#include <bits/stdc++.h>
using namespace std;

/*
Trees 

1. Full Binary Tree
The tree contains either 0 or 2 children nodes

2. Complete Binary Tree
All levels are completely filled except the last level.
The last level has all nodes m left as possible.

3. Perfect Binary Tree
All leaf nodes are at the same level.

4. Balanced Binary Tree
Height of tree at max log(N) where N is the number of nodes

5. Degenerate Tree
All the nodes are skewed.
*/

// In C, you need to use the struct keyword when declaring a variable of a structure type because struct and typedef are different constructs.

// In C++, the struct keyword is not strictly necessary when declaring variables of a structure type because struct in C++ is more like a class with public members by default.

// The above comments are talking about the struct Node *left; & struct Node *right; lines.

// Declaration of tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    // Constructor
    Node (int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

int main() {
    return 0;
}

