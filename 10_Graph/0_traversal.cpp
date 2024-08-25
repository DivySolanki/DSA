#include <bits/stdc++.h>
using namespace std;

/*
Breath First Search (BFS) of a graph

The 0th level of the graph will always have a single element.

Kind of similar to Level order traversal.

It uses visited array, queue and ans vector.
Thus space complexity is O(3N) ~ O(N).
The time complexity is O(N) + O(2E)
*/
vector<int> bfsGraph(int V, vector<int> adj[]) {
    int vis[V] = {0};
    vis[0] = 1;
    queue<int> q;
    q.push(0);
    vector<int> bfs;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        bfs.push_back(node);
        
        for(auto it: adj[node]) {
            if(!vis[it]) {
                vis[it] = 1;
                q.push(it);
            }
        }
    }
    return bfs;
}

/*
Depth First Search of a graph.

In this traversal we go to the depth of a path first.
Recursion is used.

The space complexity is O(N) + O(N) + O(N) for visiting n nodes, storing visited nodes, and recursion stack space in worst case.
The time complexity is O(N) + O(2E) as calling the function for n nodes and the internal function for summation of degree i.e. 2E
*/
void dfsHelper(int node, vector<int> adj[], int vis[], vector<int> &dfs) {
    vis[node] = 1;
    dfs.push_back(node);
    for(auto it: adj[node]) {
        if(!vis[it]) {
            dfsHelper(it, adj, vis, dfs);
        }
    }
}

vector<int> dfsGraph(int V, vector<int> adj[]) {
    vector<int> dfs;
    int vis[V] = {0};
    int start = 0;

    dfsHelper(start, adj, vis, dfs);

    return dfs;
}

int main() {
    return 0;
}

