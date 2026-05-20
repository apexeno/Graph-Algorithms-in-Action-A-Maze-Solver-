import unittest

from maze_solver import MazeSolver


class MazeSolverTests(unittest.TestCase):
    def test_bfs_and_dfs_exploration_find_all_relics(self):
        maze = [
            "S..#R",
            ".##..",
            ".R..E",
        ]

        solver = MazeSolver(maze)
        bfs = solver.explore_bfs()
        dfs = solver.explore_dfs()

        self.assertEqual(set(bfs.relics_found), {(0, 4), (2, 1)})
        self.assertEqual(set(dfs.relics_found), {(0, 4), (2, 1)})
        self.assertEqual(bfs.discovered, dfs.discovered)

    def test_dijkstra_and_astar_respect_weighted_terrain(self):
        maze = [
            "S91",
            "111",
            "11E",
        ]

        solver = MazeSolver(maze)
        dijkstra = solver.shortest_path_dijkstra(solver.start, solver.exit)
        astar = solver.shortest_path_astar(solver.start, solver.exit)

        self.assertEqual(dijkstra.cost, 4)
        self.assertEqual(astar.cost, 4)
        self.assertEqual(dijkstra.path, astar.path)

    def test_two_phase_pipeline_starts_escape_after_last_bfs_relic(self):
        maze = [
            "S.R",
            "...",
            "R.E",
        ]

        solver = MazeSolver(maze)
        result = solver.run_two_phase_pipeline()

        self.assertEqual(result.bfs_exploration.relics_found[-1], (2, 0))
        self.assertEqual(result.dijkstra_escape.path[0], (2, 0))
        self.assertEqual(result.astar_escape.path[0], (2, 0))


if __name__ == "__main__":
    unittest.main()
