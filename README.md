# GraphPath Studio

A Python weighted graph toolkit with Dijkstra shortest paths and iterative reachability. Python 3.10+; standard library only.

```bash
python -m unittest discover -s tests -v
```

```python
from graphpath import Graph
g = Graph(directed=True)
g.add_edge("home", "campus", 4)
g.add_edge("campus", "library", 2)
print(g.shortest_path("home", "library"))
```

Edges must have finite, nonnegative weights. Missing or unreachable endpoints return None. Graphs may be directed or undirected. Node IDs must be hashable. This is an in-memory educational implementation, without geospatial routing, persistence or concurrent mutation guarantees.

## Quality checks
GitHub Actions runs unit tests on Python 3.10, 3.12 and 3.13. CI results must be checked before declaring this repository verified.

MIT license; see LICENSE.
