class Solution {
private:
    // Returns true if starting from 'node', a cycle is reachable
    // (i.e., node is UNSAFE)
    bool dfs(int node,
             vector<int>& vis,
             vector<vector<int>>& graph,
             vector<int>& current) {

        // 1. Mark this node as visited
        //    (once visited, we never re-run dfs() on it again)
        vis[node] = 1;

        // 2. Put this node in the current DFS path
        //    current[node] = 1 means "on the active recursion stack"
        //    (assume unsafe for now, will correct below if proven safe)
        current[node] = 1;

        // 3. Explore every outgoing edge (neighbour) of this node
        for (auto nbr : graph[node]) {

            // Case A: neighbour has NOT been visited yet
            if (!vis[nbr]) {
                // Recurse into the neighbour
                // If that call finds a cycle, it returns true
                if (dfs(nbr, vis, graph, current) == true)
                    return true;   // propagate "unsafe" upward
                                   // NOTE: current[node] is NOT reset here —
                                   // we exit before reaching step 4
            }
            // Case B: neighbour has ALREADY been visited
            else {
                // Check if that neighbour is currently "unsafe"
                // This single check covers two situations:
                //   (i)  nbr is still on the active recursion stack
                //        → true back-edge → real cycle
                //   (ii) nbr was fully processed in an EARLIER dfs() call
                //        (different starting node) and was found unsafe,
                //        so its current[nbr] was never reset to 0
                //        → unsafety correctly propagates here too
                if (current[nbr] == 1) {
                    return true;
                }
                // If current[nbr] == 0, that neighbour was already
                // proven safe — no action needed, just continue the loop
            }
        }

        // 4. Reached only if EVERY neighbour was explored
        //    and none of them led to a cycle
        //    → this node is SAFE
        current[node] = 0;   // backtrack: remove from current path permanently

        return false;   // no cycle found through this node
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int v = graph.size();

        // vis[i] = 1 → node i has been visited at least once
        vector<int> vis(v, 0);

        // current[i] = 1 → node i is either:
        //     - still on the active recursion stack, OR
        //     - was permanently marked unsafe by a completed dfs() call
        // current[i] = 0 → node i has been proven safe
        vector<int> current(v, 0);

        vector<int> result;

        // Run DFS starting from every unvisited node
        // (needed because the graph may be disconnected)
        for (int i = 0; i < v; i++) {
            if (!vis[i]) {
                dfs(i, vis, graph, current);
                // Return value is ignored here —
                // we only care about the final state of current[]
                // after ALL dfs() calls are done
            }
        }

        // Now scan current[] to collect the answer:
        // current[i] == 0 → node i's DFS call reached step 4 and backtracked
        //                    → it's SAFE
        // current[i] == 1 → node i's DFS call exited early via "return true"
        //                    → it's UNSAFE
        for (int i = 0; i < v; i++) {
            if (current[i] == 0) {
                result.push_back(i);
            }
        }

        return result;
    }
};
