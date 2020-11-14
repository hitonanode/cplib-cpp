#pragma once

// floor(a^(1/k)) (the largest x s.t. x^k doesn't exceed a)
// Constraints: a >= 0, k > 0
unsigned long long int_kth_root(unsigned long long a, int k) {
    using Int = __int128;
    if (a == 0) {
        return 0;
    } else if (k == 1) {
        return a;
    } else {
        Int ok = 1, ng = Int(a) + 1;
        while (ng - ok > 1) {
            Int c = (ok + ng) / 2, p = c;
            for (int t = 0; t < k - 1; t++) {
                p *= c;
                if (p > a) break;
            }
            (p > a ? ng : ok) = c;
        }
        return ok;
    }
}
