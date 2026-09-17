class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {

        // Step 1: Initialize distance of every node as INF.
        // Source node has distance 0.
        vector<int> dist(V, 1e8);
        dist[src] = 0;


        // Step 2: Relax all edges V-1 times.
        // A shortest path can have at most V-1 edges
        // if there is no negative weight cycle.
        for (int i = 0; i < V - 1; i++) {

            // Track whether any distance was updated in this round.
            bool updated = false;

            // Check every edge.
            for (auto it : edges) {

                int u = it[0];     // Starting node
                int v = it[1];     // Ending node
                int wt = it[2];    // Edge weight

                // Relax the edge:
                // If u is reachable and going through u gives
                // a shorter path to v, update the distance.
                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                    updated = true;
                }
            }

            // If no distance was updated, all shortest paths
            // have already been found, so we can stop early.
            if (!updated)
                break;
        }


        // Step 3: Do one extra relaxation to check for
        // a reachable negative weight cycle.
        //
        // If a distance can still be reduced after V-1 rounds,
        // then a negative cycle is present.
        for (auto it : edges) {

            int u = it[0];
            int v = it[1];
            int wt = it[2];

            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1};
            }
        }


        // Step 4: No reachable negative cycle was found.
        // Return the shortest distances from the source.
        return dist;
    }
};