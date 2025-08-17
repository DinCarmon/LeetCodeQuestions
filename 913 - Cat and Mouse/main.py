from enum import Enum
from typing import List


class Turn(Enum):
    CAT = 1
    MOUSE = 2


class GameVerdict(Enum):
    MOUSE_WIN = 1
    CAT_WIN = 2
    DRAW = 0
    NOT_COMPUTED_YET = -1


class Solution:
    def buildBFS(self, graph) -> List[int]:
        bfs_distance = [-1] * len(graph)
        tmp = [0]
        bfs_dis = 0
        while (len(tmp) > 0):
            new_tmp = []
            for node_i in tmp:
                bfs_distance[node_i] = bfs_dis
                for nbr in graph[node_i]:
                    if bfs_distance[nbr] == -1:
                        new_tmp.append(nbr)
            tmp = new_tmp
            bfs_dis += 1
        return bfs_distance

    """def catMouseGame(self, graph: List[List[int]]) -> int:
        n = len(graph)

        # First build bfs priority
        bfs_dis = self.buildBFS(graph)
        # Add index for each node:
        bfs_dis_copy = [(i, bfs_dis[i]) for i in range(len(bfs_dis))]
        bfs_sorted = sorted(bfs_dis_copy, key = lambda x: x[1])

        # We will go from low bfs to high bfs.
        # For each node 
        win_list = [-1] * n
        win_list[0] = list(range(n)).remove(0)



        print(bfs_sorted)

        return 0"""

    saved_results = {}
    in_computation = set()

    def gameResult(self, graph, catPos, mousePos, turn: Turn) -> GameVerdict:
        key = (catPos, mousePos, turn)
        self.in_computation.add(key)
        if key in self.saved_results:
            self.in_computation.remove(key)
            return self.saved_results[key]
        if mousePos == 0:
            self.saved_results[key] = GameVerdict.MOUSE_WIN
            self.in_computation.remove(key)
            return GameVerdict.MOUSE_WIN
        if mousePos == catPos:
            self.saved_results[key] = GameVerdict.CAT_WIN
            self.in_computation.remove(key)
            return GameVerdict.CAT_WIN

        if turn == Turn.MOUSE:
            definite_cat_win = True
            for possible_next_pos in graph[mousePos]:
                if (catPos, possible_next_pos, Turn.CAT) in self.in_computation:
                    continue
                possible_verdict = self.gameResult(graph, catPos, possible_next_pos, Turn.CAT)
                if possible_verdict == GameVerdict.MOUSE_WIN:
                    self.saved_results[key] = GameVerdict.MOUSE_WIN
                    self.in_computation.remove(key)
                    return GameVerdict.MOUSE_WIN
                elif possible_verdict == GameVerdict.DRAW:
                    definite_cat_win = False
                elif possible_verdict == GameVerdict.NOT_COMPUTED_YET:
                    definite_cat_win = False
            if definite_cat_win:
                self.saved_results[key] = GameVerdict.CAT_WIN
                self.in_computation.remove(key)
                return GameVerdict.CAT_WIN
            return GameVerdict.NOT_COMPUTED_YET

        if turn == Turn.CAT:
            possible_draw = False
            for possible_next_pos in graph[catPos]:
                if possible_next_pos == 0:
                    continue  # The cat cannot go through 0
                if (possible_next_pos, mousePos, Turn.MOUSE) in self.in_computation:
                    possible_cycle_move = True
                    continue
                possible_verdict = self.gameResult(graph, possible_next_pos, mousePos, Turn.MOUSE)
                if possible_verdict == GameVerdict.CAT_WIN:
                    self.saved_results[key] = GameVerdict.CAT_WIN
                    self.in_computation.remove(key)
                    return GameVerdict.CAT_WIN
                elif possible_verdict == GameVerdict.DRAW:
                    possible_draw = True
            if possible_draw:
                self.saved_results[key] = GameVerdict.DRAW
                self.in_computation.remove(key)
                return GameVerdict.DRAW
            if possible_cycle_move:
                return
            self.saved_results[key] = GameVerdict.MOUSE_WIN
            self.in_computation.remove(key)
            return GameVerdict.MOUSE_WIN

        # Should not get here
        return 0

    def catMouseGame(self, graph: List[List[int]]) -> int:
        return self.gameResult(graph, 2, 1, Turn.MOUSE)

graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
sol = Solution()
#print(sol.catMouseGame(graph))
graph = [[5,6],[3,4],[6],[1,4,5],[1,3,5],[0,3,4,6],[0,2,5]]
print(sol.catMouseGame(graph))