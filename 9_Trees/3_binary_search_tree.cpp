#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

/*
In Binary Search Tree
the (Left Node < Root < Right Node) always.

The left subtree and right subtree should also be a BST.

Ideally there won't be any duplicates but it can be integrated with modification in conditions.
*/

/*
Search in a binary search tree.
If node->data exists then return node else return NULL.
*/
Node* SearchBST(Node* root, int target) {
    while(root != NULL && root->data != target) {
        root = target > root->data ? root->right : root->left;
    }
    return root;
}

/*
Ceil in a BST

return the value of the node that is >= target.

EG: target = 10 then ceil = 10
    target = 11 then ceil = 12
*/
int CeilBST(Node* root, int target) {
    int ceil = -1;
    while(root != NULL) {
        if(root->data == target) {
            ceil = root->data;
            return ceil;
        }
        else if(root->data > target) {
            ceil = root->data;
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return ceil;
}

/*
Floor in a BST

return the value of the node that is greater but <= target.

EG: target = 10 then floor = 10
    target = 11 then floor = 10
*/
int FloorBST(Node* root, int target) {
    int floor = -1;
    while(root != NULL) {
        if(root->data == target) {
            floor = root->data;
            return floor;
        }
        else if(root->data > target) {
            root = root->left;
        }
        else {
            floor = root->data;
            root = root->right;
        }
    }
    return floor;
}

/*
Insert a node in a BST

There are multiple possible ways to insert a node in a BST.
Return the root node with any one method insertion.
*/
Node* InsertBST(Node* root, int val) {
    Node* cur = root;
    Node* node = new Node(val);

    while(true) {
        if(cur->data <= val) {
            if(cur->right != NULL) cur = cur->right;
            else {
                cur->right = node;
                break;
            }
        } else {
            if(cur->left != NULL) cur = cur->left;
            else {
                cur->left = node;
                break;
            }
        }
    }
    return root;
}

/*
Delete a node from the BST

Steps:
1. Search the node
2. Delete the node
*/
Node* findLastRight(Node* root) {
    if(root->right == NULL) {
        return root;
    } 
    return findLastRight(root->right);
}

Node* DeleteHelper(Node* root) {
    if(root->left == NULL) {
        return root->right;
    }
    else if(root->right == NULL) {
        return root->left;
    }
    Node* rightChild = root->right;
    Node* lastRight = findLastRight(root->left);
    lastRight->right = rightChild;
    return root->left;
}

Node* DeleteBST(Node* root, int val) {
    if(root == NULL) return NULL;
    if(root->data == val) {
        return DeleteHelper(root);
    }
    Node* dummy = root;
    while(root != NULL) {
        if(root->data > val) {
            if(root->left != NULL && root->left->data == val){
                root->left = DeleteHelper(root->left);
            } else {
                root = root->left;
            }
        } else {
            if(root->right != NULL && root->right->data == val){
                root->right = DeleteHelper(root->right);
            } else {
                root = root->right;
            }
        }
    }
    return dummy;
}

/*
Kth smallest element in BST

If k=3 then return the 3rd smallest element.

The property of the BST is that the inorder is always sorted.

Morris traversal will ṭake O(N) & O(1) complexity.
*/
void KthSmallestElement(Node* root, int &counter, int k, int &kSmallest) {
    if(!root || counter >= k) return;
    
    KthSmallestElement(root->left, counter, k, kSmallest);

    counter++;

    if(counter == k) {
        kSmallest = root->data;
        return;
    }

    KthSmallestElement(root->right, counter, k, kSmallest);
}

/*
Similarily KthLargestElement
*/
void KthLargestElement(Node *root, int &counter, int k, int &kLargest) {
    if(!root || counter >= k) return;

    KthLargestElement(root->right, counter, k, kLargest);

    counter++;

    if(counter == k) {
        kLargest = root->data;
        return;
    }

    KthLargestElement(root->left, counter, k, kLargest);
}

/*
Validate a BST.

Check if it is a valid BST or not.

Provide a range to a node and if it falls within the range then its a valid node for a BST.

The inital range will be [INT_MIN, INT_MAX]
*/
bool BSTHelper(Node* root, int &minRange, int &maxRange) {
    if(!root) return true;

    if(minRange >= root->data || maxRange <= root->data) return false;

    return BSTHelper(root->left, minRange, root->data) && BSTHelper(root->right, root->data, maxRange);
}

bool IsBSTValid(Node* root) {
    int minVal = INT_MIN;
    int maxVal = INT_MAX;

    return BSTHelper(root, minVal, maxVal);
}

/*
LCA in a BST

LCA is a Lowest Common ancestor.

Given the value of 2 nodes either both of them lie to the right or to the left

The point at which they diverge to lying left or right then that node is LCA.

Also if both of them don't lie to the right or to the left then that node is LCA as it will be one of the nodes.
*/
Node* LCAofBST(Node* root, int p, int q) {
    if(!root) return NULL;
    int cur  = root->data;

    if(cur > p && cur > q) return LCAofBST(root->left, p, q);

    if(cur < p && cur < q) return LCAofBST(root->right, p, q);

    return root;
}

/*
Construct a BST from preorder traversal.

Take a global upper bound value as INT_MAX and pass that value to the left of the root node while traversing the preorder, if the next value in the preorder is less than ub place or move to the right with previous upper bound.
*/
Node* helperBSTPre(vector<int> &preorder, int &i, int ub) {
    if(i == preorder.size() || preorder[i] > ub) return NULL;

    Node* root = new Node(preorder[i++]);
    root->left = helperBSTPre(preorder, i, root->data);
    root->right = helperBSTPre(preorder, i, ub);
    return root;
}

Node* constructBSTfromPre(vector<int> &preorder) {
    int i = 0;

    return helperBSTPre(preorder, i, INT_MAX);
}

/*
Inorder successor of a BST

Given the inorder of a BST find the successor of a given node in the inorder.
*/
Node* SuccessorBST(Node* root, Node* p) {
    Node* successor = NULL;

    while(root) {
        if(p->data >= root->data) {
            root = root->right;
        } else {
            successor = root;
            root = root->left;
        }
    }
    return successor;
}

/*
Inorder predecessor of a BST

Given the inorder of a BST find the predecessor of a given node in the inorder.
*/
Node* PredecessorBST(Node* root, Node* p) {
    Node* predecessor = NULL;

    while(root) {
        if(p->data <= root->data) {
            root = root->left;
        } else {
            predecessor = root;
            root = root->right;
        }
    }
    return predecessor;
}

/*
BST iterator 

Given the root of the BST design next() and hasnext() function.

next() returns the next node in the inorder of tree initially the pointer is at the non existential start.

hasnext() returns boolean vlaue if there is a next value to the pointer in inorder of tree.

storing the inorder in a vector uses space complexity of O(N)
instead using stack and only storing the height of the tree uses O(H)
*/
class BSTiterator {
    private: 
        stack<Node*> myStack;
        bool reverse = true;

    public:
        BSTiterator(Node* root, bool isReverse){
            reverse = isReverse;
            pushAll(root);
        }

        bool hasNext() {
            return !myStack.empty();
        }

        int next() {
            Node* curr = myStack.top();
            myStack.pop();
            if(reverse) pushAll(curr->left);
            else pushAll(curr->right);
            return curr->data;
        }

    private:
        // void pushAll(Node* node) {
        //     for(; node != NULL; myStack.push(node), node = node->left); // due to , in for loop myStack.push(node), node = node->left happens sequentially
        // }
        void pushAll(Node* node) {
            for(; node != NULL; ){
                myStack.push(node);
                if(reverse) node = node->right;
                else node = node->left;
            } 
        } // modification for 2 sum
};

/*
Two sum problem in BST

It makes the use of BSTiterator.
The only modification is that it also stores the before elements i.e. elements in descending order.

It is done to get the high value and the low value is already obtained from next

Once the low and high are obtained the solution becomes a simple 2 sum problem.
*/
bool isSumBST(Node* root, int k) {
    if(!root) return false;
    
    // next
    BSTiterator l(root, false);
    //before
    BSTiterator r(root, true);

    int i = l.next();
    int j = r.next();

    while(i<j) {
        if(i+j == k) return true;
        else if(i+j < k) i = l.next();
        else j = r.next();
    }
    return false;
}

/*
Recover a BST

The question states that there are two nodes in the BST which are swapped. Our job is to correct the BST.

Brute method: Do an inorder traversal of the BST and sort it.
Then parallely traverse the inorder and tree change where missmatch occurs.

Optimal method: While traversing inorder mark the first violation as first and its adjacent next node as middle.
Then continue to traverse till the last violation is found.

As there are two cases in which
1. first and last violation are adjacent
2. first and last violation are not adjacent

For the first case swap first and middle.
For the second case swap the first and last.
*/
void inorderHelper(Node* root, Node* &prev, Node* &first, Node* &middle, Node* &last) {
    if(root == NULL) return;

    inorderHelper(root->left, prev, first, middle, last);
    if(prev != NULL && (prev->data > root->data)) {
        // First violation
        if(first == NULL) {
            first = prev;
            middle = root;
        }
        // Last violation
        else {
            last = root;
        }
    }
    prev = root;
    inorderHelper(root->right, prev, first, middle, last);
}

void RecoverBST(Node* root) {
    Node* first = NULL;
    Node* middle = NULL;
    Node* last = NULL;

    Node* prev = new Node(INT_MIN);

    inorderHelper(root, prev, first, middle, last);

    if(first && last) {
        swap(first->data, last->data);
    } else {
        swap(first->data, middle->data);
    }

    delete prev;
}

/*
Hard and confusing yet understandable

Largest BST in a Binary tree.

Solution: create a class which stores the max, min and size of the BST.

The solution is bottom up thus use post order traversal.

For a node get the (Maximum from left let it be x) and (Minimum from right let it be y).

If x < node < y then the size of the BST is 1 + x + y.
*/
class NodeValue {
    public:
        int minValue, maxValue, maxSize;

        NodeValue(int minValue, int maxValue, int maxSize) {
            this->minValue = minValue;
            this->maxValue = maxValue;
            this->maxSize = maxSize;
        }
};

NodeValue largestBSTSubtreeHelper(Node* root) {
    if(!root) {
        // AS NULL the largest from the left will be INT_MAX and the smallest from the right will be INT_MIN
        return NodeValue(INT_MAX, INT_MIN, 0);
    }

    auto left = largestBSTSubtreeHelper(root->left);
    auto right = largestBSTSubtreeHelper(root->right);

    // Current node is greater than max left AND smaller than min in right.
    if(left.maxValue < root->data &&  root->data < right.minValue) {
        // It's a BST
        return NodeValue(
            min(root->data, left.minValue),
            max(root->data, right.maxValue),
            left.maxSize + right.maxSize + 1
        );
    }

    // Otherwise return [-inf, inf] so that the parents can't be valid BST.
    return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
}

int largestBSTSubtree(Node* root) {
    return largestBSTSubtreeHelper(root).maxSize;
}

int main() {

    // Level 1
    Node *root = new Node(8);

    // Level 2
    root->left = new Node(5);
    root->right = new Node(12);

    // Level 3
    root->left->left = new Node(4);
    root->left->right = new Node(7);
    root->right->left = new Node(10);
    root->right->right = new Node(14);

    // Level 4
    root->left->right->left = new Node(6);
    root->right->right->left = new Node(13);

    RecoverBST(root);

    cout << IsBSTValid(root);
    
    return 0;
}
