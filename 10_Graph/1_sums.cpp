#include <bits/stdc++.h>
using namespace std;

void dfsHelper(int node, vector<int> adj[], int vis[]) {
    vis[node] = 1;
    for(auto it: adj[node]) {
        if(!vis[it]) {
            dfsHelper(it, adj, vis);
        }
    }
}

/*
Number of provinces in the graph

In simple terms, count the number of components in the graph.

For this problem make use of dfs or bfs traversal.
*/
int countComponents(int V, vector<int> adj[]) {

    /*
    Code to convert matrix to list
    vector<int> adj[n];

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(matrix[i][j] == 1 && i != j) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    */
    int cnt = 0;
    int vis[V] = {0};
    for(int i=0; i<V; i++) {
        if(!vis[i]) {
            cnt++;
            dfsHelper(i, adj, vis);
        }
    }
    return cnt;
}

/*
Number of Islands.

Given a matrix of n*m find the no. of islands in it i.e. the number of connected components.

The matrix will contain 0 and 1. 
1 means land and 0 means water.

In this problem we don't compute the adj list instead we use the matrix only.
*/
void bfs (int row, int col, vector<vector<int>> &vis, vector<vector<int>> &grid) {
    vis[row][col] = 1;
    queue<pair<int, int>> q;
    q.push({row, col});

    int n = grid.size();
    int m = grid[0].size();

    while(!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // traversing the neighbors
        for(int delrow = -1; delrow <= 1; delrow++) {
            for(int delcol = -1; delcol <= 1; delcol++) {
                int nrow = row + delrow;
                int ncol = col + delcol;

                if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol] && grid[nrow][ncol]) {
                    vis[nrow][ncol] = 1;
                    q.push({nrow, ncol});
                }
            }
        }
    }
}

int numIslands(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> vis(n, vector<int>(m, 0));
    int cnt = 0;
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < m; col++) {
            if(!vis[row][col] && grid[row][col]) {
                cnt++;
                bfs(row, col, vis, grid);
            }
        }
    }
    return cnt;
}

/*
Flood Fill Algorithm

Given a matrix and a row and column number. 
Flood fill the neighboring cells (up down left right) who has the same initial color with the new color provided.
Repeat the process for neighboring cells until above condition fails.
*/
void floodDfs(int row, int col, vector<vector<int>> &ans, vector<vector<int>> &image, int newColor,int initColor, int delRow[], int delCol[]) {
    ans[row][col] = newColor;
    int n = image.size();
    int m = image[0].size();
    for(int i=0; i<4; i++) {
        int nrow = row + delRow[i];
        int ncol = col + delCol[i];

        if(nrow >=0 && nrow < n && ncol >= 0 && ncol < m && image[nrow][ncol] == initColor && ans[nrow][ncol] != newColor) {
            floodDfs(nrow, ncol, ans, image, newColor, initColor, delRow, delCol);
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
    vector<vector<int>> ans = image;
    int initColor = image[sr][sc];

    int delRow[] = {-1, 0, 1, 0};
    int delCol[] = {0, 1, 0, -1};
    floodDfs(sr, sc, ans, image, newColor, initColor, delRow, delCol);
    return ans;
}

/*
(Kind of similar to the above problem)
Rotten Oranges

Given a matrix it contains rotten, fresh and empty blocks in the cell of the matrix.

2 represents rotten orange.
1 represents fresh orange.
0 represents empty compartment.

A rotten orange can spoil only the cells located to its (top down left and right) part.

We have to find the number of unit time required for all oranges to get rotten. If there is still a fresh orange at the end then return -1.

For say the 1 rotten orange spoils the top and bottom part then time = 1.
In the second iteration those top and bottom will spoil their neighbors and so on.

Note: There can also be multiple rotten orange in the initial matrix.
*/
int rottenOranges(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    int vis[n][m] = {0};
    int cntFresh = 0;

    queue<pair<pair<int, int>, int>> q;

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(grid[i][j] == 2) {
                vis[i][j] = 2;
                q.push({{i, j}, 0});
            } else {
                vis[i][j] = 0;
            }

            if(grid[i][j] == 1) {
                cntFresh++;
            }
        }
    }   

    int delRow[] = {-1, 0, 1, 0};
    int delCol[] = {0 ,1, 0, -1};

    int tm = 0;
    int cnt = 0;
    while(!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int t = q.front().second;
        q.pop();
        tm = max(t, tm);

        for(int i=0; i<4; i++) {
            int nrow = r + delRow[i];
            int ncol = c + delCol[i];

            if( nrow >= 0 && nrow < n 
                && ncol >= 0 && ncol < m
                && grid[nrow][ncol] == 1 
                && vis[nrow][ncol] != 2) {
                    q.push({{nrow, ncol}, t + 1});
                    vis[nrow][ncol] = 2;
                    cnt++;
                }
        }
    }

    if(cnt != cntFresh) return -1;

    return tm;
}

