// 1631. Path With Minimum Effort
// Difficulty: Medium
// Topic: Graph - Dijkstra / Binary Search + BFS

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
        effort[0][0] = 0;

        // Min-heap: {effort, row, col}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.push({0, 0, 0});

        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pq.empty()) {
            auto [e, r, c] = pq.top();
            pq.pop();

            if (r == m - 1 && c == n - 1) return e;
            if (e > effort[r][c]) continue;

            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int newEffort = max(e, abs(heights[nr][nc] - heights[r][c]));
                    if (newEffort < effort[nr][nc]) {
                        effort[nr][nc] = newEffort;
                        pq.push({newEffort, nr, nc});
                    }
                }
            }
        }
        return 0;
    }
};
