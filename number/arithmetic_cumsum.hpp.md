---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: formal_power_series/lagrange_interpolation.hpp
    title: "Lagrange interpolation\uFF08\u591A\u9805\u5F0F\u306E Lagrange \u88DC\u9593\
      \uFF09"
  - icon: ':x:'
    path: formal_power_series/sum_of_exponential_times_polynomial.hpp
    title: Sum of exponential times polynomial ($\sum_{i=0}^{N - 1} r^i f(i)$)
  - icon: ':x:'
    path: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
    title: Sum of exponential times polynomial limit ($\sum_{i=0}^\infty r^i f(i)$)
  - icon: ':question:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: number/test/arithmetic_function_totient.test.cpp
    title: number/test/arithmetic_function_totient.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c
  bundledCode: "#line 2 \"formal_power_series/lagrange_interpolation.hpp\"\n#include\
    \ <vector>\n\n// CUT begin\n// Lagrange interpolation\n// Input: [f(0), ..., f(N-1)]\
    \ (length = N), deg(f) < N\n// Output: f(x_eval)\n// Complexity: O(N)\n// Verified:\
    \ https://atcoder.jp/contests/arc033/tasks/arc033_4\ntemplate <typename MODINT>\
    \ MODINT interpolate_iota(const std::vector<MODINT> ys, MODINT x_eval) {\n   \
    \ const int N = ys.size();\n    if (x_eval.val() < N) return ys[x_eval.val()];\n\
    \    std::vector<MODINT> facinv(N);\n    facinv[N - 1] = MODINT(N - 1).fac().inv();\n\
    \    for (int i = N - 1; i > 0; i--) facinv[i - 1] = facinv[i] * i;\n    std::vector<MODINT>\
    \ numleft(N);\n    MODINT numtmp = 1;\n    for (int i = 0; i < N; i++) {\n   \
    \     numleft[i] = numtmp;\n        numtmp *= x_eval - i;\n    }\n    numtmp =\
    \ 1;\n    MODINT ret = 0;\n    for (int i = N - 1; i >= 0; i--) {\n        MODINT\
    \ tmp = ys[i] * numleft[i] * numtmp * facinv[i] * facinv[N - 1 - i];\n       \
    \ ret += ((N - 1 - i) & 1) ? (-tmp) : tmp;\n        numtmp *= x_eval - i;\n  \
    \  }\n    return ret;\n}\n#line 2 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n#include <cassert>\n#line 4 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\u5F0F $f(x)$ \u3068\
    \u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$\
    \ \u306E\u5024\u3092 $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$\
    \ \u3067\u8A08\u7B97\uFF0E\n// Requirement: r != 1\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT>\nMODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    assert(r != 1);\n    if (init.empty()) return\
    \ 0;\n    if (init.size() == 1) return init[0] / (1 - r);\n    auto &bs = init;\n\
    \    const int d = int(bs.size()) - 1;\n    MODINT rp = 1;\n    for (int i = 1;\
    \ i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n\
    \    rp = 1;\n    for (int i = 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d\
    \ + 1).nCr(i) * rp;\n        rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d\
    \ + 1);\n};\n#line 6 \"formal_power_series/sum_of_exponential_times_polynomial.hpp\"\
    \n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\u5F0F $f(x)$ \u3068\
    \u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^{N-1} r^i f(i)$\
    \ \u306E\u5024\u3092 $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$\
    \ \u3067\u8A08\u7B97\uFF0E\n// Reference:\n// - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial\n\
    // - https://min-25.hatenablog.com/entry/2015/04/24/031413\ntemplate <typename\
    \ MODINT>\nMODINT sum_of_exponential_times_polynomial(MODINT r, const std::vector<MODINT>\
    \ &init, long long N) {\n    if (N <= 0) return 0;\n    if (init.size() == 1)\
    \ return init[0] * (r == 1 ? MODINT(N) : (1 - r.pow(N)) / (1 - r));\n\n    std::vector<MODINT>\
    \ S(init.size() + 1);\n    MODINT rp = 1;\n    for (int i = 0; i < int(init.size());\
    \ i++) {\n        S[i + 1] = S[i] + init[i] * rp;\n        rp *= r;\n    }\n \
    \   if (N < (long long)S.size()) return S[N];\n\n    if (r == 1) return interpolate_iota<MODINT>(S,\
    \ N);\n\n    const MODINT Sinf = sum_of_exponential_times_polynomial_limit<MODINT>(r,\
    \ init);\n    MODINT rinv = r.inv(), rinvp = 1;\n    for (int i = 0; i < int(S.size());\
    \ i++) {\n        S[i] = (S[i] - Sinf) * rinvp;\n        rinvp *= rinv;\n    }\n\
    \    return interpolate_iota<MODINT>(S, N) * r.pow(N) + Sinf;\n};\n#line 3 \"\
    number/sieve.hpp\"\n#include <map>\n#line 5 \"number/sieve.hpp\"\n\n// CUT begin\n\
    // Linear sieve algorithm for fast prime factorization\n// Complexity: O(N) time,\
    \ O(N) space:\n// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces / AtCoder GCC,\
    \ C++17)\n// - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder GCC, C++17)\n\
    // Reference:\n// [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm for Finding\
    \ Prime Numbers,\"\n//     Communications of the ACM, 21(12), 999-1003, 1978.\n\
    // - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n// - https://37zigen.com/linear-sieve/\n\
    struct Sieve {\n    std::vector<int> min_factor;\n    std::vector<int> primes;\n\
    \    Sieve(int MAXN) : min_factor(MAXN + 1) {\n        for (int d = 2; d <= MAXN;\
    \ d++) {\n            if (!min_factor[d]) {\n                min_factor[d] = d;\n\
    \                primes.emplace_back(d);\n            }\n            for (const\
    \ auto &p : primes) {\n                if (p > min_factor[d] or d * p > MAXN)\
    \ break;\n                min_factor[d * p] = p;\n            }\n        }\n \
    \   }\n    // Prime factorization for 1 <= x <= MAXN^2\n    // Complexity: O(log\
    \ x)           (x <= MAXN)\n    //             O(MAXN / log MAXN) (MAXN < x <=\
    \ MAXN^2)\n    template <class T> std::map<T, int> factorize(T x) const {\n  \
    \      std::map<T, int> ret;\n        assert(x > 0 and\n               x <= ((long\
    \ long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));\n       \
    \ for (const auto &p : primes) {\n            if (x < T(min_factor.size())) break;\n\
    \            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if (x >= T(min_factor.size()))\
    \ ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++, x /= min_factor[x];\n\
    \        return ret;\n    }\n    // Enumerate divisors of 1 <= x <= MAXN^2\n \
    \   // Be careful of highly composite numbers https://oeis.org/A002182/list\n\
    \    // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n,\
    \ (# of div. of n)):\n    // 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <class T> std::vector<T> divisors(T x) const {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Euler phi functions of divisors\
    \ of given x\n    // Verified: ABC212 G https://atcoder.jp/contests/abc212/tasks/abc212_g\n\
    \    // Complexity: O(sqrt(x) + d(x))\n    template <class T> std::map<T, T> euler_of_divisors(T\
    \ x) const {\n        assert(x >= 1);\n        std::map<T, T> ret;\n        ret[1]\
    \ = 1;\n        std::vector<T> divs{1};\n        for (auto p : factorize(x)) {\n\
    \            int n = ret.size();\n            for (int i = 0; i < n; i++) {\n\
    \                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);\n    \
    \            divs.push_back(divs[i] * p.first);\n                for (T a = divs[i]\
    \ * p.first, d = 1; d < p.second; a *= p.first, d++) {\n                    ret[a\
    \ * p.first] = ret[a] * p.first;\n                    divs.push_back(a * p.first);\n\
    \                }\n            }\n        }\n        return ret;\n    }\n   \
    \ // Moebius function Table, (-1)^{# of different prime factors} for square-free\
    \ x\n    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0,\
    \ ...] https://oeis.org/A008683\n    std::vector<int> GenerateMoebiusFunctionTable()\
    \ const {\n        std::vector<int> ret(min_factor.size());\n        for (unsigned\
    \ i = 1; i < min_factor.size(); i++) {\n            if (i == 1) {\n          \
    \      ret[i] = 1;\n            } else if ((i / min_factor[i]) % min_factor[i]\
    \ == 0) {\n                ret[i] = 0;\n            } else {\n               \
    \ ret[i] = -ret[i / min_factor[i]];\n            }\n        }\n        return\
    \ ret;\n    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    // Note:\
    \ **0^0 == 1**\n    template <class MODINT> std::vector<MODINT> enumerate_kth_pows(long\
    \ long K, int nmax) const {\n        assert(nmax < int(min_factor.size()));\n\
    \        assert(K >= 0);\n        if (K == 0) return std::vector<MODINT>(nmax\
    \ + 1, 1);\n        std::vector<MODINT> ret(nmax + 1);\n        ret[0] = 0, ret[1]\
    \ = 1;\n        for (int n = 2; n <= nmax; n++) {\n            if (min_factor[n]\
    \ == n) {\n                ret[n] = MODINT(n).pow(K);\n            } else {\n\
    \                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n     \
    \       }\n        }\n        return ret;\n    }\n};\n// Sieve sieve((1 << 20));\n\
    #line 5 \"number/arithmetic_cumsum.hpp\"\n#include <cmath>\n#line 7 \"number/arithmetic_cumsum.hpp\"\
    \n\n// CUT begin\n// Dirichlet product (convolution)\n// - a[i] = f(i) (1-origin)\n\
    // - A[i - 1] = f(1) + ... + f(i)\n// - invA[i - 1] = f(1) + ... + f(N / i)\n\
    // Reference:\n// https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c\n\
    template <class T> struct arithmetic_cumsum {\n    long long N;\n    int K, L;\n\
    \    bool _verify_shape(const arithmetic_cumsum &x) const {\n        return N\
    \ == x.N and K == x.K and L == x.L;\n    }\n\n    std::vector<T> a, A, invA;\n\
    \    arithmetic_cumsum(long long N_) : N(N_) {\n        K = ceill(std::max(sqrtl(N_),\
    \ powl(N_ / (N_ > 1 ? log2l(N_) : 1.), 2.0 / 3)));\n        L = (N_ + K - 1) /\
    \ K;\n        a.resize(K), A.resize(K), invA.resize(L);\n    }\n    T at(int i)\
    \ const { // a[i]\n        assert(i >= 1 and i <= K);\n        return a[i - 1];\n\
    \    }\n    T sum(long long i) const { // a[1] + ... + a[i]\n        assert(i\
    \ >= 1 and i <= N);\n        if (i <= K) return A[i - 1];\n        long long j\
    \ = N / i;\n        assert(j >= 1 and j <= L);\n        return invA[j - 1];\n\
    \    }\n\n    arithmetic_cumsum operator+(const arithmetic_cumsum &x) const {\n\
    \        assert(N == x.N and K == x.K and L == x.L);\n        auto ret = *this;\n\
    \        for (int i = 0; i < ret.K; ++i) {\n            ret.a[i] += x.a[i];\n\
    \            ret.A[i] += x.A[i];\n        }\n        for (int i = 0; i < ret.L;\
    \ ++i) ret.invA[i] += x.invA[i];\n        return ret;\n    }\n\n    arithmetic_cumsum\
    \ operator-(const arithmetic_cumsum &x) const {\n        assert(N == x.N and K\
    \ == x.K and L == x.L);\n        auto ret = *this;\n        for (int i = 0; i\
    \ < ret.K; ++i) {\n            ret.a[i] -= x.a[i];\n            ret.A[i] -= x.A[i];\n\
    \        }\n        for (int i = 0; i < ret.L; ++i) ret.invA[i] -= x.invA[i];\n\
    \        return ret;\n    }\n    // Dirichlet product (convolution)\n    arithmetic_cumsum\
    \ operator*(const arithmetic_cumsum &y) const {\n        assert(_verify_shape(y));\n\
    \        const arithmetic_cumsum &x = *this;\n        arithmetic_cumsum ret(x.N);\n\
    \        for (int i = 1; i <= x.K; ++i) {\n            for (int j = 1; i * j <=\
    \ x.K; ++j) ret.a[i * j - 1] += x.at(i) * y.at(j);\n        }\n        ret.A =\
    \ ret.a;\n        for (int i = 1; i < ret.K; i++) ret.A[i] += ret.A[i - 1];\n\n\
    \        for (int l = 1; l <= x.L; ++l) {\n            const long long n = x.N\
    \ / l;\n            long long i = 1;\n            for (; i * i <= n; ++i) {\n\
    \                ret.invA[l - 1] += x.at(i) * y.sum(n / i) + x.sum(n / i) * y.at(i);\n\
    \            }\n            ret.invA[l - 1] -= x.sum(i - 1) * y.sum(i - 1);\n\
    \        }\n        return ret;\n    }\n\n    bool operator==(const arithmetic_cumsum\
    \ &y) const {\n        return _verify_shape(y) and a == y.a and A == y.A and invA\
    \ == y.invA;\n    }\n\n    arithmetic_cumsum operator/(const arithmetic_cumsum\
    \ &y) const { // Division (*this) / y\n        assert(_verify_shape(y));\n   \
    \     const arithmetic_cumsum &x = *this;\n        arithmetic_cumsum ret(x.N);\n\
    \        assert(y.at(1) != 0);\n        const auto y1inv = 1 / y.at(1);\n    \
    \    ret.a = x.a;\n        for (int i = 1; i <= x.K; ++i) {\n            ret.a[i\
    \ - 1] *= y1inv;\n            for (int j = 2; i * j <= x.K; ++j) ret.a[i * j -\
    \ 1] -= ret.at(i) * y.at(j);\n        }\n        ret.A = ret.a;\n        for (int\
    \ i = 2; i <= x.K; ++i) ret.A[i - 1] += ret.A[i - 2];\n\n        for (int l =\
    \ x.L; l; --l) {\n            const long long n = x.N / l;\n            if (n\
    \ <= K) {\n                ret.invA[l - 1] = ret.sum(n);\n            } else {\n\
    \                ret.invA[l - 1] = 0;\n                long long i = 1;\n    \
    \            T tmp = 0;\n                for (; i * i <= n; ++i) {\n         \
    \           tmp += y.at(i) * ret.sum(n / i) + y.sum(n / i) * ret.at(i);\n    \
    \            }\n                tmp -= y.sum(i - 1) * ret.sum(i - 1);\n      \
    \          ret.invA[l - 1] = (x.sum(n) - tmp) * y1inv;\n            }\n      \
    \  }\n        return ret;\n    }\n\n    static arithmetic_cumsum identity(long\
    \ long n) { // [1, 0, ..., 0]\n        arithmetic_cumsum ret(n);\n        ret.a[0]\
    \ = 1;\n        ret.A.assign(ret.K, 1);\n        ret.invA.assign(ret.L, 1);\n\
    \        return ret;\n    }\n};\n\n// zeta(s) = [1, 1, 1, ...]\ntemplate <class\
    \ T> arithmetic_cumsum<T> zeta_cumsum(long long n) {\n    arithmetic_cumsum<T>\
    \ ret(n);\n    ret.a.assign(ret.K, 1);\n    for (int k = 1; k <= ret.K; k++) ret.A[k\
    \ - 1] = k;\n    for (int l = 1; l <= ret.L; l++) ret.invA[l - 1] = n / l;\n \
    \   return ret;\n}\n\n// zeta(s - 1) = [1, 2, 3, ...]\ntemplate <class T> arithmetic_cumsum<T>\
    \ zeta_shift_1_cumsum(long long n) {\n    arithmetic_cumsum<T> ret(n);\n    for\
    \ (int i = 0; i < ret.K; ++i) {\n        ret.a[i] = i + 1;\n        ret.A[i] =\
    \ T(i + 1) * (i + 2) / 2;\n    }\n    for (int l = 1; l <= ret.L; ++l) {\n   \
    \     T u = n / l;\n        ret.invA[l - 1] = u * (u + 1) / 2;\n    }\n    return\
    \ ret;\n}\n\n// zeta(s - k) = [1^k, 2^k, 3^k, ...]\ntemplate <class T> arithmetic_cumsum<T>\
    \ zeta_shift_cumsum(long long n, int k) {\n    if (k == 0) return zeta_cumsum<T>(n);\n\
    \    if (k == 1) return zeta_shift_1_cumsum<T>(n);\n    arithmetic_cumsum<T> ret(n);\n\
    \    auto init_pows = Sieve(k).enumerate_kth_pows<T>(k, k);\n    for (int i =\
    \ 1; i <= ret.K; ++i) {\n        ret.a[i - 1] = T(i).pow(k);\n        ret.A[i]\
    \ = ret.a[i] + (i ? ret.A[i - 1] : 0);\n    }\n    for (int l = 0; l < ret.L;\
    \ ++l) {\n        ret.invA[l] = sum_of_exponential_times_polynomial<T>(1, init_pows,\
    \ n / (l + 1) + 1);\n    }\n    return ret;\n}\n\n// Euler totient phi function\
    \ phi(s) = zeta(s - 1) / zeta(s)\ntemplate <class T> arithmetic_cumsum<T> euler_phi_cumsum(long\
    \ long n) {\n    return zeta_shift_1_cumsum<T>(n) / zeta_cumsum<T>(n);\n}\n\n\
    // \u7D04\u6570\u95A2\u6570\u306E\u7D2F\u7A4D\u548C\n// sigma_k (n) = \\sum_{d\
    \ \\mid n} d^k\ntemplate <class T> arithmetic_cumsum<T> divisor_func_cumsum(long\
    \ long n, int k) {\n    return zeta_shift_cumsum<T>(n, k) * zeta_cumsum<T>(n);\n\
    }\n\n// Cumulative sum of Moebius function (: Mertens function)\ntemplate <class\
    \ T> arithmetic_cumsum<T> moebius_func_cumsum(long long n) {\n    return arithmetic_cumsum<T>::identity(n)\
    \ / zeta_cumsum<T>(n);\n}\n"
  code: "#pragma once\n#include \"../formal_power_series/sum_of_exponential_times_polynomial.hpp\"\
    \n#include \"sieve.hpp\"\n#include <cassert>\n#include <cmath>\n#include <vector>\n\
    \n// CUT begin\n// Dirichlet product (convolution)\n// - a[i] = f(i) (1-origin)\n\
    // - A[i - 1] = f(1) + ... + f(i)\n// - invA[i - 1] = f(1) + ... + f(N / i)\n\
    // Reference:\n// https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c\n\
    template <class T> struct arithmetic_cumsum {\n    long long N;\n    int K, L;\n\
    \    bool _verify_shape(const arithmetic_cumsum &x) const {\n        return N\
    \ == x.N and K == x.K and L == x.L;\n    }\n\n    std::vector<T> a, A, invA;\n\
    \    arithmetic_cumsum(long long N_) : N(N_) {\n        K = ceill(std::max(sqrtl(N_),\
    \ powl(N_ / (N_ > 1 ? log2l(N_) : 1.), 2.0 / 3)));\n        L = (N_ + K - 1) /\
    \ K;\n        a.resize(K), A.resize(K), invA.resize(L);\n    }\n    T at(int i)\
    \ const { // a[i]\n        assert(i >= 1 and i <= K);\n        return a[i - 1];\n\
    \    }\n    T sum(long long i) const { // a[1] + ... + a[i]\n        assert(i\
    \ >= 1 and i <= N);\n        if (i <= K) return A[i - 1];\n        long long j\
    \ = N / i;\n        assert(j >= 1 and j <= L);\n        return invA[j - 1];\n\
    \    }\n\n    arithmetic_cumsum operator+(const arithmetic_cumsum &x) const {\n\
    \        assert(N == x.N and K == x.K and L == x.L);\n        auto ret = *this;\n\
    \        for (int i = 0; i < ret.K; ++i) {\n            ret.a[i] += x.a[i];\n\
    \            ret.A[i] += x.A[i];\n        }\n        for (int i = 0; i < ret.L;\
    \ ++i) ret.invA[i] += x.invA[i];\n        return ret;\n    }\n\n    arithmetic_cumsum\
    \ operator-(const arithmetic_cumsum &x) const {\n        assert(N == x.N and K\
    \ == x.K and L == x.L);\n        auto ret = *this;\n        for (int i = 0; i\
    \ < ret.K; ++i) {\n            ret.a[i] -= x.a[i];\n            ret.A[i] -= x.A[i];\n\
    \        }\n        for (int i = 0; i < ret.L; ++i) ret.invA[i] -= x.invA[i];\n\
    \        return ret;\n    }\n    // Dirichlet product (convolution)\n    arithmetic_cumsum\
    \ operator*(const arithmetic_cumsum &y) const {\n        assert(_verify_shape(y));\n\
    \        const arithmetic_cumsum &x = *this;\n        arithmetic_cumsum ret(x.N);\n\
    \        for (int i = 1; i <= x.K; ++i) {\n            for (int j = 1; i * j <=\
    \ x.K; ++j) ret.a[i * j - 1] += x.at(i) * y.at(j);\n        }\n        ret.A =\
    \ ret.a;\n        for (int i = 1; i < ret.K; i++) ret.A[i] += ret.A[i - 1];\n\n\
    \        for (int l = 1; l <= x.L; ++l) {\n            const long long n = x.N\
    \ / l;\n            long long i = 1;\n            for (; i * i <= n; ++i) {\n\
    \                ret.invA[l - 1] += x.at(i) * y.sum(n / i) + x.sum(n / i) * y.at(i);\n\
    \            }\n            ret.invA[l - 1] -= x.sum(i - 1) * y.sum(i - 1);\n\
    \        }\n        return ret;\n    }\n\n    bool operator==(const arithmetic_cumsum\
    \ &y) const {\n        return _verify_shape(y) and a == y.a and A == y.A and invA\
    \ == y.invA;\n    }\n\n    arithmetic_cumsum operator/(const arithmetic_cumsum\
    \ &y) const { // Division (*this) / y\n        assert(_verify_shape(y));\n   \
    \     const arithmetic_cumsum &x = *this;\n        arithmetic_cumsum ret(x.N);\n\
    \        assert(y.at(1) != 0);\n        const auto y1inv = 1 / y.at(1);\n    \
    \    ret.a = x.a;\n        for (int i = 1; i <= x.K; ++i) {\n            ret.a[i\
    \ - 1] *= y1inv;\n            for (int j = 2; i * j <= x.K; ++j) ret.a[i * j -\
    \ 1] -= ret.at(i) * y.at(j);\n        }\n        ret.A = ret.a;\n        for (int\
    \ i = 2; i <= x.K; ++i) ret.A[i - 1] += ret.A[i - 2];\n\n        for (int l =\
    \ x.L; l; --l) {\n            const long long n = x.N / l;\n            if (n\
    \ <= K) {\n                ret.invA[l - 1] = ret.sum(n);\n            } else {\n\
    \                ret.invA[l - 1] = 0;\n                long long i = 1;\n    \
    \            T tmp = 0;\n                for (; i * i <= n; ++i) {\n         \
    \           tmp += y.at(i) * ret.sum(n / i) + y.sum(n / i) * ret.at(i);\n    \
    \            }\n                tmp -= y.sum(i - 1) * ret.sum(i - 1);\n      \
    \          ret.invA[l - 1] = (x.sum(n) - tmp) * y1inv;\n            }\n      \
    \  }\n        return ret;\n    }\n\n    static arithmetic_cumsum identity(long\
    \ long n) { // [1, 0, ..., 0]\n        arithmetic_cumsum ret(n);\n        ret.a[0]\
    \ = 1;\n        ret.A.assign(ret.K, 1);\n        ret.invA.assign(ret.L, 1);\n\
    \        return ret;\n    }\n};\n\n// zeta(s) = [1, 1, 1, ...]\ntemplate <class\
    \ T> arithmetic_cumsum<T> zeta_cumsum(long long n) {\n    arithmetic_cumsum<T>\
    \ ret(n);\n    ret.a.assign(ret.K, 1);\n    for (int k = 1; k <= ret.K; k++) ret.A[k\
    \ - 1] = k;\n    for (int l = 1; l <= ret.L; l++) ret.invA[l - 1] = n / l;\n \
    \   return ret;\n}\n\n// zeta(s - 1) = [1, 2, 3, ...]\ntemplate <class T> arithmetic_cumsum<T>\
    \ zeta_shift_1_cumsum(long long n) {\n    arithmetic_cumsum<T> ret(n);\n    for\
    \ (int i = 0; i < ret.K; ++i) {\n        ret.a[i] = i + 1;\n        ret.A[i] =\
    \ T(i + 1) * (i + 2) / 2;\n    }\n    for (int l = 1; l <= ret.L; ++l) {\n   \
    \     T u = n / l;\n        ret.invA[l - 1] = u * (u + 1) / 2;\n    }\n    return\
    \ ret;\n}\n\n// zeta(s - k) = [1^k, 2^k, 3^k, ...]\ntemplate <class T> arithmetic_cumsum<T>\
    \ zeta_shift_cumsum(long long n, int k) {\n    if (k == 0) return zeta_cumsum<T>(n);\n\
    \    if (k == 1) return zeta_shift_1_cumsum<T>(n);\n    arithmetic_cumsum<T> ret(n);\n\
    \    auto init_pows = Sieve(k).enumerate_kth_pows<T>(k, k);\n    for (int i =\
    \ 1; i <= ret.K; ++i) {\n        ret.a[i - 1] = T(i).pow(k);\n        ret.A[i]\
    \ = ret.a[i] + (i ? ret.A[i - 1] : 0);\n    }\n    for (int l = 0; l < ret.L;\
    \ ++l) {\n        ret.invA[l] = sum_of_exponential_times_polynomial<T>(1, init_pows,\
    \ n / (l + 1) + 1);\n    }\n    return ret;\n}\n\n// Euler totient phi function\
    \ phi(s) = zeta(s - 1) / zeta(s)\ntemplate <class T> arithmetic_cumsum<T> euler_phi_cumsum(long\
    \ long n) {\n    return zeta_shift_1_cumsum<T>(n) / zeta_cumsum<T>(n);\n}\n\n\
    // \u7D04\u6570\u95A2\u6570\u306E\u7D2F\u7A4D\u548C\n// sigma_k (n) = \\sum_{d\
    \ \\mid n} d^k\ntemplate <class T> arithmetic_cumsum<T> divisor_func_cumsum(long\
    \ long n, int k) {\n    return zeta_shift_cumsum<T>(n, k) * zeta_cumsum<T>(n);\n\
    }\n\n// Cumulative sum of Moebius function (: Mertens function)\ntemplate <class\
    \ T> arithmetic_cumsum<T> moebius_func_cumsum(long long n) {\n    return arithmetic_cumsum<T>::identity(n)\
    \ / zeta_cumsum<T>(n);\n}\n"
  dependsOn:
  - formal_power_series/sum_of_exponential_times_polynomial.hpp
  - formal_power_series/lagrange_interpolation.hpp
  - formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
  - number/sieve.hpp
  isVerificationFile: false
  path: number/arithmetic_cumsum.hpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - number/test/arithmetic_function_totient.test.cpp
