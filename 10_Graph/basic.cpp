#include <bits/stdc++.h>
using namespace std;

/*
Components of a graph.
1. Nodes
2. Edges

Types of edges
1. Weighted Edge
2. Unweighted Edge

Types of graphs
1. Directed Graph
2. Undirected Graph

Cycle in a graph: When there is a path in which the node is itself the starting point and ending point.

Path of a graph: When a node is reachable involving adjacent edges. Then the traersal is called a path.
A node cannot appear twice in a path.
*/

/*
The input will always be given as n and m where n is the number of nodes in the graph and m is the number of edges.

Representation of a graph in C++
1. Matrix
2. List

1. Matrix
It is also called as adjacency matrix.
It is of n+1 * n+1 size where there is an edge between say x and y mark adj[x][y] = 1 else adj[x][y] = 0.

Space taken n*n and costly

int main() {
    int n, m;
    cin >> n >> m;
    int adj[n+1][n+1];
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    return 0;
}

2. List
It is also called as adjacency list.
It uses vector<int> adj[n+1];
That is every element of adj will contain a vector.
The space taken is 2 * edges.

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> adj[n+1];
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        // If it is a directed graph then comment the below line.
        adj[v].push_back(u);
    }
    return 0;
}

If the edges have weight wt then the modifications in the code are
For matrix
    adj[u][v] = wt; 

For list
    vector<pair<int, int>> adj[n+1];

    //insertion
    adj[u].push_back({v, wt});
*/

/*
Connect Components

If there are varioud components in a graph and they are not connected to each other then too they are considered as a single graph.

Traversal from a node to cannot cover the whole graph.

To make it possible to traverse the entire graph use a visited array.
where the array length is the number of nodes.
Initially all the elements of the array are 0.

// Traversal
for (int i = 0; i < n; i++) {
    if (!visited[i]) {
        traverse(i);
    }
}
*/

