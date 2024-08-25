#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

// Maximum depth of Binary Tree
int maxDepth(Node* root) {
    if(root == NULL) return 0;

    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);

    return 1 + max(lh, rh);
}

// Maximum depth of Binary Tree using Levelorder traversal
int MaxDepthlevelOrder(Node* root) {
    int level = 0;
    if(root == NULL) return level;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        level++;
        for(int i=0; i<size; i++) {
            Node* node = q.front();
            q.pop();
            if(node->left != NULL) {
                q.push(node->left);
            }
            if(node->right != NULL) {
                q.push(node->right);
            }
        }
    }
    return level;
}

/* 
Check for balanced binary tree
A Balanced Binary tree is a tree in which for every node 
height(left) - height(right) <= 1;
*/
// Sub function
int dfsHeight(Node* root) {
    if(root == NULL) return 0;

    int leftHeight = dfsHeight(root->left);
    if(leftHeight == -1) return -1;

    int rightHeight = dfsHeight(root->right);
    if(rightHeight == -1) return -1;

    if(abs(leftHeight - rightHeight) > 1) return -1;
    return max(leftHeight, rightHeight) + 1;
}

bool balancedBinaryTree(Node* root) {
    return dfsHeight(root) != -1;
}

/*
Diameter of a Binary Tree
Conditions
- longest path between 2 nodes
- path does not need to pass via root
*/
int height(Node* root, int& diameter) {
    if(root == NULL) return 0;

    int lh = height(root->left, diameter);
    int rh = height(root->right, diameter);
    diameter = max(diameter, lh+rh);
    return 1 + max(lh, rh);
}

int diameterOfBinaryTree(Node* root) {
    int diameter = INT_MIN;
    height(root, diameter);
    return diameter;
}

/*
Maximum Path Sum of Binary Tree
Adding the weights of the nodes adn return the maximum sum path.
*/
int pathSum(Node* root, int& maxi) {
    if(root == NULL) return 0;

    int lSum = max(0, pathSum(root->left, maxi));
    int rSum = max(0, pathSum(root->right, maxi));
    maxi = max(maxi, lSum + rSum + root->data);
    return root->data + max(lSum, rSum);
}

int maximumPathSumBinaryTree(Node* root) {
    int maxi = INT_MIN;
    pathSum(root, maxi);
    return maxi;
}

/*
Identical Tree or not

Simple way to solve perform any traversal technique on both the trees.
If Similar then true else false.
*/
bool isSimilar(Node* p, Node* q) {
    if(p==NULL || q==NULL) return (p==q);

    return (p->data == q->data) && isSimilar(p->left, q->left)
    && isSimilar(p->right, q->right);
}

/*
Zig-zag traversal
Right -> left then left -> right or vice versa

true means l to r
false means r to l
*/
vector<vector<int>> zigZagTraversal(Node* root) {
    vector<vector<int>> ans;
    if(root == NULL) return ans;
    queue<Node* > nodesQueue;
    nodesQueue.push(root);
    bool leftToRight = true;

    while(!nodesQueue.empty()) {
        int size = nodesQueue.size();
        vector<int> row(size);

        for(int i = 0; i < size; i++) {
            Node* node = nodesQueue.front();
            nodesQueue.pop();

            int index = (leftToRight) ? i : (size - 1 - i);

            row[index] = node->data;

            if(node->left) {
                nodesQueue.push(node->left);
            }
            if(node->right) {
                nodesQueue.push(node->right);
            }
        }
        leftToRight = !leftToRight;
        ans.push_back(row);
    }
    return ans;
}

/*
Boundary Traversal (Anti clockwise)

Traversing manner:
1. Left Boundary excluding leaf
2. Leaf nodes.
3. Right Boundary reversed excluding leaf
*/
bool isLeaf(Node* node) {
    if(node->left == NULL && node->right == NULL) return true;
    return false;
}

void addLeftBoundary(Node* root, vector<int> &res) {
    Node* curr = root->left;
    while(curr) {
        if(!isLeaf(curr)) res.push_back(curr->data);
        if(curr->left) curr = curr->left;
        else curr = curr->right;
    }
}

