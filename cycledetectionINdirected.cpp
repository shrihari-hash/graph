class Solution {
private:

    bool dfs(int node,
             vector<vector<int>>& adj,
             vector<int>& vis,
             vector<int>& current) {

        // 1. We have visited this node
        vis[node] = 1;

        // 2. Put this node in the current DFS path
        current[node] = 1;

        // 3. Explore all neighbours of this node
        for(auto nbr : adj[node]) {

            // Neighbour has NOT been visited
            if(!vis[nbr]) {

                // Explore the neighbour
                bool res = dfs(nbr, adj, vis, current);

                // If cycle is found in that neighbour's DFS
                if(res) {
                    return true;
                }
            }

            // Neighbour is already visited
            else {

                // Check whether neighbour is still
                // present in the current DFS path
                if(current[nbr] == 1) {

                    // We came back to a node in
                    // the current path → cycle
                    return true;
                }
            }
        }

        // 4. All neighbours are explored
        // No cycle was found from this node

        // Remove this node from current DFS path
        // This is BACKTRACKING
        current[node] = 0;

        // No cycle found
        return false;
    }


public:

    bool isCyclic(int V, vector<vector<int>>& edges) {

        // Create adjacency list
        vector<vector<int>> adj(V);

        // Visited array
        // vis[i] = 1 → node i was visited
        vector<int> vis(V, 0);

        // Current DFS path
        // current[i] = 1 → node i is currently
        // inside the recursion path
        vector<int> current(V, 0);


        // Build adjacency list
        for(auto e : edges) {

            int u = e[0];
            int v = e[1];

            // Directed edge: u → v
            adj[u].push_back(v);
        }


        // Handle all connected components
        for(int i = 0; i < V; i++) {

            // If this node has not been visited
            if(!vis[i]) {

                // Start DFS
                bool ans = dfs(i, adj, vis, current);

                // Cycle found
                if(ans) {
                    return true;
                }
            }
        }


        // No cycle anywhere in the graph
        return false;
    }
};