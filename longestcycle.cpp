class Solution {
private:
    int longestCycleLen = -1;

    void dfsFindLongestCycle(
        int cycleLen,
        int node,
        vector<int>& currentPath,
        vector<int>& visitedNodeList,
        vector<int>& edges
    ) {
        // Increase depth
        cycleLen++;

        // Store the position of this node in current DFS path
        currentPath[node] = cycleLen;

        // Mark node as globally visited
        visitedNodeList[node] = 1;

        // Get the only neighbour of this node
        int nbr = edges[node];

        // If there is a neighbour
        if (nbr != -1) {

            // Neighbour has never been visited
            if (!visitedNodeList[nbr]) {

                dfsFindLongestCycle(
                    cycleLen,
                    nbr,
                    currentPath,
                    visitedNodeList,
                    edges
                );
            }

            // Neighbour is already visited
            else if (currentPath[nbr] != 0) {

                // Cycle found
                int currCycleLen =
                    currentPath[node] - currentPath[nbr] + 1;

                longestCycleLen =
                    max(longestCycleLen, currCycleLen);
            }
        }

        // Remove node from current DFS path
        currentPath[node] = 0;
    }

public:
    int longestCycle(vector<int>& edges) {

        int numOfNodes = edges.size();

        vector<int> visitedNodeList(numOfNodes, 0);

        vector<int> currentPath(numOfNodes, 0);

        // Start DFS from every unvisited node
        for (int i = 0; i < numOfNodes; i++) {

            if (visitedNodeList[i] != 1) {

                dfsFindLongestCycle(
                    0,
                    i,
                    currentPath,
                    visitedNodeList,
                    edges
                );
            }
        }

        return longestCycleLen;
    }
};

