#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> bfs(vector<vector<int>> &adj) {

        // Total number of vertices
        int V = adj.size();

        // Visited array
        int vis[V] = {0};

        // Queue for BFS
        queue<int> q;

        // Stores BFS traversal
        vector<int> bfs;

        // Start from node 0
        vis[0] = 1;
        q.push(0);

        while (!q.empty()) {

            // Take the front node
            int node = q.front();
            q.pop();

            // Store it in answer
            bfs.push_back(node);

            // Visit all adjacent nodes
            for (auto it : adj[node]) {

                if (!vis[it]) {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }

        return bfs;
    }
};

int main() {

    int V, E;

    // Input number of vertices and edges
    cin >> V >> E;

    // Create adjacency list
    vector<vector<int>> adj(V);

    // Input edges
    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;

        // Undirected graph
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Solution obj;

    vector<int> ans = obj.bfs(adj);

    cout << "BFS Traversal : ";

    for (auto it : ans)
        cout << it << " ";

    return 0;
}