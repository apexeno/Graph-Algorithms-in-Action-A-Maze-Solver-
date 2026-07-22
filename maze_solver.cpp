

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cassert>
#include <functional>
#include <cstring>
#include <chrono>


using namespace std;



struct Grid {
    int R, C;
    vector<string> cells;
};

struct Result {
    int cost;                        // total steps or total weight
    vector<pair<int,int>> path;      // cells in order
    int expanded;                    // cells visited by the search
};



vector<pair<int,int>> neighbours(const Grid& g, int r, int c) {
    static const int dr[] = {-1, 1, 0, 0};
    static const int dc[] = {0, 0, -1, 1};
    vector<pair<int,int>> nbrs;
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr >= 0 && nr < g.R && nc >= 0 && nc < g.C && g.cells[nr][nc] != '#') {
            nbrs.push_back({nr, nc});
        }
    }
    return nbrs;
}



static int cellCost(const Grid& g, int r, int c) {
    char ch = g.cells[r][c];
    if (ch >= '0' && ch <= '9') return ch - '0';
    return 1; // S, G, c, '.' all cost 1
}



static vector<pair<int,int>> reconstructPath(
    const vector<vector<pair<int,int>>>& parent,
    pair<int,int> s, pair<int,int> t)
{
    vector<pair<int,int>> path;
    pair<int,int> cur = t;
    while (cur != make_pair(-1, -1)) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    return path;
}


Result bfs(const Grid& g, pair<int,int> s, pair<int,int> t) {
    Result res;
    res.cost = -1;
    res.expanded = 0;

    vector<vector<int>> dist(g.R, vector<int>(g.C, -1));
    vector<vector<pair<int,int>>> parent(g.R, vector<pair<int,int>>(g.C, {-1, -1}));

    queue<pair<int,int>> q;
    dist[s.first][s.second] = 0;
    q.push(s);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        res.expanded++;

        if (make_pair(r, c) == t) {
            res.cost = dist[r][c];
            res.path = reconstructPath(parent, s, t);
            return res;
        }

        for (auto [nr, nc] : neighbours(g, r, c)) {
            if (dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                parent[nr][nc] = {r, c};
                q.push({nr, nc});
            }
        }
    }

    // Target unreachable
    return res;
}


Result dfsPath(const Grid& g, pair<int,int> s, pair<int,int> t) {
    Result res;
    res.cost = -1;
    res.expanded = 0;

    vector<vector<bool>> visited(g.R, vector<bool>(g.C, false));
    visited[s.first][s.second] = true;

    // simple dfs to find a path
    stack<pair<int,int>> dfsStack;
    vector<vector<pair<int,int>>> parent(g.R, vector<pair<int,int>>(g.C, {-1, -1}));
    dfsStack.push(s);

    while (!dfsStack.empty()) {
        auto [r, c] = dfsStack.top();
        dfsStack.pop();
        res.expanded++;

        if (make_pair(r, c) == t) {
            res.path = reconstructPath(parent, s, t);
            res.cost = (int)res.path.size() - 1;
            return res;
        }

        for (auto [nr, nc] : neighbours(g, r, c)) {
            if (!visited[nr][nc]) {
                visited[nr][nc] = true;
                parent[nr][nc] = {r, c};
                dfsStack.push({nr, nc});
            }
        }
    }

    return res;
}



Result dijkstra(const Grid& g, pair<int,int> s, pair<int,int> t) {
    Result res;
    res.cost = -1;
    res.expanded = 0;

    vector<vector<int>> dist(g.R, vector<int>(g.C, INT_MAX));
    vector<vector<pair<int,int>>> parent(g.R, vector<pair<int,int>>(g.C, {-1, -1}));
    vector<vector<bool>> visited(g.R, vector<bool>(g.C, false));

    // min-heap: (cost, row, col)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;

    dist[s.first][s.second] = 0;
    pq.push({0, s.first, s.second});

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();

        if (visited[r][c]) continue;
        visited[r][c] = true;
        res.expanded++;

        if (make_pair(r, c) == t) {
            res.cost = dist[r][c];
            res.path = reconstructPath(parent, s, t);
            return res;
        }

        for (auto [nr, nc] : neighbours(g, r, c)) {
            int w = cellCost(g, nr, nc);
            if (dist[r][c] + w < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + w;
                parent[nr][nc] = {r, c};
                pq.push({dist[nr][nc], nr, nc});
            }
        }
    }

    return res;
}



