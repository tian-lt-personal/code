#include "rand-ints.h"
#include "print.h"

void qsort(int* beg, int* end) {
  if (end - beg <= 1) return;
  int pivot = beg[(end - beg)/2];
  int* i = beg;
  int* j = end - 1;
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
  auto vi = gen_rand_vi(-1000, 1000, 50);
  print(vi);
  qsort(vi.data(), vi.data() + vi.size());  
  print(vi);
}