class Solution {
    deque<int> dq;

private:
    void dfs(int node, vector<int>& visited, vector<vector<int>>& adj) {

        // STEP 1:
        // Mark the current node as visited.
        // This prevents us from visiting the same node again.
        visited[node] = 1;

        // STEP 2:
        // Visit all neighbours of the current node.
        for (auto &nbr : adj[node]) {

            // IMPORTANT:
            // Only call DFS if the neighbour has not been visited.
            if (!visited[nbr]) {

                // STEP 3:
                // Go deeper into the graph.
                // This DFS call must completely finish before
                // we continue with the current node.
                dfs(nbr, visited, adj);
            }
        }

        // STEP 4:
        // We reach here only after ALL neighbours of 'node'
        // have been completely processed.
        //
        // This means the DFS call for this node is FINISHED.
        //
        // IMPORTANT:
        // A node is added to the topological order AFTER
        // all its outgoing neighbours have been processed.
        //
        // We use push_front() so that the node that finishes
        // later comes before the nodes that finished earlier.
        dq.push_front(node);
    }

public:

    vector<int> topoSort(int V, vector<vector<int>>& adj) {

        vector<int> ans;

        // STEP 5:
        // Initially, no node has been visited.
        vector<int> visited(V, 0);

        // STEP 6:
        // Start DFS from every unvisited node.
        //
        // This is necessary because the graph can be disconnected.
        for (int i = 0; i < V; i++) {

            if (!visited[i]) {

                // Start DFS from node i.
                dfs(i, visited, adj);
            }
        }

        // STEP 7:
        // All DFS calls are now finished.
        // dq contains the nodes in topological order
        // because we used push_front().
        for (auto it : dq) {
            ans.push_back(it);
        }

        // STEP 8:
        // Return the final topological ordering.
        return ans;
    }
};