Result astar(const Grid& g, pair<int,int> s, pair<int,int> t) {
    Result res;
    res.cost = -1;
    res.expanded = 0;

    auto heuristic = [&](int r, int c) -> int {
        return abs(r - t.first) + abs(c - t.second);
    };

    vector<vector<int>> gScore(g.R, vector<int>(g.C, INT_MAX));
    vector<vector<pair<int,int>>> parent(g.R, vector<pair<int,int>>(g.C, {-1, -1}));
    vector<vector<bool>> visited(g.R, vector<bool>(g.C, false));

    // min-heap: (f, g-cost, row, col)
    priority_queue<tuple<int,int,int,int>, vector<tuple<int,int,int,int>>, greater<tuple<int,int,int,int>>> pq;

    gScore[s.first][s.second] = 0;
    pq.push({heuristic(s.first, s.second), 0, s.first, s.second});

    while (!pq.empty()) {
        auto [f, gc, r, c] = pq.top();
        pq.pop();

        if (visited[r][c]) continue;
        visited[r][c] = true;
        res.expanded++;

        if (make_pair(r, c) == t) {
            res.cost = gScore[r][c];
            res.path = reconstructPath(parent, s, t);
            return res;
        }

        for (auto [nr, nc] : neighbours(g, r, c)) {
            int w = cellCost(g, nr, nc);
            int newG = gScore[r][c] + w;
            if (newG < gScore[nr][nc]) {
                gScore[nr][nc] = newG;
                parent[nr][nc] = {r, c};
                pq.push({newG + heuristic(nr, nc), newG, nr, nc});
            }
        }
    }

    return res;
}



static int dfs_cnt; // global counter for orderings tried

static void dfsBacktrack(
    const vector<vector<int>>& dist,
    int startIdx, int goalIdx,
    vector<int>& coins,       // coin indices (1..K)
    vector<bool>& used,
    vector<int>& current,     // current permutation so far
    int partialCost,
    int& bestCost,
    vector<int>& bestOrder)
{
    int lastIdx = current.empty() ? startIdx : current.back();
    
    if ((int)current.size() == (int)coins.size()) {
        dfs_cnt++;
        int total = partialCost + dist[lastIdx][goalIdx];
        if (total < bestCost) {
            bestCost = total;
            bestOrder = current;
        }
        return;
    }

    for (int i = 0; i < (int)coins.size(); i++) {
        if (used[i]) continue;

        int nextIdx = coins[i];
        int newCost = partialCost + dist[lastIdx][nextIdx];

        // Pruning: abandon if partial cost already >= best
        if (newCost >= bestCost) continue;

        used[i] = true;
        current.push_back(nextIdx);

        dfsBacktrack(dist, startIdx, goalIdx, coins, used,
                     current, newCost, bestCost, bestOrder);

        current.pop_back();
        used[i] = false;
    }
}

int bestOrder(const vector<vector<int>>& dist,
              int startIdx, int goalIdx,
              vector<int>& outOrder)
{
    int K = (int)dist.size() - 2; // total key points = K+2
    vector<int> coins;
    for (int i = 0; i < (int)dist.size(); i++) {
        if (i != startIdx && i != goalIdx) {
            coins.push_back(i);
        }
    }

    dfs_cnt = 0;

    int bestCost = INT_MAX;
    vector<bool> used(coins.size(), false);
    vector<int> current;
    outOrder.clear();

    dfsBacktrack(dist, startIdx, goalIdx, coins, used,
                 current, 0, bestCost, outOrder);

    return bestCost;
}



