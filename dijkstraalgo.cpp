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

        // Step 2: Min heap
        // {distance, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        // Step 3: Distance array
        vector<int> dist(V, 1e9);

        dist[src] = 0;
        pq.push({0, src});

        // Step 4: Dijkstra
        while (!pq.empty()) {

            int dis = pq.top().first;
            int node = pq.top().second;

            pq.pop();

            // Important: ignore outdated heap entries
            if (dis > dist[node])
                continue;

            // Visit neighbours
            for (auto &it : adj[node]) {

                int adjNode = it.first;
                int edgeWeight = it.second;

                // Relaxation
                if (dis + edgeWeight < dist[adjNode]) {

                    dist[adjNode] = dis + edgeWeight;

                    pq.push({dist[adjNode], adjNode});
                }
            }
        }

        return dist;
    }
};