/*
Detecting a cycle in undirected graph.

It uses BFS algorithm.

The graph also has connected components.

In the queue we'll store node and its parent.

If the node's adjacent node is already visited and its parent is not equal to adjacent node.
i.e. In the adjacency list of a node there is one more element than the parent which is already visited.
This means that its the point of convergence of two paths thus cycle.
*/
bool checkCycleBFS(int src, vector<int> adj[], int vis[]) {
    vis[src] = 1;
    queue<pair<int, int>> q;
    q.push({src, -1});

    while(!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for(auto adjNode: adj[node]) {
            if(!vis[adjNode]) {
                vis[adjNode] = 1;
                q.push({adjNode, node});
            }
            else if(parent != adjNode) {
                return true;
            }
        }
    }
    return false;
}

bool detectCycleBFS(int V, vector<int> adj[]) {
    int vis[V] = {0};

    for(int i=0; i<V; i++) {
        if(!vis[i]) {
            if(checkCycleBFS(i, adj, vis)) return true;
        }
    }
    return false;
}

/*
Detect a cycle in an undirected graph
using DFS.

Similar to the above problem.
*/
bool checkCycleDFS(int node, int parent, vector<int> adj[], int vis[]) {
    vis[node] = 1;

    for(auto adjNode: adj[node]) {
        if(!vis[adjNode]) {
            if(checkCycleDFS(adjNode, node, adj, vis)) return true;
        }
        else if(parent != adjNode) {
            return true;
        }
    }
    return false;
}

bool detectCycleDFS(int V, vector<int> adj[]) {
    int vis[V] = {0};

    for(int i=0; i<V; i++) {
        if(!vis[i]) {
            if(checkCycleDFS(i, -1, adj, vis)) return true;
        }
    }
    return false;
}

/*
Distance of the nearest cell having 1

Given a n*m matrix find the distance of each cell to its nearest 1.

The distance is calculated by (i1 - i2) + (c1 - c2)

Eg:
0 0 0       2 1 2
0 1 0    -> 1 0 1
1 0 1       0 1 0
(Given)     (result)

For 1 he himself is a 1 thus distance is 0.

Using BFS.
*/
vector<vector<int>> distance1(vector<vector<int>> &grid, int n, int m) {
    vector<vector<int>> vis(n, vector<int>(m, 0));
    vector<vector<int>> dist(n, vector<int>(m, 0));
    queue<pair<pair<int, int>, int>> q;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 1) {
                q.push({{i, j}, 0});
                vis[i][j] = 1;
            }
        }
    }

    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    while(!q.empty()) {
        int row = q.front().first.first;
        int col = q.front().first.second;
        int steps = q.front().second;
        q.pop();

        dist[row][col] = steps;

        for(int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            if(nrow >=0 && nrow < n && ncol >= 0 && ncol > m && !vis[nrow][ncol]) {
                vis[nrow][ncol] = 1;
                q.push({{nrow, ncol}, steps + 1});
            }
        }
    }
    return dist;
}

