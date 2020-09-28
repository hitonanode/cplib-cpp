#pragma once

// CUT begin
// \sum_{i=0}^{n-1} floor((ai + b) / m)
// 0 <= n <= 1e9
// 1 <= m <= 1e9
// 0 <= a, b < m
// Complexity: O(lg(n + m + a + b))
long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}