static vector<string> overlayPath(const Grid& g,
                                  const vector<pair<int,int>>& fullPath)
{
    vector<string> vis = g.cells;
    for (auto [r, c] : fullPath) {
        char ch = g.cells[r][c];
        if (ch == 'S' || ch == 'G' || ch == 'c') {
            // Keep special characters visible
        } else {
            vis[r][c] = '*';
        }
    }
    return vis;
}



using PathFn = function<Result(const Grid&, pair<int,int>, pair<int,int>)>;

static vector<pair<int,int>> buildFullPath(
    const Grid& g,
    const vector<pair<int,int>>& keyPoints,
    const vector<int>& order,   // coin indices in visit order
    int startIdx, int goalIdx,
    PathFn pathfinder)
{
    vector<pair<int,int>> fullPath;

    
    vector<int> seq;
    seq.push_back(startIdx);
    for (int idx : order) seq.push_back(idx);
    seq.push_back(goalIdx);

    for (int i = 0; i + 1 < (int)seq.size(); i++) {
        auto res = pathfinder(g, keyPoints[seq[i]], keyPoints[seq[i + 1]]);
        if (res.cost < 0) return {}; // unreachable

       
        int startJ = (i == 0) ? 0 : 1;
        for (int j = startJ; j < (int)res.path.size(); j++) {
            fullPath.push_back(res.path[j]);
        }
    }

    return fullPath;
}

