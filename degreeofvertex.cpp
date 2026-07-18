/*
class Solution {
public:
    vector<int> degree(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> ans(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i] += matrix[i][j];
            }
        }

        return ans;
    }
}
    */

//     The degree of a vertex is the number of edges connected to that vertex.
// For an adjacency matrix, each row represents one vertex. So, to find the 
// degree of vertex i, we add all the 1s in row i.

// For example:

// matrix = [
//   [0, 1, 1],
//   [1, 0, 1],
//   [1, 1, 0]
// ]
// Vertex 0: row [0, 1, 1] → 0 + 1 + 1 = 2 → degree = 2
// Vertex 1: row [1, 0, 1] → 1 + 0 + 1 = 2 → degree = 2
// Vertex 2: row [1, 1, 0] → 1 + 1 + 0 = 2 → degree = 2


// adj = {
//     {1, 2},       // vertex 0
//     {0, 2},       // vertex 1
//     {0, 1, 3},    // vertex 2
//     {2}           // vertex 3
// }

// Vertex 0 → 2 neighbors → degree = 2
// Vertex 1 → 2 neighbors → degree = 2
// Vertex 2 → 3 neighbors → degree = 3
// Vertex 3 → 1 neighbor  → degree = 1

// ans = [2, 2, 3, 1]

/*
class Solution {
public:
    vector<int> degree(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            ans[i] = adj[i].size();
        }

        return ans;
    }
};


So remember: Adjacency matrix → sum of each row. Adjacency list → size of each list.

*/