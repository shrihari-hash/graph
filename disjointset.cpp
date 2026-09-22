#include<bits/stdc++.h>
using namespace std;

int main(){
    // Disjoint Set (Union-Find) data structure
    // Supports two operations efficiently:
    // 1. Find - which "set"/component a node belongs to
    // 2. Union - merge two sets/components together
    // Uses "Union by Rank" + "Path Compression" for near O(1) operations (amortized)
    class DisjointSet {
        vector<int> rank, parent; 
        // rank[i]  -> approximate "height" of tree rooted at i (used to keep tree flat)
        // parent[i]-> parent of node i (parent[i] == i means i is the root of its set)

    public:
        // Constructor: initializes n+1 nodes (0 to n), each node is its own parent initially
        // i.e., initially every node is in its own separate set
        DisjointSet(int n){
            rank.resize(n+1, 0);     // all ranks start at 0
            parent.resize(n+1);

            for(int i = 0; i <=n; i++){
                parent[i] = i;        // each node is its own leader/root initially
            }
         
        }

        // Find the "ultimate parent" (root/leader) of the set that 'node' belongs to
        // Uses PATH COMPRESSION: while recursing back up, every visited node's 
        // parent pointer is updated to point directly to the root.
        // This flattens the tree for future queries, making them much faster.
        int finduPar(int node){
            if(node == parent[node])   // base case: node is its own parent => it's the root
                return node;

            // recursively find root, and compress path by directly attaching 
            // 'node' to the root instead of its old parent
            return parent[node] = finduPar(parent[node]);
        }

        // Union two sets containing u and v, using UNION BY RANK
        // Attaches the smaller-rank tree under the root of the larger-rank tree,
        // keeping overall tree height small (avoids long chains).
        void unionByRank(int u, int v){
            int ulp_u = finduPar(u);   // find root of u's set
            int ulp_v = finduPar(v);   // find root of v's set

            if(ulp_u == ulp_v) return; // already in the same set, nothing to do

            if(rank[ulp_u] < rank[ulp_v]){
                // v's tree is "taller" -> attach u's root under v's root
                parent[ulp_u] = ulp_v;
            } 
            else if(rank[ulp_v] < rank[ulp_u]){
                // u's tree is "taller" -> attach v's root under u's root
                parent[ulp_v] = ulp_u;
            } 
            else {
                // equal rank -> arbitrarily attach v's root under u's root
                // and increase u's rank by 1 (tree got taller)
                parent[ulp_v] = ulp_u;
                rank[ulp_u]++;
            }
        }
    };

    return 0;
}
