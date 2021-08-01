#pragma once
#include <cstdio>

// CUT begin
template <typename T> T rd_integer() {
    T ret = 0;
    bool minus = false;

    char c = getchar_unlocked();
    while (!isdigit(c)) minus |= (c == '-'), c = getchar_unlocked();
    while (isdigit(c)) ret = (ret << 1) + (ret << 3) + (c ^ 48), c = getchar_unlocked();

    return minus ? -ret : ret;
}
int rdi() { return rd_integer<int>(); }
long long rdll() { return rd_integer<long long>(); }
