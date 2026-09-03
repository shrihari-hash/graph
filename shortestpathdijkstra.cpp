class Solution {
public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges,
                             int src, int dest) {

        // Adjacency list
        vector<vector<pair<int, int>>> adj(V + 1);

        // Build undirected weighted graph
        for (auto e : edges) {
            int u = e[0];
            int v = e[1];
            int x = e[2];

            adj[u].push_back({v, x});
            adj[v].push_back({u, x});
        }

        // Min heap: {distance, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        vector<int> dist(V + 1, 1e9);
        vector<int> parent(V + 1);

        // Initially, every node is its own parent
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }

        // Source initialization
        dist[src] = 0;
        pq.push({0, src});

        // Dijkstra
        while (!pq.empty()) {

            auto it = pq.top();
            pq.pop();

            int dis = it.first;
            int node = it.second;

            // Traverse neighbours
            for (auto it : adj[node]) {

                int adjNode = it.first;
                int eweight = it.second;

                // Relaxation
                if (dis + eweight < dist[adjNode]) {

                    dist[adjNode] = dis + eweight;

                    pq.push({dist[adjNode], adjNode});

                    parent[adjNode] = node;
                }
            }
        }

        // Destination unreachable
        if (dist[dest] == 1e9) {
            return {-1};
        }

        // Construct shortest path
        vector<int> path;

        int node = dest;

        while (parent[node] != node) {
            path.push_back(node);
            node = parent[node];
        }

        path.push_back(src);

        reverse(path.begin(), path.end());

        return path;
    }
};