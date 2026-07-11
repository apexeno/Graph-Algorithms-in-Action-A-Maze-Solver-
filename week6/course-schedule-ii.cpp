// 210. Course Schedule II
// Difficulty: Medium
// Topic: Graph - Topological Sort / BFS (Kahn's Algorithm)

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        for (auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> order;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            for (int next : adj[course]) {
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        return order.size() == numCourses ? order : vector<int>();
    }
};
