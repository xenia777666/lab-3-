#include <stdio.h>

void print_two_oldest_bits(int num) {
    unsigned int high_bits = num >> (sizeof(num) * 8 - 2);
    printf("Два старших бита: %d%d\n", (high_bits & 2) >> 1, high_bits & 1);
}
