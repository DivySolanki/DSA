#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

// Preorder traversal
void preorder (struct Node* node) {
    if(node == NULL) return;

    cout << node->data << " ";
    preorder (node->left);
    preorder (node->right);
}

// Inorder traversal
void inorder (struct Node* node) {
    if(node == NULL) return;

    inorder (node->left);
    cout << node->data << " ";
    inorder (node->right);
}

// Postorder traversal
void postorder (struct Node* node) {
    if(node == NULL) return;

    postorder (node->left);
    postorder (node->right);
    cout << node->data << " ";
}

// Levelorder traversal
vector<int> levelOrder(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        for(int i=0; i<size; i++) {
            Node* node = q.front();
            q.pop();
            ans.push_back(node->data);
            if(node->left != NULL) q.push(node->left);
            if(node->right != NULL) q.push(node->right);
        }
    }
    return ans;
}

// preorder traversal (iterative)
vector<int> preOrder(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;
    stack<Node*> st;
    st.push(root);
    while(!st.empty()) {
        root = st.top();
        st.pop();
        ans.push_back(root->data);
        if(root->right != NULL) st.push(root->right);
        if(root->left != NULL) st.push(root->left);
    }
    return ans;
}

// inorder traversal (iterative)
vector<int> inOrder(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;
    stack<Node*> st;
    Node* node = root;
    while(true) {
        if(node != NULL) {
            st.push(node);
            node = node->left;
        } else {
            if(st.empty()) break;
            node = st.top();
            st.pop();
            ans.push_back(node->data);
            node = node->right;
        }
    }
    return ans;
}

// postorder traversal (iterative) using 2 stack
vector<int> postorder2Stack(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;
    stack<Node*> st1, st2;
    st1.push(root);
    while(!st1.empty()) {
        root = st1.top();
        st1.pop();
        st2.push(root);
        if(root->left != NULL) st1.push(root->left);
        if(root->right != NULL) st1.push(root->right);
    }
    while(!st2.empty()) {
        ans.push_back(st2.top()->data);
        st2.pop();
    }
    return ans;
}

// postorder traversal (iterative) using 1 stack
//Tricky
vector<int> postorder1Stack(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;
    Node* curr = root;
    stack<Node*> st;
    while(curr != NULL || !st.empty()) {
        if(curr != NULL) {
            st.push(curr);
            curr = curr->left;
        } else {
            Node* temp = st.top() -> right;
            if(temp == NULL) {
                temp = st.top();
                st.pop();
                ans.push_back(temp->data);
                while(!st.empty() && temp==st.top() -> right) {
                    temp = st.top();
                    st.pop();
                    ans.push_back(temp->data);
                }
            } else {
                curr = temp;
            }
        }
    }
    return ans;
}

// Preorder, Inorder & Postorder traversal in 1 go
vector<vector<int>> AllTraversals(Node* root) {
    vector<vector<int>> ans;
    stack<pair<Node*, int>> st;
    st.push({root, 1});
    vector<int> pre, in, post;
    if(root == NULL) return ans;
    while(!st.empty()) {
        auto it = st.top();
        st.pop();

        if(it.second == 1) {
            pre.push_back(it.first->data);
            it.second++;
            st.push(it);

            if(it.first->left != NULL) {
                st.push({it.first->left, 1});
            }
        }
        else if(it.second == 2) {
            in.push_back(it.first->data);
            it.second++;
            st.push(it);

            if(it.first->right != NULL) {
                st.push({it.first->right, 1});
            }
        }
        else {
            post.push_back(it.first->data);
        }
    }
    ans.push_back(pre);
    ans.push_back(in);
    ans.push_back(post);
    return ans;
}

int main() {
    // Level 1 (root)
    Node* root = new Node(1);

    // Level 2
    root->left = new Node(2);
    root->right = new Node(3);

    // Level 3
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    vector<int> res = levelOrder(root);

    for(auto it: res) {
        cout << it << " ";
    }
    // for(int i = 0; i < res.size(); i++) {
    //     for (int j = 0; j < res[0].size(); j++)
    //     {
    //         cout << res[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}