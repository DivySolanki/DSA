// Node.h

#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

#endif // NODE_H
