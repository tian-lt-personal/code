#include "utils.h"

void my_qsort(int* beg, int* end) {
  if (end - beg <= 1) return;
  int pivot = beg[(end-beg)/2];
  int* i = beg; int* j = end-1;
  while(i <= j) {
    while(*i < pivot) ++i;
    while(*j > pivot) --j;
    if (i <= j) {
      std::swap(*i, *j);
      ++i; --j;
    }
  }
  my_qsort(beg, j+1);
  my_qsort(i, end);
}

int main() {
  auto v = grvi(0, 20, 40);
  print(v);
  my_qsort(v.data(), v.data() + v.size());
  print(v);
}