#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <random>
#include <vector>
#include <utility>

using adj_graph_type = std::vector<std::vector<int>>;

inline std::vector<int> grvi(int low, int hi, size_t count) {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dist{low, hi};
  std::vector<int> res;
  for(size_t i=0; i < count; ++i){
    res.push_back(dist(gen));
  }
  return res;
}

template <class T>
void print(const std::vector<T>& v) {
  if (v.empty()) return;
  std::cout << '[' << v[0];
  for (size_t i=0; i < v.size(); ++i) {
    std::cout << ',' << v[i];
  }
  std::cout << "]\n";
}

template <class F>
void test_sort(F&& f, int n) {
  for(int i=0; i<n; ++i) {
    std::cout << "run " << i << "--------------\n";
    auto v = grvi(0, 20, 30);
    print(v);
    f(v.data(), v.data() + v.size());
    print(v);
    std::cout << "result: " << (std::ranges::is_sorted(v) ? "Correct" : "Wrong") << std::endl;
  }
}

// Expected signature:
// std::optional<adj_graph_type> f(const adj_graph_type& graph);
//
// f returns a topological ordering for a DAG and std::nullopt when the graph
// contains a cycle. The inner vectors of the result are flattened in order.
template <class F>
void test_topo(F&& f, int n) {
  std::random_device rd;
  std::mt19937 gen{rd()};

  for (int i = 0; i < n; ++i) {
    std::cout << "run " << i << "--------------\n";

    const int vertex_count = std::uniform_int_distribution<int>{1, 20}(gen);
    std::vector<int> topological_order(vertex_count);
    std::iota(topological_order.begin(), topological_order.end(), 0);
    std::shuffle(topological_order.begin(), topological_order.end(), gen);

    // Build a DAG by only adding edges from an earlier to a later vertex in
    // the randomly chosen order.  The chain keeps every vertex connected and
    // makes the generated graph non-empty, even for small graphs.
    adj_graph_type graph(vertex_count);
    for (int u = 0; u + 1 < vertex_count; ++u) {
      graph[topological_order[u]].push_back(topological_order[u + 1]);
    }
    for (int u = 0; u < vertex_count; ++u) {
      for (int v = u + 2; v < vertex_count; ++v) {
        if (std::uniform_int_distribution<int>{0, 3}(gen) == 0) {
          graph[topological_order[u]].push_back(topological_order[v]);
        }
      }
    }

    for (int graph_type = 0; graph_type < 2; ++graph_type) {
      const bool is_dag = graph_type == 0;
      auto test_graph = graph;
      if (!is_dag) {
        // The chain above ensures that this edge closes a cycle.
        test_graph[topological_order.back()].push_back(topological_order.front());
      }

      std::cout << (is_dag ? "DAG" : "cyclic graph") << "\n";
      const auto result = f(test_graph);
      const bool returned_result = result.has_value();
      std::cout << "returned: "
                << (returned_result ? "topological ordering" : "nullopt")
                << "\n";

      bool valid_order = false;
      if (returned_result) {
        std::vector<int> position(vertex_count, -1);
        size_t order_position = 0;
        valid_order = true;
        for (const auto& vertices : *result) {
          for (const int vertex : vertices) {
            if (vertex < 0 || vertex >= vertex_count ||
                position[vertex] != -1) {
              valid_order = false;
              continue;
            }
            position[vertex] = static_cast<int>(order_position++);
          }
        }

        for (int vertex = 0; vertex < vertex_count; ++vertex) {
          if (position[vertex] == -1) valid_order = false;
          for (const int next : test_graph[vertex]) {
            if (position[vertex] == -1 || position[next] == -1 ||
                position[vertex] >= position[next]) {
              valid_order = false;
            }
          }
        }
      }

      const bool correct = is_dag ? returned_result && valid_order
                                  : !returned_result;
      std::cout << "result: " << (correct ? "Correct" : "Wrong")
                << std::endl;
    }
  }
}
