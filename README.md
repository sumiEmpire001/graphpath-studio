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

## C++11 Dijkstra graph core (additional implementation)

The existing Python code and tests remain unchanged. The portable C++11 core is at `cpp/include/graph.hpp`, with tests under `cpp/tests`.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
python -m unittest discover -s tests -v
```

GitHub Actions separately compiles the C++ host tests with GCC and Clang. C++ uses integer node indices (0..N-1), not arbitrary hashable Python IDs, and caps the graph at 10,000 nodes. No path reconstruction or persistence; distance overflow throws. Not appropriate for hard real-time control or safety-critical navigation.

**Embedded integration:** The C++ implementation is a host-tested reusable algorithm, not a verified Arduino/ESP32 sketch. Exceptions, STL allocations and memory limits require adaptation for small microcontrollers. Do not connect physical actuators based on this library without independent fail-safe controls and on-device testing.
