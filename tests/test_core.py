import unittest
from graphpath import Graph

class GraphTests(unittest.TestCase):
    def test_shortest(self):
        graph = Graph()
        graph.add_edge("a", "b", 10)
        graph.add_edge("a", "c", 2)
        graph.add_edge("c", "b", 3)
        self.assertEqual(graph.shortest_path("a", "b"), {"distance": 5, "path": ["a", "c", "b"]})
        self.assertEqual(graph.reachable("a"), {"a", "b", "c"})

    def test_directed_and_unreachable(self):
        graph = Graph(directed=True)
        graph.add_edge("a", "b")
        self.assertIsNone(graph.shortest_path("b", "a"))
        self.assertEqual(graph.shortest_path("a", "a"), {"distance": 0, "path": ["a"]})

    def test_weights(self):
        graph = Graph()
        for value in (-1, float("nan"), float("inf"), True):
            with self.assertRaises(ValueError):
                graph.add_edge("a", "b", value)


    def test_zero_weight_and_mixed_nodes(self):
        graph = Graph(directed=True)
        graph.add_edge("start", 42, 0)
        graph.add_edge(42, ("end",), 0)
        self.assertEqual(graph.shortest_path("start", ("end",))["distance"], 0)
        self.assertEqual(graph.reachable(42), {42, ("end",)})

    def test_huge_weight_is_rejected(self):
        graph = Graph()
        with self.assertRaises(ValueError):
            graph.add_edge("a", "b", 10 ** 1000)
        self.assertEqual(graph.edges, {})

if __name__ == "__main__":
    unittest.main()
