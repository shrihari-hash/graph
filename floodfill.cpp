class Solution {

private:

    // ----------------------------------------------------------
    // DFS FUNCTION
    //
    // This function colors the current cell and recursively
    // colors all connected cells having the same initial color.
    // ----------------------------------------------------------
    void dfs(int row, int col,
             vector<vector<int>>& ans,
             vector<vector<int>>& image,
             int iniColor,
             int newColor,
             int delRow[],
             int delCol[]) {

        // ------------------------------------------------------
        // STEP 1 : Color the current cell.
        //
        // We immediately change its color so that it is marked
        // as visited and will not be processed again.
        // ------------------------------------------------------
        ans[row][col] = newColor;

        // Number of rows and columns
        int n = image.size();
        int m = image[0].size();

        // ------------------------------------------------------
        // STEP 2 : Visit all four neighbouring cells.
        //
        // Directions:
        // Up, Right, Down, Left
        // ------------------------------------------------------
        for (int i = 0; i < 4; i++) {

            // Compute neighbour coordinates
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];

            // --------------------------------------------------
            // Valid neighbour conditions:
            //
            // 1. Inside the matrix
            // 2. Has the same initial color
            // 3. Has not already been colored with newColor
            // --------------------------------------------------
            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                image[nrow][ncol] == iniColor &&
                ans[nrow][ncol] != newColor) {

                // Continue DFS on the neighbour
                dfs(nrow, ncol,
                    ans,
                    image,
                    iniColor,
                    newColor,
                    delRow,
                    delCol);
            }
        }
    }

public:

    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr,
                                  int sc,
                                  int color) {

        // ------------------------------------------------------
        // STEP 1 : Store the initial color.
        //
        // Flood fill spreads only through cells having this color.
        // ------------------------------------------------------
        int iniColor = image[sr][sc];

        // ------------------------------------------------------
        // STEP 2 : Create the answer matrix.
        //
        // We copy the original image and perform all changes
        // on this matrix.
        // ------------------------------------------------------
        vector<vector<int>> ans = image;

        // ------------------------------------------------------
        // STEP 3 : Direction arrays.
        //
        // delRow and delCol together represent:
        //
        // (-1,0) -> Up
        // (0,1)  -> Right
        // (1,0)  -> Down
        // (0,-1) -> Left
        // ------------------------------------------------------
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};

        // ------------------------------------------------------
        // STEP 4 : Start DFS from the source cell.
        //
        // DFS will color the source cell and every connected
        // cell having the same initial color.
        // ------------------------------------------------------
        dfs(sr,
            sc,
            ans,
            image,
            iniColor,
            color,
            delRow,
            delCol);

        // ------------------------------------------------------
        // STEP 5 : Return the final colored image.
        // ------------------------------------------------------
        return ans;
    }
};