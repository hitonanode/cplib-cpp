#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../../modint.hpp"
#include "../../number/modint_runtime.hpp"
#include "../linalg_modint.hpp"
#include <iostream>

int main() {
    constexpr int mod = 998244353;
    ModIntRuntime::set_mod(mod);

    int N;
    std::cin >> N;

    matrix<ModInt<mod>> Mfixed(N, N);
    std::cin >> Mfixed;

    matrix<ModIntRuntime> Mruntime(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) { Mruntime[i][j] = Mfixed[i][j].val; }
    }
    int ret_fixed = Mfixed.gauss_jordan().determinant_of_upper_triangle().val;
    int ret_runtime = Mruntime.gauss_jordan().determinant_of_upper_triangle().val;

    assert(ret_fixed == ret_runtime);
    std::cout << ret_fixed << std::endl;
}
