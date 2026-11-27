#include "utils.h"

void mqsort(int* B, int* E) {
    if (E-B <= 1) return;
    int pivot = B[(E-B)/2];
    int *i = B, *j = E-1;
    while(i <= j) {
        while(*i < pivot) ++i;
        while(*j > pivot) --j;
        if(i <= j) {
            std::swap(*i, *j);
            ++i; --j;
        }
    }
    mqsort(B, j+1);
    mqsort(i, E);
}

int main() {
    test_sort(mqsort, 10);
}