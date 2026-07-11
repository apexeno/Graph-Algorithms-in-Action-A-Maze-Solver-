// 332. Reconstruct Itinerary
// Difficulty: Hard
// Topic: Graph - Eulerian Path / DFS

class Solution {
public:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj;
    vector<string> result;

    void dfs(const string& airport) {
        while (!adj[airport].empty()) {
            string next = adj[airport].top();
            adj[airport].pop();
            dfs(next);
        }
        result.push_back(airport);
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& t : tickets) {
            adj[t[0]].push(t[1]);
        }

        dfs("JFK");
        reverse(result.begin(), result.end());
        return result;
    }
};
