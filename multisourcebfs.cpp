class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& grid) {

        // Get the dimensions of the matrix
        int n = grid.size();
        int m = grid[0].size();

        // vis matrix:
        // 1 = not visited
        // 0 = visited
        vector<vector<int>> vis(n, vector<int>(m, 1));

        // Result matrix to store the distance of each cell from the nearest 0
        vector<vector<int>> res(n, vector<int>(m, 0));

        // Queue stores:
        // {{row, col}, distance}
        queue<pair<pair<int,int>,int>> q;

        // ---------------- MULTI-SOURCE BFS ----------------
        // Push all 0 cells into the queue initially.
        // These are the starting points of BFS.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (grid[i][j] == 0) {
                    q.push({{i, j}, 0});   // distance of 0 cell is 0
                    vis[i][j] = 0;         // mark as visited
                }
            }
        }

        // Direction arrays for moving in 4 directions
        // Up, Left, Down, Right
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, -1, 0, 1};

        // ---------------- BFS TRAVERSAL ----------------
        while (!q.empty()) {

            // Current cell
            int row = q.front().first.first;
            int col = q.front().first.second;

            // Current distance from nearest 0
            int t = q.front().second;

            q.pop();

            // Store the shortest distance for this cell
            res[row][col] = t;

            // Explore all 4 neighbouring cells
            for (int i = 0; i < 4; i++) {

                int nrow = row + delrow[i];
                int ncol = col + delcol[i];

                // Check:
                // 1. Inside the matrix
                // 2. Not visited before
                // 3. Cell value is 1
                if (nrow >= 0 && nrow < n &&
                    ncol >= 0 && ncol < m &&
                    vis[nrow][ncol] == 1 &&
                    grid[nrow][ncol] == 1) {

                    // Mark visited immediately
                    // (prevents the same cell from entering queue multiple times)
                    vis[nrow][ncol] = 0;

                    // Push neighbour with distance + 1
                    q.push({{nrow, ncol}, t + 1});
                }
            }
        }

        // Return the matrix containing the distance of every cell
        // from the nearest 0
        return res;
    }
};

/*
===================== REVISION NOTES =====================

Pattern:
    Multi-Source BFS

Idea:
    - All 0 cells are treated as sources.
    - BFS expands level by level.
    - The first time a 1 cell is reached,
      that distance is guaranteed to be the shortest.

Why mark visited while pushing?
    To avoid inserting the same cell into the queue
    multiple times from different directions.

Time Complexity:
    O(n * m)
    Each cell is visited exactly once.

Space Complexity:
    O(n * m)
    - vis matrix
    - res matrix
    - queue (in the worst case)
*/