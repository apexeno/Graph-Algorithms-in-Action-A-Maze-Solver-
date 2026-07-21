# Capstone Project Report : Maze Solver

## Algorithm Roles

| Algorithm | Purpose | Data Structure Used |
|-----------|---------|---------------------|
| **BFS** | Computes unweighted shortest step-distance between every pair of key points (S, coins, G). Produces a symmetric (K+2)×(K+2) distance matrix. | Queue (Week 3) |
| **DFS Backtracking** | Enumerates all K! permutations of coin-visit order over the precomputed matrix. Uses best-so-far pruning to skip partial sums ≥ current best. Run twice: once on the BFS matrix (uniform result) and once on the Dijkstra matrix (weighted result). | Stack / recursion (Week 3) |
| **Dijkstra** | Same role as BFS but respects terrain costs (digits 0–9). Each cell's weight is `ch - '0'` for digits, 1 for S/G/c/dot. Produces a weighted (K+2)×(K+2) matrix. | Priority Queue (Week 4) |
| **A*** | Identical to Dijkstra but adds Manhattan-distance heuristic `h(n) = |r-tr| + |c-tc|`. Must produce the exact same distance matrix as Dijkstra (admissible heuristic guarantees optimality) while expanding fewer cells. | Priority Queue with f = g + h (Week 4/6) |

## A* vs Dijkstra: Expansion Counts

Both algorithms were run as per-pair queries (with early exit on reaching the target) to make expansion counts directly comparable.

| Test Case | Dijkstra Expanded | A* Expanded | Reduction |
|-----------|-------------------|-------------|-----------|
| tiny_2coins | 318 | 206 | 35.2% fewer |
| medium_5coins | 2175 | 1134 | 47.9% fewer |
| weighted_4coins | 350 | 219 | 37.4% fewer |
| stress_8coins | 9009 | 3621 | 59.8% fewer |

A* consistently expands fewer cells than Dijkstra across all tests. The advantage grows with maze size — on the 15×15 stress test, A* explores nearly 60% fewer cells. This is because the Manhattan heuristic strongly guides the search toward the target, avoiding exploration of cells in the opposite direction.

Both algorithms produce identical distance matrices, confirming the heuristic is admissible and consistent.

## Best Coin Order : Medium Maze (5 coins)

**Uniform (BFS):** S → c(3,0) → c(7,0) → c(0,7) → c(3,9) → c(7,9) → G — Total steps: 32
**Weighted (Dijkstra):** S → c(3,0) → c(7,0) → c(0,7) → c(3,9) → c(7,9) → G — Total cost: 32

Since the medium maze has no digit-terrain cells (only `.` and `#`), both runs produce the same order and cost. DFS pruning reduced the search from 120 possible permutations (5!) down to 26 orderings tried.

## RESULTS:

- **Sanity checks pass on all tests:** `dist[i][j] == dist[j][i]`, `dist[i][i] == 0`, `dijkDist >= bfsDist` cell-by-cell, `astarDist == dijkDist` cell-by-cell.
- **Weighted maze (Test 3)** is where BFS and Dijkstra diverge: BFS finds 22 steps (uniform), Dijkstra finds cost 24 (respecting the `9`-cost cells by routing around them).
- **Stress test** completes in ~0.05s with pruning : well under the 2-second limit.
