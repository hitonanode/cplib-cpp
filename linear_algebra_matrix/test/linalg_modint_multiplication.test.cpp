#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D"
#include "linear_algebra_matrix/linalg_modint.hpp"
#include "modint.hpp"
#include "number/bare_mod_algebra.hpp"
#include "number/modint_runtime.hpp"
#include <iostream>

constexpr int MODfixed = 1000003;
constexpr int MODruntime = 10007;

int main()
{
    int N, M, L;
    std::cin >> N >> M >> L;
    matrix<ModInt<MODfixed>> Afixed(N, M), Bfixed(M, L);
    ModIntRuntime::set_mod(MODruntime);
    std::cin >> Afixed >> Bfixed;
    matrix<ModIntRuntime> Aruntime(N, M), Bruntime(M, L);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            Aruntime[i][j] = Afixed[i][j].val;
        }
    }

    for (int j = 0; j < M; j++) {
        for (int k = 0; k < L; k++) {
            Bruntime[j][k] = Bfixed[j][k].val;
        }
    }

    auto Cfixed = Afixed * Bfixed;
    auto Cruntime = Aruntime * Bruntime;

    for (int i = 0; i < N; i++)
    {
        for (int l = 0; l < L; l++) {
            std::cout << linear_congruence({1, 1}, {Cfixed[i][l].val, Cruntime[i][l].val}, {MODfixed, MODruntime}).first;
            std::cout << (l == L - 1 ? "\n" : " ");
        }
    }
}
