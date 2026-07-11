// 269. Alien Dictionary (Topological Sort)
// Difficulty: Hard
// Topic: Graph - Topological Sort / BFS

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> indegree;

        // Initialize all characters
        for (auto& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }

        // Build graph from adjacent word pairs
        for (int i = 0; i < words.size() - 1; i++) {
            string& w1 = words[i];
            string& w2 = words[i + 1];
            int minLen = min(w1.size(), w2.size());

            // Invalid case: prefix comes after longer word
            if (w1.size() > w2.size() && w1.substr(0, minLen) == w2.substr(0, minLen))
                return "";

            for (int j = 0; j < minLen; j++) {
                if (w1[j] != w2[j]) {
                    if (!adj[w1[j]].count(w2[j])) {
                        adj[w1[j]].insert(w2[j]);
                        indegree[w2[j]]++;
                    }
                    break;
                }
            }
        }

        // BFS topological sort
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }

        string result;
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            result += c;
            for (char next : adj[c]) {
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        return result.size() == indegree.size() ? result : "";
    }
};
