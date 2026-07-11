// 721. Accounts Merge (DSU)
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

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        parent.resize(n);
        rank_.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);

        // Map email -> first account index that owns it
        unordered_map<string, int> emailToId;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string& email = accounts[i][j];
                if (emailToId.count(email)) {
                    unite(i, emailToId[email]);
                } else {
                    emailToId[email] = i;
                }
            }
        }

        // Group emails by root parent
        unordered_map<int, set<string>> merged;
        for (auto& [email, id] : emailToId) {
            merged[find(id)].insert(email);
        }

        // Build result
        vector<vector<string>> result;
        for (auto& [id, emails] : merged) {
            vector<string> account = {accounts[id][0]};
            account.insert(account.end(), emails.begin(), emails.end());
            result.push_back(account);
        }
        return result;
    }
};
