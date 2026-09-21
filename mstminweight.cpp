class Solution {
public:
    // Prim's Algorithm - MST using Min Heap (Priority Queue)
    // Time: O(E log E) | Space: O(V + E)
    int spanningTree(int V, vector<vector<int>>& adj) {

        // Min-heap of {weight, node} — always pop the smallest edge weight first
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        // Tracks nodes already included in the MST
        vector<int> vis(V, 0);

        // Start from node 0 with weight 0 (arbitrary starting point for Prim's)
        pq.push({0, 0});

        int sum = 0; // stores total weight of the MST

        while (!pq.empty()) {

            // Pick the edge with minimum weight from the heap
            auto top = pq.top();
            pq.pop();

            int wt = top.first;
            int node = top.second;

            // Skip if node already added to MST (lazy deletion —
            // heap may contain stale duplicate entries for the same node)
            if (vis[node])
                continue;

            // Include this node in the MST
            vis[node] = 1;
            sum += wt; // add its edge weight to the total MST cost

            // Explore all neighbors of the newly added node
            for (auto edge : adj[node]) {

                int adjNode = edge[0]; // neighbor node
                int edw = edge[1];     // edge weight to neighbor

                // Only push if neighbor is not yet part of MST
                // (greedy choice — smaller weights will surface first via heap)
                if (!vis[adjNode]) {
                    pq.push({edw, adjNode});
                }
            }
        }

        // sum = total weight of the Minimum Spanning Tree
        return sum;
    }
};