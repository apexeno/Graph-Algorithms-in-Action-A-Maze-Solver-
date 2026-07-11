// 1192. Critical Connections in a Network
// Difficulty: Hard
// Topic: Graph - Tarjan's Bridge-Finding Algorithm

class Solution {
public:
    int timer = 0;
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<vector<int>> bridges;

    void dfs(int u, int parent) {
        disc[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == parent) continue;
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        adj.resize(n);
        disc.assign(n, -1);
        low.assign(n, -1);

        for (auto& c : connections) {
            adj[c[0]].push_back(c[1]);
            adj[c[1]].push_back(c[0]);
        }

        dfs(0, -1);
        return bridges;
    }
};