void addRightBoundary(Node* root, vector<int> &res) {
    Node* curr = root->right;
    vector<int> temp;
    while(curr) {
        if(!isLeaf(curr)) temp.push_back(curr->data);
        if(curr->right) curr = curr->right;
        else curr = curr->left;
    }
    for(int i = temp.size()-1; i>=0; --i) {
        res.push_back(temp[i]);
    }
}

void addLeaves(Node* root, vector<int> &res) {
    if(!root) return;
    if(isLeaf(root)) {
        res.push_back(root->data);
        return;
    }
    addLeaves(root->left, res);
    addLeaves(root->right, res);
}

vector<int> printBoundry(Node* root) {
    vector<int> res;
    if(root == NULL) return res;
    if(!isLeaf(root)) res.push_back(root->data);
    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);
    return res;
}

/*
Tricky
col Order Traversal

Consider an imaginary x axis which represents the col position of the element.
Eg: root is at 0 then moving to its left child the vectical will decrease by 1.
When moving to its right child the vectical will increase by 1.

Also the detail of the level of the tree needs to be considered.

In a nutshell,
Moving left: col -1 and level +1
Moving right: col +1 and level +1

It uses 2 Data structures.
1. Queue: In which the node, col and level is stored.
2. Map: In which the col, level and Multiset of nodes is stored.
*/
vector<vector<int>> colTraversal(Node* root) {
    vector<vector<int>> ans;
    if(!root) return ans;
    map<int, map<int, multiset<int>>> nodes;
    queue<pair<Node* ,pair<int, int>>> todo;
    todo.push({root, {0,0}});

    while(!todo.empty()) {
        auto p = todo.front();
        todo.pop();
        Node* node = p.first; // node
        int x = p.second.first; // col
        int y = p.second.second; // level
        nodes[x][y].insert(node->data);
        if(node->left) {
            todo.push({node->left, {x-1, y+1}});
        }
        if(node->right) {
            todo.push({node->right, {x+1, y+1}});
        }
    }

    for(auto p: nodes) {
        vector<int> col;
        for(auto q: p.second) {
            col.insert(
                col.end(),
                q.second.begin(), // multiset start
                q.second.end() // multiset end
            );
        }
        ans.push_back(col);
    }

    return ans;
}

/*
Top View of Binary Tree

Similar to the above problem just cover the verctial from -min to +max
*/
vector<int> topView(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;

    map<int, int> mpp;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while(!q.empty()) {
        auto curr = q.front();
        q.pop();
        Node* node = curr.first;
        int vertical = curr.second;
        if(mpp.find(vertical) == mpp.end()) {
            mpp[vertical] = node->data;
        }
        if(node->left) q.push({node->left, vertical-1});
        if(node->right) q.push({node->right, vertical+1});
    }

    for(auto it: mpp) {
        ans.push_back(it.second);
    }

    return ans;
}

/*
Bottom view of Binary tree

It is totally similar to the above problem, just don't check for the condition if the key for a vertical already exists.
*/
vector<int> bottomView(Node* root) {
    vector<int> ans;
    if(root == NULL) return ans;

    map<int, int> mpp;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while(!q.empty()) {
        auto curr = q.front();
        q.pop();
        Node* node = curr.first;
        int vertical = curr.second;
        
        // The only change
        mpp[vertical] = node->data;

        if(node->left) q.push({node->left, vertical-1});
        if(node->right) q.push({node->right, vertical+1});
    }

    for(auto it: mpp) {
        ans.push_back(it.second);
    }

    return ans;
}

/*
Right View of binary tree

For the Right view consider using recursive traversal.
Eg: Reverse Preorder (Root Right Left)
As in the right view the first node is the visible node when moving right to left.
*/
void rightRecursion(Node* root, int level, vector<int> &ans) {
    if(root == NULL) return;
    if(ans.size() == level) ans.push_back(root->data);
    rightRecursion(root->right, level+1, ans);
    rightRecursion(root->left, level+1, ans);
}

vector<int> rightView(Node* root) {
    vector<int> ans;
    rightRecursion(root, 0, ans);
    return ans;
}

