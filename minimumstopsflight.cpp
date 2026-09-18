class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {

        // Step 1: Build adjacency list
        // adj[u] contains {v, cost} for every flight u -> v
        vector<vector<pair<int,int>>> adj(n);

        for (auto it : flights) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            adj[u].push_back({v, wt});
        }

        /*
            queue stores:
            {stops, {node, cost}}

            stops = number of flights/edges used so far
            node  = current city
            cost  = total cost to reach this city
        */
        queue<pair<int, pair<int,int>>> q;

        // Initially we are at src with 0 stops and 0 cost
        q.push({0, {src, 0}});

        // dist[i] = minimum cost found so far to reach city i
        vector<int> dist(n, 1e9);

        dist[src] = 0;

        // Step 2: Process the queue
        while (!q.empty()) {

            auto it = q.front();
            q.pop();

            int stops = it.first;
            int node = it.second.first;
            int cost = it.second.second;

            // We cannot take more than k intermediate stops.
            // Therefore, we cannot continue expanding this state.
            if (stops > k) {
                continue;
            }

            // Step 3: Explore all neighbouring cities
            for (auto it : adj[node]) {

                int adjnode = it.first;
                int edgeweight = it.second;

                /*
                    If going from node -> adjnode gives a cheaper cost,
                    update the distance and push the new state.

                    stops <= k ensures that we do not start another
                    flight after already exceeding the allowed stops.
                */
                if (cost + edgeweight < dist[adjnode] &&
                    stops <= k) {

                    dist[adjnode] = cost + edgeweight;

                    q.push({
                        stops + 1,
                        {adjnode, dist[adjnode]}
                    });
                }
            }
        }

        // If destination was never reached
        if (dist[dst] == 1e9) {
            return -1;
        }

        return dist[dst];
    }
};