/*
Replace O's with X's if they are surrounded by X.

Eg:
X O X X     X O X X
X O O X  -> X O O X
X X X X     X X X X
X O O X     X X X X
X X X X     X X X X 
(Given)     (result)

Important observation boundary O's and O's connected to it cannot be converted to X's

To identify all the boundry O's and its connecting O's use DFS algorithm.
*/
void fillDfs(int row, int col, vector<vector<int>> &vis, 
vector<vector<char>> &mat, int delrow[], int delcol[]) {
    vis[row][col] = 1; 
    int n = mat.size();
    int m = mat[0].size();
    
    for(int i = 0;i<4;i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i]; 

        if(nrow >=0 && nrow <n && ncol >= 0 && ncol < m 
        && !vis[nrow][ncol] && mat[nrow][ncol] == 'O') {
            fillDfs(nrow, ncol, vis, mat, delrow, delcol); 
        }
    }
}

vector<vector<char>> fill(int n, int m, vector<vector<char>> mat)
{
    int delrow[] = {-1, 0, +1, 0};
    int delcol[] = {0, 1, 0, -1}; 
    vector<vector<int>> vis(n, vector<int>(m,0)); 

    for(int j = 0 ; j<m;j++) {

        // first row 
        if(!vis[0][j] && mat[0][j] == 'O') {
            fillDfs(0, j, vis, mat, delrow, delcol); 
        }
        
        // last row 
        if(!vis[n-1][j] && mat[n-1][j] == 'O') {
            fillDfs(n-1,j,vis,mat, delrow, delcol); 
        }
    }
    
    for(int i = 0;i<n;i++) {

        // first column 
        if(!vis[i][0] && mat[i][0] == 'O') {
            fillDfs(i, 0, vis, mat, delrow, delcol); 
        }
        
        // last column
        if(!vis[i][m-1] && mat[i][m-1] == 'O') {
            fillDfs(i, m-1, vis, mat, delrow, delcol); 
        }
    }
    
    for(int i = 0;i<n;i++) {
        for(int j= 0 ;j<m;j++) {
            if(!vis[i][j] && mat[i][j] == 'O') 
                mat[i][j] = 'X'; 
        }
    }
    
    return mat; 
}

/*
Number of enclaves in a graph.

Given a grid 0 represents water and 1 represents land.

Output the count of land (1) from which the border can't be traversed.

Similar to rotten oranges problem.

BFS or DFS traversal can be used to mark all the connecting boundary 1's.
*/

int numberOfEnclaves(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    int vis[n][m] = {0};
    queue<pair<int, int>> q;

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(i == 0 || i == n-1 || j == 0 || j == m-1) {
                if(grid[i][j] == 1) {
                    vis[i][j] = 1;
                    q.push({i, j});
                }
            }
        }
    }

    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    while(!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for(int i=0; i<4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            if(nrow >=0 && nrow < n && ncol >= 0 && ncol < m && grid[nrow][ncol] == 1 && !vis[nrow][ncol]) {
                vis[nrow][ncol] = 1;
                q.push({nrow, ncol});
            }
        }
    }

    int cnt = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(grid[i][j] == 1 && !vis[i][j]) cnt++;
        }
    }
    return cnt;
}

/*
Count the number of distinct islands.

Two islands are said to distinct if they are not the rotate or refelction of each other.

Eg:
1 1 0 1 1
1 0 0 0 0
0 0 0 0 1
1 1 0 1 1

In the above grid there are three distinct islands. 
1. 1 1
2. 1 1
   1
3.   1
   1 1

The idea is to store all the islands in a set as it will only contain unique ones.

Store it in the form of a list.
To make the coordinates identical selct a base and subtract the top, left, bottom and right from the base.
Then store.
*/
void countDistinctIslandsDfs(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &vis, vector<pair<int, int>> &vec, int baseRow, int baseCol) {
    vis[row][col] = 1;
    vec.push_back({row - baseRow, col - baseCol});

    int n = grid.size();
    int m = grid[0].size();

    int delRow[] = {-1, 0, 1, 0};
    int delCol[] = {0, 1, 0, -1};

    for(int i=0; i<4; i++) {
        int nrow = row + delRow[i];
        int ncol = col + delCol[i];

        if(nrow >=0 && nrow < n && ncol >= 0 && ncol < m && grid[nrow][ncol] && !vis[nrow][ncol]) {
            countDistinctIslandsDfs(nrow, ncol, grid, vis, vec, baseRow, baseCol);
        }
    }
}