/*
Left View of binary tree

Similar to right view
Eg: Preorder (Root Left Right)
As in the left view the first node is the visible node when moving left to right.
*/
void leftRecursion(Node* root, int level, vector<int> &ans) {
    if(root == NULL) return;
    if(ans.size() == level) ans.push_back(root->data);
    leftRecursion(root->left, level+1, ans);
    leftRecursion(root->right, level+1, ans);
}

vector<int> leftView(Node* root) {
    vector<int> ans;
    leftRecursion(root, 0, ans);
    return ans;
}

/*
Check for symmetrical binary tree

i.e. that it  forms a mirror of itself around the centre or not

Simply check that the left subtree and right sub tree are identical or not
By performing Root Left Right on the left
and Root Right Left on the right part simlutaneously.
*/
bool isSymmetricalHelp(Node* left, Node* right) {
    if(left==NULL || right==NULL)
        return left==right;

    if(left->data != right->data) return false;

    return isSymmetricalHelp(left->left, right->right) && isSymmetricalHelp(left->right, right->left);
}

bool isSymmetric(Node* root) {
    return root==NULL || isSymmetricalHelp(root->left, root->right);
}

/*
Print root to node path in a binary tree
*/
bool getPath(Node* root, vector<int> &arr, int target) {
    if(!root) {
        return false;
    }
    arr.push_back(root->data);

    if(root->data == target) 
        return true;

    if(getPath(root->left, arr, target) || getPath(root->right, arr, target)) return true;

    arr.pop_back();
    return false;
}

vector<int> nodePath(Node* root, int target) {
    vector<int> path;
    if(!root) return path;
    getPath(root, path, target);
    return path;
}

/*
Lowest Common ancestor in binary tree

i.e. finding the common ancestor to both the node at the lowest level down.
*/
Node* lcaHelper(Node* root, int val1, int val2) {
    if(!root) return NULL;

    if(root->data == val1 || root->data == val2) {
        return root;
    }

    Node* left = lcaHelper(root->left, val1, val2);
    Node* right = lcaHelper(root->right, val1, val2);

    if(left == NULL) {
        return right;
    }
    else if(right == NULL) {
        return left;
    }
    else {
        return root;
    }
}

int lcaFinder(Node* root, int val1, int val2) {
    Node* temp = lcaHelper(root, val1, val2);
    return temp->data;
}

/*
(Tricky yet do able)
Maximum width of a Binary Tree

i.e. maximum no of nodes in a level between any two nodes (inclusive) also include the imaginary nodes that could be present.

Consider the following binary tree
            i
           / \
      2*i+1   2*i+2

The above are the indexes of an individual node. 
To avoid overflow consider the level indexes and subtract them from minimum on the level.

The length will be max - min + 1 for a level.
*/
int binaryTreeWidth(Node* root) {
    if(!root) return 0;
    int ans = 0;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while(!q.empty()) {
        int size = q.size();
        int mmin = q.front().second;
        int first, last;
        for(int i = 0; i < size; i++) {
            int curr_id = q.front().second-mmin;
            Node* node = q.front().first;
            q.pop();
            if(i==0) first = curr_id;
            if(i==size-1) last = curr_id;
            if(node->left)
                q.push({node->left, curr_id*2+1});
            if(node->right)
                q.push({node->right, curr_id*2+2});
        }
        ans = max(ans, last-first+1);
    }
    return ans;
}

/*
(Hard to understand)
Children Sum Property in Binary Tree
i.e. the value of parent should be equal to the value of left child and the right child.
node->data = node->left->data + node->right->data

If this does not holds then we can increment the value of parent by one multiple times.
*/
void childrenSum(Node* root) {
    if(!root) return;
    int child = 0;
    if(root->left) {
        child += root->left->data;
    }
    if(root->right) {
        child += root->right->data;
    }

    if(child >= root->data) {
        root->data = child; // If root is smaller than assign child's value
    } else {
        // Else propagate the root value to children
        if(root->left) root->left->data = root->data;
        if(root->right) root->right->data = root->data;
    }

    childrenSum(root->left);
    childrenSum(root->right);

    int tot = 0;
    if(root->left) tot += root->left->data;
    if(root->right) tot += root->right->data;
    if(root->left || root->right) root->data = tot;
}

