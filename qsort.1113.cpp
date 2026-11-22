#include "utils.h"

void my_qsort(int* B, int* E) {
  if (E-B <= 1) return;
  int pivot = B[(E-B)/2];
  int* i = B; int* j = E-1;
  while(i <=j) {
    while(*i < pivot) ++i;
    while(*j > pivot) --j;
    if(i <= j) {
      std::swap(*i, *j);
      ++i; --j;
    }
  }
  my_qsort(B, j+1);
  my_qsort(i, E);
}

int main() {
  test_sort(my_qsort, 10);
}