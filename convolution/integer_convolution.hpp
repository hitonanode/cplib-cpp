#include <vector>

// f[n]のn >= 1に対して、全ての倍数n*iに対するf[n*i]の和が出てくる 計算量O(NlogN)
template <typename T> void integer_zeta(std::vector<T> &f) {
    int N = f.size() - 1;
    for (int i = 1; i <= N; i++) {
        for (int j = i * 2; j <= N; j += i) { f[i] += f[j]; }
    }
}

// f[n]に対して、全てのnの倍数n*iに対するf[n*i]の和が出てくる 計算量O(NloglogN)
// 素数p毎に処理する高速ゼータ変換
// 使用例 <https://yukicoder.me/submissions/385043>
template <typename T> void fast_integer_zeta(std::vector<T> &f) {
    int N = f.size() - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++)
        if (is_prime[p]) {
            for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
            for (int j = N / p * p; j > 0; j -= p) f[j / p] += f[j];
        }
}

// fast_integer_zetaの逆演算 O(NloglogN)
// 使用例 <https://yukicoder.me/submissions/385120>
template <typename T> void fast_integer_moebius(std::vector<T> &f) {
    int N = f.size() - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++)
        if (is_prime[p]) {
            for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
            for (int j = p; j <= N; j += p) f[j / p] -= f[j];
        }
}
