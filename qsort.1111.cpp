#include "utils.h"

void qsort(int* beg, int* end) {
  if (end - beg <= 1) return;
  int pivot = beg[(end - beg)/2];
  int* i = beg; int* j = end -1;
  while(i <= j) {
    while(*i < pivot) ++i;
    while(*j > pivot) --j;
    if (i <= j) {
      std::swap(*i, *j);
      ++i; --j;
    }
  }
  qsort(beg, j+1);
  qsort(i, end);
}

int main() {
  auto v = gen_rand_vi(0, 20, 50);
  print(v);
  qsort(v.data(), v.data()+v.size());
  print(v);
}