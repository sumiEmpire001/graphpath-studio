import heapq
import math

class Graph:
    def __init__(self, directed=False):
        self.directed = directed
        self.edges = {}

    def add_edge(self, source, target, weight=1):
        if isinstance(weight, bool) or not isinstance(weight, (int, float)) or not math.isfinite(weight) or weight < 0:
            raise ValueError("weight must be finite and nonnegative")
        self.edges.setdefault(source, {})[target] = weight
        self.edges.setdefault(target, {})
        if not self.directed:
            self.edges[target][source] = weight

    def shortest_path(self, source, target):
        if source not in self.edges or target not in self.edges:
            return None
        # Counter breaks ties without comparing arbitrary node types.
        counter = 0
        heap = [(0, counter, source)]
        distance = {source: 0}
        parent = {}
        while heap:
            cost, _, node = heapq.heappop(heap)
            if cost != distance[node]:
                continue
            if node == target:
                path = [node]
                while node in parent:
                    node = parent[node]
                    path.append(node)
                return {"distance": cost, "path": list(reversed(path))}
            for neighbor, weight in self.edges[node].items():
                new_cost = cost + weight
                if new_cost < distance.get(neighbor, math.inf):
                    distance[neighbor] = new_cost
                    parent[neighbor] = node
                    counter += 1
                    heapq.heappush(heap, (new_cost, counter, neighbor))
        return None

    def reachable(self, source):
        if source not in self.edges:
            return set()
        visited = {source}
        stack = [source]
        while stack:
            for neighbor in self.edges[stack.pop()]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    stack.append(neighbor)
        return visited