documentation_of: number/arithmetic_cumsum.hpp
layout: document
title: "Cumulative sum of arithmetic functions \uFF08\u6570\u8AD6\u7684\u95A2\u6570\
  \u306E\u7D2F\u7A4D\u548C\uFF09"
---

$f(s) = \sum_{k=1}^N a\_k k^s$ のような形式で表される数論的関数に対して，以下の処理をサポートする．

- 2つの数論的関数の積の計算（$O(N^{2/3} (\log N)^{1/3})$）．
- $\sum_{k=1}^{\lfloor N / i \rfloor} a\_k$ の値の取得（$O(1)$）．

なお，一つの関数の保持に $O(\sqrt{N})$ の空間計算量を要する．

## 使用方法

### 関数定義

有名な数学関数は専用の関数によって直ちに生成できる．

#### ゼータ関数

関数 $\sum\_{k = 1, \dots} k^x$ （$\mathbf{a} = (1, 1, \dots,)$）は
```cpp
long long n;
arithmetic_cumsum<mint> z = zeta_cumsum<mint>(n);
```
によって生成できる．生成に要する計算量は $O(n)$．

#### ゼータ関数のシフト

$\sum\_{i = 1, \dots} i^d i^x$ （$\mathbf{a} = (1^d, 2^d, \dots,)$）は以下で生成できる．与える型は `ModInt<>` や `atcoder::static_modint<>` を想定している．
```cpp
int k;
auto f = zeta_shift_cumsum<mint>(n, k);
```
生成に要する計算量は $O(nk)$．

