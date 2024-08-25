#include<bits/stdc++.h>
using namespace std;

/*
Containers

1. Pairs

2. Vectors (Singly linked list is maintained)
push_back, emplace_back, push_front, emplace_front
erase, insert, size, pop_front ,pop_back, swap, clear, empty

3. List (Doubly linked list is maintained)
push_back, emplace_back, push_front, emplace_front
erase, insert, size, swap, clear, empty

4. Deque
erase, insert, size, pop_front ,pop_back, swap, clear, empty

5. Stack (No indexing) (LIFO)
push, pop, emplace, top, size, empty

6. Queue (FIFO)
front, back, push, emplace, top, size, empty

7. Priority Queue (Tree is maintained)
simiral functions to queue
Min Heap, Max Heap are the types of PQ

8. Set (Tree is maintained)
Stores everything in the sorted order and Unique
find, count

9. Multi Set 
Stores everything in the sorted order and not Unique
find, erase

10. Unordered Set
Stores everything that is Unique and no order

11. Map (Similar to Dictionary in python)
Stores everything in the sorted order of key and Unique

12. Multi Map
No unique key constrain

13. Unordered Map
Unique keys and not in sorted order of keys

Iterators
begin, end, rend, rbegin, back

Algorithms

1. Sort

2. __builtin_popcount(), __builtin_popcountll() (for long long)
returns set bits

3. next_permutation (but start from sorted order)

4. max_element
returns the pointer

5. min_element
returns the pointer

*/

// void paris() {
//     pair<int, int> p = {1, 2};
//     pair<int, pair<int, int>> d = {1, {1, 2}};
//     pair<int, int> arr[] = {{1, 2}, {2, 4}, {6,8}};
//     cout << p.first << " " << p.second;
// }

void find_largest_number_smaller_than_X(int X) {
    int A[] = {1, 4, 4, 9, 9, 9, 10, 11};
    int getArrayLength = sizeof(A) / sizeof(int);
    int ind = lower_bound(A, A+getArrayLength, X) - A;
    ind--;
    if(ind>=0 && A[ind]==X) cout << A[ind];
    else cout << -1;
}

int main() {
    find_largest_number_smaller_than_X(12);
    return 0;
}