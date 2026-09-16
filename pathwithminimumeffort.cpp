class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& height) {

        // Step 1: Min-heap priority queue
        // Stores: {effort, {row, col}}
        // The cell with minimum effort comes first.
        priority_queue<
            pair<int, pair<int,int>>,
            vector<pair<int, pair<int,int>>>,
            greater<pair<int, pair<int,int>>>
        > pq;

        // Step 2: Get number of rows and columns
        int n = height.size();
        int m = height[0].size();

        // Step 3: dist[i][j] stores the minimum effort
        // required to reach cell (i, j).
        // Initially, all cells have effort = INF.
        vector<vector<int>> dist(n, vector<int>(m, 1e9));

        // Step 4: Direction arrays
        // These represent:
        // up, down, left, right
        int delr[] = {-1, 1, 0, 0};
        int delc[] = {0, 0, -1, 1};

        // Step 5: Starting cell (0,0) requires effort 0
        dist[0][0] = 0;

        // Step 6: Push starting cell into the min-heap
        // {effort, {row, col}}
        pq.push({0, {0, 0}});

        // Step 7: Process cells until priority queue becomes empty
        while (!pq.empty()) {

            // Step 8: Get the cell having minimum effort
            auto it = pq.top();
            pq.pop();

            // Step 9: Extract effort, row and column
            int diff = it.first;
            int row = it.second.first;
            int col = it.second.second;

            // Step 10: If we reached the destination,
            // the current effort is the minimum possible effort.
            if (row == n - 1 && col == m - 1) {
                return diff;
            }

            // Step 11: Try all 4 possible directions
            for (int i = 0; i < 4; i++) {

                // Step 12: Calculate coordinates of the neighbour
                int newr = row + delr[i];
                int newc = col + delc[i];

                // Step 13: Check whether the neighbour is inside the grid
                if (newr >= 0 && newr < n &&
                    newc >= 0 && newc < m) {

                    // Step 14: Calculate effort of moving to the neighbour
                    //
                    // Effort of this edge:
                    // abs(current height - neighbour height)
                    //
                    // Path effort:
                    // maximum edge effort encountered so far.
                    int neweffort = max(
                        abs(height[row][col] - height[newr][newc]),
                        diff
                    );

                    // Step 15: If this path gives a smaller effort
                    // for the neighbour, update its distance.
                    if (neweffort < dist[newr][newc]) {

                        // Step 16: Store the minimum effort
                        dist[newr][newc] = neweffort;

                        // Step 17: Push the updated neighbour
                        // into the priority queue.
                        pq.push({neweffort, {newr, newc}});
                    }
                }
            }
        }

        // Step 18: This is theoretically unreachable
        // because the grid always has a path from start to destination.
        return 0;
    }
};