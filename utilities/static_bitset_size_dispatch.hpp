#pragma once

// https://codeforces.com/blog/entry/143059
template <unsigned long long sz = 1>
void static_bitset_size_dispatch(unsigned long long n, auto &&callback) {
    if constexpr (sz > (1ULL << 30)) {
        return;
    } else if (n > sz) {
        static_bitset_size_dispatch<((sz * 3 + 1) / 2)>(n, callback); // tune here
    } else {
        callback.template operator()<sz>();
    }
}
/* Usage:
int ret = 0;
static_bitset_size_dispatch(n, [&]<size_t BS_SIZE>() {
    std::bitset<BS_SIZE> bs;
    // do something...
    // ret = ...;
});
*/
