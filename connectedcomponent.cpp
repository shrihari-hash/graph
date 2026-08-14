class Solution {

private:

    // ----------------------------------------------------------
    // DFS FUNCTION
    //
    // This function visits all nodes belonging to the same
    // connected component starting from the given node.
    // ----------------------------------------------------------
    void dfs(int node,
             vector<int>& vis,
             vector<vector<int>>& adj,
             vector<int>& component) {

        // ------------------------------------------------------
        // STEP 1 : Mark the current node as visited.
        // ------------------------------------------------------
        vis[node] = 1;

        // ------------------------------------------------------
        // STEP 2 : Store the node in the current component.
        //
        // Every node reached during this DFS belongs to the
        // same connected component.
        // ------------------------------------------------------
        component.push_back(node);

        // ------------------------------------------------------
        // STEP 3 : Visit all neighbouring nodes.
        // ------------------------------------------------------
        for (auto it : adj[node]) {

            // Visit only unvisited neighbours.
            if (!vis[it]) {
                dfs(it, vis, adj, component);
            }
        }
    }

public:

    vector<vector<int>> getComponents(int V,
                                      vector<vector<int>>& edges) {

        // ------------------------------------------------------
        // STEP 1 : Create visited array.
        //
        // vis[i] = 0 -> not visited
        // vis[i] = 1 -> visited
        // ------------------------------------------------------
        vector<int> vis(V, 0);

        // ------------------------------------------------------
        // STEP 2 : Final answer.
        //
        // Each inner vector stores one connected component.
        // ------------------------------------------------------
        vector<vector<int>> result;

        // ------------------------------------------------------
        // STEP 3 : Create adjacency list.
        // ------------------------------------------------------
        vector<vector<int>> adj(V);

        // ------------------------------------------------------
        // STEP 4 : Build the graph.
        //
        // Since the graph is undirected,
        // add both u->v and v->u.
        // ------------------------------------------------------
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // ------------------------------------------------------
        // STEP 5 : Traverse every node.
        //
        // Whenever an unvisited node is found,
        // it starts a new connected component.
        // ------------------------------------------------------
        for (int i = 0; i < V; i++) {

            if (!vis[i]) {

                // ----------------------------------------------
                // Create a fresh vector for this component.
                // ----------------------------------------------
                vector<int> component;

                // Collect all nodes of this component.  component is a vector after one call it store 
                // like [1,2,3]  then result vector is type of vector of vector then push in result vector 
                // again call component will store [4,5,6] and then push into the result vector 
                dfs(i, vis, adj, component);

                // Store this completed component.
                result.push_back(component);
            }
        }

        // ------------------------------------------------------
        // STEP 6 : Return all connected components.
        // ------------------------------------------------------
        return result;
    }
};