#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <utility>

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