/*
Nodes at a distance K from a given target node.

Return those value of nodes in any order.

Note: When you have to traverse back use a map to store the parent node

Steps to solve:
1. Have parent pointers of the node.
2. Radially move 1 distance to left, right and parent of the node.
3. As soon as the distance is k take the nodes from the visited nodes.
*/
void markParent(Node* root, unordered_map<Node*, Node*> &parent_track) {
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* cur = q.front();
        q.pop();
        if(cur->left) {
            parent_track[cur->left] = cur;
            q.push(cur->left);
        }
        if(cur->right) {
            parent_track[cur->right] = cur;
            q.push(cur->right);
        }
    }   
}

vector<int> distanceK(Node* root, Node* target, int k) {
    unordered_map<Node*, Node*> parent_track;
    markParent(root, parent_track);

    unordered_map<Node*, bool> visited;
    queue<Node*> q;
    q.push(target);
    visited[target] = true;
    int curr_level = 0;
    while(!q.empty()) {
        int size = q.size();
        if(curr_level == k) break;
        curr_level++;
        for(int i=0; i<size; i++) {
            Node* current = q.front();
            q.pop();
            if(current->left && !visited[current->left]) {
                q.push(current->left);
                visited[current->left] = true;
            }
            if(current->right && !visited[current->right]) {
                q.push(current->right);
                visited[current->right] = true;
            }
            if(parent_track[current] && !visited[parent_track[current]]) {
                q.push(parent_track[current]);
                visited[parent_track[current]] = true;
            }
        }
    }
    vector<int> result;
    while(!q.empty()) {
        Node* curr = q.front();
        q.pop();
        result.push_back(curr->data);
    }
    return result;
}

/*
Count total nodes in a complete binary tree.

Refer the definition of complete binary tree

The formula for total nodes in a complete binary tree is 2^(height of tree) - 1
*/
int findHeight(Node* node, string direction) {
    int height = 0;
    if(direction == "left") {
        while(node) {
            height++;
            node = node->left;
        }
    } else {
        while(node) {
            height++;
            node = node->right;
        }
    }
    return height;
}

int countNodes(Node* root) {
    if(root == NULL) return 0;

    int lh = findHeight(root, "left");
    int rh = findHeight(root, "right");

    if(lh == rh) return int(pow(2.0, float(lh))) - 1;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

/*
Lesson Notes: Requirements needed to construct a unique Binary tree

1 - With given preorder and postorder; many binary trees can be constructed.

2 - For a binary tree to be unique there must be inorder with pre or post as knowing the root is not important but what lies to its left and right is important.
*/

/*
Contruct Binary tree from inorder and preorder
*/
Node* helperBinaryTree(vector<int> &preorder, int preStart, int preEnd, vector<int> &inorder, int inStart, int inEnd, map<int,int> &inMap) {

    if(preStart > preEnd || inStart > inEnd) return NULL;

    Node* root = new Node(preorder[preStart]);

    int inRoot = inMap[root->data];
    int numsLeft = inRoot - inStart;

    root->left = helperBinaryTree(
        preorder, preStart+1, preStart+numsLeft, inorder, inStart, inRoot-1, inMap
    );

    root->right = helperBinaryTree(
        preorder, preStart+numsLeft+1, preEnd, inorder, inRoot+1, inEnd, inMap
    );

    return root;
}

Node* constructBinaryTree(vector<int> preorder, vector<int> inorder) {
    map<int, int> inMap;

    for(int i=0; i<inorder.size(); i++){
        inMap[inorder[i]] = i;
    }

    Node* root = helperBinaryTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);

    return root;
}

/*
Contruct Binary tree from inorder and postorder
*/
Node* helperBinaryTree2(vector<int> &postorder, int postStart, int postEnd, vector<int> &inorder, int inStart, int inEnd, map<int,int> &inMap) {

    if(postStart > postEnd || inStart > inEnd) return NULL;

    Node* root = new Node(postorder[postEnd]);

    int inRoot = inMap[root->data];
    int numsLeft = inRoot - inStart;

    root->left = helperBinaryTree2(
        postorder, postStart, postStart+numsLeft-1, inorder, inStart, inRoot-1, inMap
    );

    root->right = helperBinaryTree2(
        postorder, postStart+numsLeft, postEnd-1, inorder, inRoot+1, inEnd, inMap
    );

    return root;
}

