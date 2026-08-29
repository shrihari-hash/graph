class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {

        int n = board.size();

        int node = 1;

        // true  -> left to right
        // false -> right to left
        bool flag = true;

        vector<int> connection(n * n + 1, -1);

        // Convert board into 1D positions
        // Start from the bottom row
        for (int i = n - 1; i >= 0; i--) {

            if (flag) {

                // Left -> Right
                for (int j = 0; j < n; j++) {

                    if (board[i][j] != -1) {
                        connection[node] = board[i][j];
                    }

                    node++;
                }

            } else {

                // Right -> Left
                for (int j = n - 1; j >= 0; j--) {

                    if (board[i][j] != -1) {
                        connection[node] = board[i][j];
                    }

                    node++;
                }
            }

            flag = !flag;
        }


        // Build graph
        vector<vector<int>> graph(n * n + 1);

        for (int i = 1; i <= n * n - 1; i++) {

            // Dice can give 1 to 6
            for (int count = 1; count <= 6; count++) {

                int nbr = i + count;

                if (nbr <= n * n) {

                    // Snake or ladder exists
                    if (connection[nbr] != -1) {
                        graph[i].push_back(connection[nbr]);
                    }

                    // No snake or ladder
                    else {
                        graph[i].push_back(nbr);
                    }
                }
            }
        }


        // BFS
        int level = 0;

        vector<int> visited(n * n + 1, 0);

        queue<int> q;

        q.push(1);
        visited[1] = 1;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                int pos = q.front();
                q.pop();

                // Reached destination
                if (pos == n * n) {
                    return level;
                }

                for (auto nbr : graph[pos]) {

                    if (!visited[nbr]) {

                        visited[nbr] = 1;
                        q.push(nbr);
                    }
                }
            }

            // One BFS level = one dice throw
            level++;
        }

        return -1;
    }
};