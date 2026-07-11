// 684. Redundant Connection
// Difficulty: Medium
// Topic: Graph - Disjoint Set Union (Union-Find)

class Solution {
public:
    vector<int> parent, rank_;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        parent.resize(n + 1);
        rank_.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);

        for (auto& e : edges) {
            if (!unite(e[0], e[1])) {
                return e;
            }
        }
        return {};
    }
};
