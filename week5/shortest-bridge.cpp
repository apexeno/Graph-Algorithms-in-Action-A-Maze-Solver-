// 934. Shortest Bridge
// Difficulty: Medium
// Topic: Graph - DFS + BFS

class Solution {
public:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(vector<vector<int>>& grid, queue<pair<int, int>>& q, int r, int c) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] != 1)
            return;
        grid[r][c] = 2;
        q.push({r, c});
        for (auto& d : dirs) {
            dfs(grid, q, r + d[0], c + d[1]);
        }
    }

    int shortestBridge(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        bool found = false;

        for (int i = 0; i < m && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, q, i, j);
                    found = true;
                }
            }
        }

        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int k = 0; k < size; k++) {
                auto [r, c] = q.front();
                q.pop();
                for (auto& d : dirs) {
                    int nr = r + d[0], nc = c + d[1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        if (grid[nr][nc] == 1) return steps;
                        if (grid[nr][nc] == 0) {
                            grid[nr][nc] = 2;
                            q.push({nr, nc});
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
