#pragma once

template <typename T, typename Int> T pow(T x, Int n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= x;
        x *= x;
        n >>= 1;
    }
    return ans;
}
