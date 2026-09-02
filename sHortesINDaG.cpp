class Solution {
private:
    void toposort(int node,
                  vector<vector<pair<int,int>>>& adj,
                  vector<int>& vis,
                  stack<int>& st) {

        vis[node] = 1;

        for (auto it : adj[node]) {
            int v = it.first;

            if (!vis[v]) {
                toposort(v, adj, vis, st);
            }
        }

        st.push(node);
    }

public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges) {

        vector<vector<pair<int,int>>> adj(V);

        // Build directed graph
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];

            adj[u].push_back({v, wt});
        }

        // Topological sort
        vector<int> vis(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                toposort(i, adj, vis, st);
            }
        }

        // Distance array
        vector<int> dist(V, 1e9);

        // Source = 0
        dist[0] = 0;

        // Process nodes in topological order
        while (!st.empty()) {

            int node = st.top();
            st.pop();

            // Only process reachable nodes
            if (dist[node] != 1e9) {

                for (auto it : adj[node]) {

                    int v = it.first;
                    int wt = it.second;

                    if (dist[node] + wt < dist[v]) {
                        dist[v] = dist[node] + wt;
                    }
                }
            }
        }

        // Convert unreachable nodes to -1
        for (int i = 0; i < V; i++) {
            if (dist[i] == 1e9) {
                dist[i] = -1;
            }
        }

        return dist;
    }
    
    
    // time complexity topo sort plain dfs 
    //   O(V+E)
    // and for proccesing all the nodes in the stack 
    // there are V nodes and goind to M edges 
};