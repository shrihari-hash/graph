class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {

        // Number of rows and columns
        int n = grid.size();
        int m = grid[0].size();

        // Queue stores:
        // {{row, col}, time}
        // We use Multi-Source BFS, so initially every rotten orange
        // is inserted into the queue.
        queue<pair<pair<int,int>,int>> q;

        // Count total fresh oranges.
        // Later we compare how many actually became rotten.
        int cntfresh = 0;

        // Visited matrix
        // 0 -> Not visited
        // 2 -> Rotten / Already processed
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // ----------------------------------------------------------
        // STEP 1 : Traverse the entire grid.
        //
        // 1. Push every rotten orange into the queue.
        // 2. Count every fresh orange.
        // ----------------------------------------------------------
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {

                // Initial rotten oranges are BFS sources.
                if(grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                    vis[i][j] = 2;
                }

                // Count fresh oranges.
                if(grid[i][j] == 1) {
                    cntfresh++;
                }
            }
        }

        // Stores total time required.
        int tm = 0;

        // Counts how many fresh oranges became rotten.
        int cnt = 0;

        // Directions: Up, Left, Down, Right
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, -1, 0, 1};

        // ----------------------------------------------------------
        // STEP 2 : Multi-Source BFS
        // ----------------------------------------------------------
        while(!q.empty()) {

            // Current rotten orange
            int r = q.front().first.first;
            int c = q.front().first.second;

            // Time when this orange became rotten
            int t = q.front().second;

            // Remove current node from queue
            q.pop();

            // Update maximum time reached
            tm = max(tm, t);

            // Visit all four neighbouring cells
            for(int i = 0; i < 4; i++) {

                int nrow = r + delrow[i];
                int ncol = c + delcol[i];

                // --------------------------------------------------
                // Valid neighbour conditions:
                //
                // 1. Inside grid
                // 2. Not already rotten/visited
                // 3. Must be a fresh orange
                // --------------------------------------------------
                if(nrow >= 0 && nrow < n &&
                   ncol >= 0 && ncol < m &&
                   vis[nrow][ncol] != 2 &&
                   grid[nrow][ncol] == 1) {

                    // Mark as rotten immediately
                    vis[nrow][ncol] = 2;

                    // Push into queue with one extra minute
                    q.push({{nrow, ncol}, t + 1});

                    // Count this fresh orange as rotten
                    cnt++;
                }
            }
        }

        // ----------------------------------------------------------
        // STEP 3 : Check if every fresh orange became rotten.
        // ----------------------------------------------------------

        // Some fresh oranges could not be reached.
        if(cnt != cntfresh)
            return -1;

        // All oranges became rotten.
        return tm;
    }
};