// 1584. Min Cost to Connect All Points (MST)
// Difficulty: Medium
// Topic: Graph - Minimum Spanning Tree (Prim's / Kruskal's)

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false);
        // Min-heap: {cost, point_index}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, 0});

        int totalCost = 0;
        int edgesUsed = 0;

        while (edgesUsed < n) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;
            totalCost += cost;
            edgesUsed++;

            for (int v = 0; v < n; v++) {
                if (!inMST[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    pq.push({dist, v});
                }
            }
        }
        return totalCost;
    }
};