int countDistinctIslands(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> vis(n, vector<int>(m, 0));
    set<vector<pair<int, int>>> st;

    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(!vis[i][j] && grid[i][j]) {
                vector<pair<int, int>> vec;
                countDistinctIslandsDfs(i, j, grid, vis, vec, i, j);
                st.insert(vec);
            }
        }
    }

    return st.size();
}

/*
Bipartite Graph using BFS.

A graph is a bipartite graph if we can colour the nodes with 2 colours such that no adjacent color is similar.

A linear graph (No cycle) is always a bipartite graph.

Any graph with a even cycle can be a bipartite graph.
Thus graph with a odd cycle cannot be a bipartite graph.

If code fails on large test cases always check for components.
*/
bool isBipartiteBFSHelper(int start, vector<vector<int>> &adj, vector<int> &color) {
    color[start] = 0;
    queue<int> q;
    q.push(start);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(auto it: adj[node]) {
            if(color[it] == -1) {
                color[it] = 1 - color[node];
                q.push(it);
            }
            else if(color[node] == color[it]) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartiteBFS(vector<vector<int>> &edges) {
	int n = edges.size();
    vector<vector<int>> adj(n);

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(edges[i][j]) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}

	int V = adj.size();

    vector<int> color(n, -1);

    for(int i=0; i<V; i++) {
        if(color[i] == -1) {
            if(isBipartiteBFSHelper(i, adj, color) == false) return false;
        }
    }

    return true;
}

/*
Check Bipartite graph using DFS.
*/
bool isBipartiteDFSHelper(int node, int col, vector<vector<int>> &adj, vector<int> &color) {
    color[node] = col;

    for(auto it: adj[node]) {
        if(color[it] == -1) {
            if(isBipartiteDFSHelper(it, 1 - col, adj, color) == false) return false;
        }
        else if(color[it] == col) {
            return false;
        }
    }
    
    return true;
}

bool isBipartiteDFS(vector<vector<int>> &edges) {
	int n = edges.size();
    vector<vector<int>> adj(n);

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(edges[i][j]) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}

	int V = adj.size();

    vector<int> color(n, -1);

    for(int i=0; i<V; i++) {
        if(color[i] == -1) {
            if(isBipartiteDFSHelper(i, 0, adj, color) == false) return false;
        }
    }

    return true;
}

/*
Detect cycle in a directed graph.

Same algorithm for detecting a cycle in undirected graphs cannot be used.

In this problem, we have to use a visited and a path visited array.

Path visited array indicated if the nodes have arrived to a conjunction following the same path.
*/
bool isCycleDirectedDFS(int node, vector<int> adj[], int vis[], int pathVis[]) {    
    vis[node] = 1;
    pathVis[node] = 1;

    for(auto it: adj[node]) {
        if(!vis[it]) {
            if(isCycleDirectedDFS(it, adj, vis, pathVis)) return true;
        }
        else if(pathVis[it]) {
            return true;
        }
    }
    pathVis[node] = 0;
    return false;
}

bool isCycleDirected(int V, vector<int> adj[]) {
    int vis[V] = {0};
    int pathVis[V] = {0};

    for(int i=0; i<V; i++) {
        if(!vis[i]) {
            if(isCycleDirectedDFS(i, adj, vis, pathVis)) return true;
        }
    }

    return false;
}

