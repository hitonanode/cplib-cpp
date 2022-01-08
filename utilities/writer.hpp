#pragma once
#include <cstdio>

template <typename T> void wt_integer(T x, char delim) {
    if (x == 0) {
        putchar('0'), putchar(delim);
        return;
    }
    if (x < 0) putchar('-'), x = -x;
    static char cache[20];
    char *head = cache;
    while (x) *head = '0' + x % 10, head++, x /= 10;
    while (head != cache) putchar(*(--head));
    putchar(delim);
}