Node* constructBinaryTree2(vector<int> postorder, vector<int> inorder) {
    map<int, int> inMap;

    for(int i=0; i<inorder.size(); i++){
        inMap[inorder[i]] = i;
    }

    Node* root = helperBinaryTree2(postorder, 0, postorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);

    return root;
}

/*
Serialize and De serialize Binary Tree

Serialize and De serialize are the functions written by us. 

When we pass a root of the tree to Serialize it returns a string.
and when we pass the returned string to De serialize it returns the root of the binary tree constructed from the string.
*/
string SerializeBinaryTree(Node* root) {
    if(!root) return " ";

    queue<Node* > q;
    string str = "";
    q.push(root);
    while(!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if(curr==NULL) str.append("-1 ");
        else str.append(to_string(curr->data)+" ");
        if(curr != NULL) {
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return str;
}

Node* DeserializeBinaryTree(string data) {
    if(data.size() == 0) return NULL;
    
    stringstream s(data);
    string str;
    s >> str;
    Node* root = new Node(stoi(str));
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* node = q.front();
        q.pop();

        s >> str;
        if(str == "-1") {
            node->left = NULL;
        } else {
            Node* leftNode = new Node(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }

        s >> str;
        if(str == "-1") {
            node->right = NULL;
        } else {
            Node* rightNode = new Node(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

/*
(Important!)
Morris Traversal for Inorder and Preorder

It takes time complexity of O(N) and space complexity of O(1) while other traversal techniques like recursive and stack takes space complexity of O(N)

It uses a concept of Threaded Binary Tree

The pattern is to go from the last node of a sub tree back to root node
*/
vector<int> morrisInorder(Node* root) {
    vector<int> inorder;
    Node* curr = root;
    while(curr!=NULL) {
        if(curr->left == NULL) {
            inorder.push_back(curr->data);
            curr = curr->right;
        }
        else {
            Node* prev = curr->left;
            while(prev->right && prev->right!=curr) {
                prev = prev->right;
            }

            if(prev->right == NULL) {
                prev->right = curr;
                curr = curr->left;
            }
            else {
                prev->right = NULL;
                inorder.push_back(curr->data);
                curr = curr->right;
            }
        }
    }
    return inorder;
}

vector<int> morrisPreorder(Node* root) {
    vector<int> preorder;
    Node* curr = root;
    while(curr!=NULL) {
        if(curr->left == NULL) {
            preorder.push_back(curr->data);
            curr = curr->right;
        }
        else {
            Node* prev = curr->left;
            while(prev->right && prev->right!=curr) {
                prev = prev->right;
            }

            if(prev->right == NULL) {
                prev->right = curr;
                preorder.push_back(curr->data);
                curr = curr->left;
            }
            else {
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }
    return preorder;
}

/*
Flatten a binary tree to linked list

Get the preorder of the given tree and rearrange the tree to represent a linked list depicting the preorder.

Note: the left will always point to NULL.

There is an iterative and recursive solution which takes time complexity of O(N) and space complexity of O(N)
Solution: https://takeuforward.org/data-structure/flatten-binary-tree-to-linked-list/

The same problem can be also done using morris traversal. It takes time complexity of O(N) and space complexity of O(1)

Below is the code for it.
*/
void FlattenBinaryTree(Node* root) {
    Node* curr = root;
    
    while(curr != NULL) {
        if(curr->left != NULL) {
            Node* prev = curr->left;
            while(prev->right != NULL) {
                prev = prev->right;
            }
            prev->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }
        curr = curr->right;
    }
}


int main() {
    // Level 1 (root)
    Node* root = new Node(15);

    // Level 2
    root->left = new Node(40);
    root->right = new Node(62);

    // Level 3
    root->right->left = new Node(10);
    root->right->right = new Node(20);

    FlattenBinaryTree(root);
    vector<int> res = morrisPreorder(root);

    for(auto it: res) {

        cout << it << " ";

        // for(auto q: it) {
        //     cout << q << " ";
        // }
    }

    return 0;
}