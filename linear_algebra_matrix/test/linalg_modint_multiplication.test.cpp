#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D"
#include "../../modint.hpp"
#include "../../number/bare_mod_algebra.hpp"
#include "../../number/modint_runtime.hpp"
#include "../matrix.hpp"
#include <iostream>
using namespace std;

constexpr int MODfixed = 1000003;
constexpr int MODruntime = 10007;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M, L;
    cin >> N >> M >> L;
    matrix<ModInt<MODfixed>> Afixed(N, M), Bfixed(M, L);
    ModIntRuntime::set_mod(MODruntime);
    cin >> Afixed >> Bfixed;
    matrix<ModIntRuntime> Aruntime(N, M), Bruntime(M, L);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) Aruntime[i][j] = Afixed[i][j].val();
    }

    for (int j = 0; j < M; j++) {
        for (int k = 0; k < L; k++) Bruntime[j][k] = Bfixed[j][k].val();
    }

    auto Cfixed = Afixed * Bfixed;
    auto Cruntime = Aruntime * Bruntime;

    for (int i = 0; i < N; i++) {
        for (int l = 0; l < L; l++) {
            cout << linear_congruence<long long>(
                        {1, 1}, {Cfixed[i][l].val(), Cruntime[i][l].val()}, {MODfixed, MODruntime})
                        .first;
            cout << (l == L - 1 ? "\n" : " ");
        }
    }
}