#### 約数関数

$\sum\_{i = 1, \dots} \sum\_{d \mid i} d^k i^x$ は以下で生成できる．
```cpp
arithmetic_cumsum<mint> d = divisor_func_cumsum<mint>(n, k);
```
生成に要する計算量は $O(nk)$．

#### 自分で定義した関数

具体的に各項の係数を手で与えるには，以下のようにメンバ変数を設定すればよい．

- `a` : 長さ $K$．第 $i$ 要素（$0 \le i < K$）は $a\_{i + 1}$ の値に対応する．
- `A` : 長さ $K$．第 $i$ 要素（$0 \le i < K$）には $\sum\_{j = 1}^{i + 1} a\_{j}$ の値に対応する（`a` の累積和を持たせればよい）．
- `invA` : 長さ $L$．第 $i$ 要素（$0 \le i < L$）には $\sum\_{j=1}^{\lfloor N / (i + 1)\rfloor} a\_j$ の値を持たせる．

### サポートする演算

```cpp
arithmetic_cumsum<mint> f(N), g(N);  // 同一の N をもつもの同士に対してのみ演算が可能．

auto f2 = f + g;
auto f3 = f - g;
auto id = arithmetic_cumsum<mint>::identity(N);
auto h = f * g;
auto i = h / g;  // g の a_1 の値が逆元を持てば可能
assert(f == i);
mint t = f.sum(k);  // a_1 + ... + a_k を返す． k = floor(N / t) を満たす 1 <= t <= N が存在するような k のみ可能．
```

## 問題例

- [Library Checker: Sum of Totient Function](https://judge.yosupo.jp/problem/sum_of_totient_function)
- [AtCoder Regular Contest 116 C - Multiple Sequences](https://atcoder.jp/contests/arc116/tasks/arc116_c)

## リンク

- [Dirichlet 積と、数論関数の累積和 \| maspyのHP](https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c)
