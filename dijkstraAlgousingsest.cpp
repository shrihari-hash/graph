class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {

        // Step 1: Create adjacency list
        vector<vector<pair<int, int>>> adj(V);

        for (auto &it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            // Graph is undirected
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        // Step 2: Distance array
        vector<int> dist(V, 1e9);

        // Step 3: Set stores {distance, node}
        set<pair<int, int>> st;

        // Source distance = 0
        dist[src] = 0;
        st.insert({0, src});

        // Step 4: Process nodes
        while (!st.empty()) {

            // Get node having minimum distance
            auto it = *(st.begin());

            int dis = it.first;
            int node = it.second;

            // Remove it from set
            st.erase(it);

            // Step 5: Check all neighbours
            for (auto &it : adj[node]) {

                int adjnode = it.first;
                int edgeweight = it.second;

                // Step 6: Relaxation
                if (dis + edgeweight < dist[adjnode]) {

                    // If old distance exists in set,
                    // remove the old {distance, node}
                    if (dist[adjnode] != 1e9) {
                        st.erase({dist[adjnode], adjnode});
                    }

                    // Update shortest distance
                    dist[adjnode] = dis + edgeweight;

                    // Insert new {distance, node}
                    st.insert({dist[adjnode], adjnode});
                }
            }
        }

        return dist;
    }
};