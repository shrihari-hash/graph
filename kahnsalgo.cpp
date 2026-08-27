class Solution {
  public:
    vector<int> topoSort(int V, vector<vector<int>>& adj) {
        vector<int> indegree(V, 0);
        queue<int> q;
        vector<int> result;

        // Compute indegree of each vertex
        for (int i = 0; i < V; i++) {
            for (int x : adj[i]) {
                indegree[x]++;
            }
        }

        // Push all vertices with indegree 0
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);   // record order

            for (int x : adj[node]) {
                indegree[x]--;
                if (indegree[x] == 0)
                    q.push(x);
            }
        }

        // Optional: if result.size() != V, there's a cycle,
        // so no valid topological order exists.
        // You could return {} or handle it based on problem requirements.

        return result;
    }
};

// graph should be directed and acyclic not cycle should be preset in that 