/*
Eventual safe state

Return an array of safe nodes sorted in ascending order.

A node is a terminal node when it has zero outgoing edges.

A node is a safe node when every possible path starting from that node leads to a terminal node.

A terminal node is itself a safe node

Observation:
1. Any node which is a part of the cycle cannot be a safe node.
2. Any node which leads to a cycle cannot be a safe node.
*/
bool eSNHelper(int node, vector<int> adj[], int vis[], int pathVis[], int check[]) {    
    vis[node] = 1;
    pathVis[node] = 1;
    check[node] = 0;

    for(auto it: adj[node]) {
        if(!vis[it]) {
            if(eSNHelper(it, adj, vis, pathVis, check)) {
                return true;
            }
        }
        else if(pathVis[it]) {
            return true;
        }
    }
    check[node] = 1;
    pathVis[node] = 0;
    return false;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    int vis[V] = {0};
    int pathVis[V] = {0};
    int check[V] = {0};
    vector<int> safeNodes;

    for(int i=0; i<V; i++) {
        if(!vis[i]) {
            eSNHelper(i, adj, vis, pathVis, check);
        }
    }
    for(int i=0; i<V; i++) {
        if(check[i]) {
            safeNodes.push_back(i);
        }
    }

    return safeNodes;
}

/*
Topological sort algorithm.
Only in DAG (Directed Acyclic Graph).

It is a linear ordering of vertices such that,
if there is an edge between u & v, 
then u appears before v in that ordering.
*/
void tSDFS(int node, vector<int> adj[], int vis[], stack<int> &st) {
    vis[node] = 1;
    
    for(auto it: adj[node]) {
        if(!vis[it]) {
            tSDFS(it, adj, vis, st);
        }
    }

    st.push(node);
}

vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  {
    vector<int> adj[v+1];
    for(int i=0; i<e; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
    }

    int vis[v] = {0};
    stack<int> st;

    for(int i=0; i<v; i++) {
        if(!vis[i]) {
            tSDFS(i, adj, vis, st);
        }
    }

    vector<int> ans;
    for(int i=0; i<v; i++) {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}

/*
Kahn's algorithm BFS (Topological order)

All conditions same as topological order but different name as it uses BFS instead of DFS.

It uses the concept of indegree.
*/
vector<int> kahnAlgorithm(vector<vector<int>> &edges, int v, int e)  {
    vector<int> adj[v+1];
    for(int i=0; i<e; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
    }

    int indegree[v+1] = {0};
    for(int i=0; i<v; i++) {
        for(auto it: adj[i]) {
            indegree[it]++;
        }
    }

    queue<int> q;
    for(int i=0; i<v; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ans;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for(auto it: adj[node]) {
            indegree[it]--;
            if(indegree[it] == 0) {
                q.push(it);
            }
        }
    }
    return ans;
}

/*
Detect a cycle in Directed Graph using topological sort (Kahn's Algorithm).

The simple modification in the above code is that
if topological sort size is equal to the number of nodes in the graph then it is an acyclical graph.
else it has size less than the number of nodes in the graph then cyclical graph.

Code to add:
if(ans.size() == v) return false;
return true;

We can also replace the ans vector with count variable.
*/

/*
Course schedule | ans ||

Given the edges of the graph
in {x, y} pattern.
x -> y is an edge 
To perform task y, first x has to be performed.

We have to return if it is possible to perform all the task with given condition.
If yes then return true else return false.
*/
bool prerequisite(vector<vector<int>> &edges, int v, int e) {
    vector<int> res = kahnAlgorithm(edges, v, e);

    if(res.size() == v) return true;
    return false;
}

/*
Find Eventual safe state using topological sort.

Just we have to reverse the graph.
i.e. if the edge is going from x -> y then after reversing it will be y -> x.

After reversing the graph we have to perform simple topological sort.

At the end the topological sort will contain the safe nodes and terminal nodes in reversed order.

Now reverse/sort the topological sort and return the answer.
*/

int main() {

    vector<vector<int>> grid = {
        {2, 1},
        {1, 0},
        {3, 2},
        {0, 1},
        {0, 2}};

    int v = 4;
    int e = 5;
    vector<int> res = kahnAlgorithm(grid, v, e);

    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }

    return 0;
}