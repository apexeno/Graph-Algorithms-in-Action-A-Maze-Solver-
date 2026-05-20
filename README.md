# Graph-Algorithms-in-Action-A-Maze-Solver-

An intelligent autonomous agent that solves 2D mazes using a two-phase pipeline:

1. **Phase 1 — Exploration**
   - `explore_bfs()` and `explore_dfs()` systematically explore an unknown maze.
   - Both track discovered territory and relic locations.
2. **Phase 2 — Optimal Escape**
   - After relic collection, the agent computes shortest escape paths to the exit with
     `shortest_path_dijkstra()` and `shortest_path_astar()`.
   - Weighted terrain is supported through numeric cell costs (`1`-`9`).

## Quick start

```python
from maze_solver import MazeSolver

maze = [
    "S..#R",
    ".##..",
    ".R..E",
]

solver = MazeSolver(maze)
result = solver.run_two_phase_pipeline()

print(result.bfs_exploration.relics_found)
print(result.dijkstra_escape.path, result.dijkstra_escape.cost)
```

## Run tests

```bash
python -m unittest discover -s tests -v
```
