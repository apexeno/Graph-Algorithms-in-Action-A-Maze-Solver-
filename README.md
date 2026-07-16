# Graph-Algorithms-in-Action-A-Maze-Solver-
https://dsa-kqps.onrender.com/
<br>An intelligent autonomous agent that solves 2D mazes using a two-phase pipeline: 
<br>🔍 Phase 1 — Exploration: The agent spawns blind in an unknown maze. Using BFS and DFS, it systematically explores, locates scattered relics, and maps the territory. <br>⚡ Phase 2 — Optimal Escape: Once relics are collected, the dungeon begins to collapse. The agent must instantly compute the shortest path to the exit using Dijkstra's Algorithm and A* Search, navigating walls and weighted terrain. By the end, every mentee will have implemented and visually compared four foundational graph algorithms — BFS, DFS, Dijkstra, A* — on the same problem, understanding why each suits its specific sub-task rather than treating them as interchangeable. The agent runs on mentee-designed test mazes, with stretch features like fog-of-war, weighted terrain, and multi-coin TSP variants.
# Week 1: 
Goal: Get comfortable with C++ syntax, array/string patterns, Big-O analysis, and bit manipulation.
# Week 2: 
Goal: Master the STL containers and core algorithms : sorting, binary search, recursion, and backtracking.
# Week 3:
Goal: Master pointer-based linear structures and the hashing trick for O(1) lookups.
# Week 4:
Goal: Master the non-linear structures : every traversal cold, BST operations, heap mechanics, and tries.
# Week 5:
Goal: Understand graph representations (adjacency list/matrix, implicit grids) and master BFS and DFS traversals.
# Week 6:
Goal: Implement weighted shortest-path algorithms — Dijkstra and A* - with priority queues and path reconstruction.

# Capstone Project: Maze Solver

A single C++ program that reads a maze containing coins, plans the shortest total path that starts at **S**, collects every coin (**c**), and ends at **G** — using four different graph-search algorithms.

## Compile & Run

**Linux / macOS (Bash)**
```bash
g++ -O2 capstone-project/maze_solver.cpp -o maze_solver
./maze_solver < capstone-project/test_mazes/tiny_2coins.txt
./maze_solver < capstone-project/test_mazes/medium_5coins.txt
./maze_solver < capstone-project/test_mazes/weighted_4coins.txt
./maze_solver < capstone-project/test_mazes/stress_8coins.txt
```

**Windows (PowerShell)**
```powershell
g++ -O2 capstone-project/maze_solver.cpp -o maze_solver.exe
Get-Content capstone-project/test_mazes/tiny_2coins.txt | ./maze_solver.exe
Get-Content capstone-project/test_mazes/medium_5coins.txt | ./maze_solver.exe
Get-Content capstone-project/test_mazes/weighted_4coins.txt | ./maze_solver.exe
Get-Content capstone-project/test_mazes/stress_8coins.txt | ./maze_solver.exe
```

## Algorithms Used
| Algorithm | Role |
|-----------|------|
| **BFS** | Builds unweighted (K+2)×(K+2) distance matrix between all key points |
| **DFS Backtracking** | Enumerates coin-visit permutations with pruning to find optimal order |
| **Dijkstra** | Builds weighted distance matrix using terrain costs |
| **A*** | Same as Dijkstra but with Manhattan heuristic — fewer cell expansions |

## Expected Output (tiny_2coins.txt)

```
=== UNIFORM COST (BFS + DFS) ===
Coins: 2
Best order: S -> c(3,0) -> c(0,7) -> G
Total steps: 17
Path:
S******c
*......*
*...#..*
c......*
.......G

=== WEIGHTED (Dijkstra + A*) ===
Coins: 2
Best order: S -> c(3,0) -> c(0,7) -> G
Total cost: 17
A* cells expanded across all pair queries: 206
Dijkstra cells expanded across all pair queries: 318
Path:
S******c
*......*
*...#..*
c......*
.......G

SUMMARY | BFS pairs computed: 16 | DFS orderings tried: 4 | Dijkstra:318 | A*:206
```

