from __future__ import annotations

from collections import deque
from dataclasses import dataclass
import heapq
from typing import Dict, List, Optional, Set, Tuple

Position = Tuple[int, int]


@dataclass(frozen=True)
class ExplorationResult:
    visit_order: List[Position]
    discovered: Set[Position]
    relics_found: List[Position]


@dataclass(frozen=True)
class PathResult:
    path: List[Position]
    cost: int


@dataclass(frozen=True)
class PipelineResult:
    bfs_exploration: ExplorationResult
    dfs_exploration: ExplorationResult
    dijkstra_escape: PathResult
    astar_escape: PathResult


class MazeSolver:
    """Solve a 2D maze with BFS/DFS exploration and Dijkstra/A* escape."""

    def __init__(self, maze: List[str]):
        if not maze or not maze[0]:
            raise ValueError("Maze cannot be empty")

        width = len(maze[0])
        if any(len(row) != width for row in maze):
            raise ValueError("Maze rows must all have equal length")

        self.maze = maze
        self.height = len(maze)
        self.width = width
        self.start = self._find_token("S")
        self.exit = self._find_token("E")

    def _find_token(self, token: str) -> Position:
        for r, row in enumerate(self.maze):
            for c, value in enumerate(row):
                if value == token:
                    return (r, c)
        raise ValueError(f"Maze must contain '{token}'")

    def _in_bounds(self, pos: Position) -> bool:
        return 0 <= pos[0] < self.height and 0 <= pos[1] < self.width

    def _is_open(self, pos: Position) -> bool:
        return self.maze[pos[0]][pos[1]] != "#"

    def _neighbors(self, pos: Position) -> List[Position]:
        r, c = pos
        candidates = [(r - 1, c), (r, c + 1), (r + 1, c), (r, c - 1)]
        return [p for p in candidates if self._in_bounds(p) and self._is_open(p)]

    def _cell_cost(self, pos: Position) -> int:
        value = self.maze[pos[0]][pos[1]]
        return int(value) if value.isdigit() else 1

    def explore_bfs(self) -> ExplorationResult:
        queue = deque([self.start])
        seen: Set[Position] = {self.start}
        order: List[Position] = []
        relics: List[Position] = []

        while queue:
            current = queue.popleft()
            order.append(current)
            if self.maze[current[0]][current[1]] == "R":
                relics.append(current)

            for nxt in self._neighbors(current):
                if nxt in seen:
                    continue
                seen.add(nxt)
                queue.append(nxt)

        return ExplorationResult(visit_order=order, discovered=seen, relics_found=relics)

    def explore_dfs(self) -> ExplorationResult:
        stack = [self.start]
        seen: Set[Position] = {self.start}
        order: List[Position] = []
        relics: List[Position] = []

        while stack:
            current = stack.pop()
            order.append(current)
            if self.maze[current[0]][current[1]] == "R":
                relics.append(current)

            for nxt in reversed(self._neighbors(current)):
                if nxt in seen:
                    continue
                seen.add(nxt)
                stack.append(nxt)

        return ExplorationResult(visit_order=order, discovered=seen, relics_found=relics)

    def _reconstruct_path(
        self, came_from: Dict[Position, Optional[Position]], goal: Position
    ) -> List[Position]:
        if goal not in came_from:
            return []

        path = [goal]
        current = goal
        while came_from[current] is not None:
            current = came_from[current]  # type: ignore[assignment]
            path.append(current)
        path.reverse()
        return path

    def shortest_path_dijkstra(self, start: Position, goal: Position) -> PathResult:
        distances: Dict[Position, int] = {start: 0}
        came_from: Dict[Position, Optional[Position]] = {start: None}
        queue: List[Tuple[int, Position]] = [(0, start)]

        while queue:
            dist, current = heapq.heappop(queue)
            if dist > distances.get(current, float("inf")):
                continue
            if current == goal:
                break

            for nxt in self._neighbors(current):
                ndist = dist + self._cell_cost(nxt)
                if ndist >= distances.get(nxt, float("inf")):
                    continue
                distances[nxt] = ndist
                came_from[nxt] = current
                heapq.heappush(queue, (ndist, nxt))

        path = self._reconstruct_path(came_from, goal)
        if not path:
            return PathResult(path=[], cost=-1)
        return PathResult(path=path, cost=distances[goal])

    def shortest_path_astar(self, start: Position, goal: Position) -> PathResult:
        def heuristic(a: Position, b: Position) -> int:
            return abs(a[0] - b[0]) + abs(a[1] - b[1])

        g_score: Dict[Position, int] = {start: 0}
        came_from: Dict[Position, Optional[Position]] = {start: None}
        queue: List[Tuple[int, Position]] = [(heuristic(start, goal), start)]

        while queue:
            _, current = heapq.heappop(queue)
            if current == goal:
                break

            current_g = g_score[current]
            for nxt in self._neighbors(current):
                tentative = current_g + self._cell_cost(nxt)
                if tentative >= g_score.get(nxt, float("inf")):
                    continue
                came_from[nxt] = current
                g_score[nxt] = tentative
                f_score = tentative + heuristic(nxt, goal)
                heapq.heappush(queue, (f_score, nxt))

        path = self._reconstruct_path(came_from, goal)
        if not path:
            return PathResult(path=[], cost=-1)
        return PathResult(path=path, cost=g_score[goal])

    def run_two_phase_pipeline(self) -> PipelineResult:
        bfs = self.explore_bfs()
        dfs = self.explore_dfs()

        phase2_start = bfs.relics_found[-1] if bfs.relics_found else self.start
        dijkstra_path = self.shortest_path_dijkstra(phase2_start, self.exit)
        astar_path = self.shortest_path_astar(phase2_start, self.exit)

        return PipelineResult(
            bfs_exploration=bfs,
            dfs_exploration=dfs,
            dijkstra_escape=dijkstra_path,
            astar_escape=astar_path,
        )