// main 

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── Read input ──
    int R, C;
    cin >> R >> C;

    int sr, sc, gr, gc;
    cin >> sr >> sc >> gr >> gc;

    Grid g;
    g.R = R;
    g.C = C;
    g.cells.resize(R);
    for (int i = 0; i < R; i++) {
        cin >> g.cells[i];
    }

    // ── Identify key points: S, coins, G ──
    pair<int,int> startPos = {sr, sc};
    pair<int,int> goalPos = {gr, gc};

    vector<pair<int,int>> coins;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (g.cells[r][c] == 'c') {
                coins.push_back({r, c});
            }
        }
    }

    int K = (int)coins.size();

    // Key points: index 0 = S, 1..K = coins, K+1 = G
    vector<pair<int,int>> keyPoints;
    keyPoints.push_back(startPos);
    for (auto& cp : coins) keyPoints.push_back(cp);
    keyPoints.push_back(goalPos);

    int N = K + 2; // number of key points
    int startIdx = 0;
    int goalIdx = N - 1;

    

    // Build BFS distance matrix
    vector<vector<int>> bfsDist(N, vector<int>(N, 0));
    int bfs_exp = 0;
    int bfs_pairs = 0;

    
    vector<vector<Result>> bfs_res(N, vector<Result>(N));

    for (int i = 0; i < N; i++) {
        
        vector<vector<int>> dist(g.R, vector<int>(g.C, -1));
        vector<vector<pair<int,int>>> parent(g.R, vector<pair<int,int>>(g.C, {-1, -1}));

        queue<pair<int,int>> q;
        auto si = keyPoints[i];
        dist[si.first][si.second] = 0;
        q.push(si);
        int expanded = 0;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            expanded++;

            for (auto [nr, nc] : neighbours(g, r, c)) {
                if (dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[nr][nc] = {r, c};
                    q.push({nr, nc});
                }
            }
        }

        bfs_exp += expanded;

        // Extract distances to all key points
        for (int j = 0; j < N; j++) {
            auto tj = keyPoints[j];
            bfsDist[i][j] = dist[tj.first][tj.second];
            bfs_pairs++;

            // Store result for path reconstruction
            if (i != j && dist[tj.first][tj.second] >= 0) {
                bfs_res[i][j].cost = dist[tj.first][tj.second];
                bfs_res[i][j].path = reconstructPath(parent, si, tj);
                bfs_res[i][j].expanded = expanded;
            } else {
                bfs_res[i][j].cost = (i == j) ? 0 : -1;
                bfs_res[i][j].expanded = expanded;
            }
        }
    }




  
    bool allReachable = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (bfsDist[i][j] < 0) {
                allReachable = false;
            }
        }
    }

    vector<int> ord1;
    dfs_cnt = 0;
    int cost1 = bestOrder(bfsDist, startIdx, goalIdx, ord1);
    int dfs_ord1 = dfs_cnt;



   
    vector<pair<int,int>> path1 = buildFullPath(
        g, keyPoints, ord1, startIdx, goalIdx,
        [&](const Grid& grid, pair<int,int> a, pair<int,int> b) -> Result {
            return bfs(grid, a, b);
        });

 
    cout << "=== UNIFORM COST (BFS + DFS) ===" << endl;
    cout << "Coins: " << K << endl;

    if (!allReachable) {
        cout << "Path found: no" << endl;
    } else {
        cout << "Best order: S";
        for (int idx : ord1) {
            auto [r, c] = keyPoints[idx];
            cout << " -> c(" << r << "," << c << ")";
        }
        cout << " -> G" << endl;
        cout << "Total steps: " << cost1 << endl;
        cout << "Path:" << endl;

        auto vis = overlayPath(g, path1);
        for (auto& row : vis) cout << row << endl;
    }

    cout << endl;

    

    
    vector<vector<int>> dijkDist(N, vector<int>(N, 0));
    int dijk_exp = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                dijkDist[i][j] = 0;
                continue;
            }
            Result res = dijkstra(g, keyPoints[i], keyPoints[j]);
            dijkDist[i][j] = res.cost;
            dijk_exp += res.expanded;
        }
    }

   
    vector<vector<int>> astarDist(N, vector<int>(N, 0));
    int astar_exp = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                astarDist[i][j] = 0;
                continue;
            }
            Result res = astar(g, keyPoints[i], keyPoints[j]);
            astarDist[i][j] = res.cost;
            astar_exp += res.expanded;
        }
    }



    
    vector<int> ord2;
    dfs_cnt = 0;
    int cost2 = bestOrder(dijkDist, startIdx, goalIdx, ord2);
    int dfs_ord2 = dfs_cnt;

    // Build full path for weighted solution
    vector<pair<int,int>> path2 = buildFullPath(
        g, keyPoints, ord2, startIdx, goalIdx,
        [&](const Grid& grid, pair<int,int> a, pair<int,int> b) -> Result {
            return dijkstra(grid, a, b);
        });

    // ── Print weighted block ──
    cout << "=== WEIGHTED (Dijkstra + A*) ===" << endl;
    cout << "Coins: " << K << endl;

    if (!allReachable) {
        cout << "Path found: no" << endl;
    } else {
        cout << "Best order: S";
        for (int idx : ord2) {
            auto [r, c] = keyPoints[idx];
            cout << " -> c(" << r << "," << c << ")";
        }
        cout << " -> G" << endl;
        cout << "Total cost: " << cost2 << endl;
        cout << "A* cells expanded across all pair queries: " << astar_exp << endl;
        cout << "Dijkstra cells expanded across all pair queries: " << dijk_exp << endl;
        cout << "Path:" << endl;

        auto vis = overlayPath(g, path2);
        for (auto& row : vis) cout << row << endl;
    }

    cout << endl;

    // Summary
    cout << "\n--- Execution Summary ---" << endl;
    cout << "BFS computations: " << bfs_pairs << endl;
    cout << "DFS orderings: " << dfs_ord1 + dfs_ord2 << endl;
    cout << "Expanded states -> Dijkstra: " << dijk_exp << " | A*: " << astar_exp << endl;

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end_time - start_time;
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}
