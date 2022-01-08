#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../../modint.hpp"
#include "../blackbox_algorithm.hpp"
#include "../blackbox_matrices.hpp"
#include "../matrix.hpp"
#include <chrono>
#include <cstdio>
#include <random>
#include <type_traits>
#include <vector>
using namespace std;

mt19937 mt(1010101);

template <class MODINT, class MATRIX,
          typename std::enable_if<std::is_same<MATRIX, toeplitz_ntt<MODINT>>::value>::type * = nullptr>
toeplitz_ntt<MODINT> gen_random_matrix() {
    auto rnd = uniform_int_distribution<int>(1, 100);
    int h = rnd(mt), w = max(h, rnd(mt));
    auto vh = gen_random_vector<MODINT>(h), vw = gen_random_vector<MODINT>(w);
    vw[0] = vh[0];
    return toeplitz_ntt<MODINT>(vh, vw);
}

template <class MODINT, class MATRIX,
          typename std::enable_if<std::is_same<MATRIX, square_toeplitz_ntt<MODINT>>::value>::type * = nullptr>
square_toeplitz_ntt<MODINT> gen_random_matrix() {
    int N = uniform_int_distribution<int>(1, 100)(mt);
    auto v = gen_random_vector<MODINT>(N * 2 - 1);
    return square_toeplitz_ntt<MODINT>(v);
}

template <class MODINT, class MATRIX,
          typename std::enable_if<std::is_same<MATRIX, sparse_matrix<MODINT>>::value>::type * = nullptr>
sparse_matrix<MODINT> gen_random_matrix() {
    int H = uniform_int_distribution<int>(1, 20)(mt),
        W = max(H, uniform_int_distribution<int>(1, 20)(mt));
    sparse_matrix<MODINT> M(H, W);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            MODINT v = uniform_int_distribution<int>(0, MODINT::mod() - 1)(mt);
            M.add_element(i, j, v);
        }
    }
    return M;
}

template <class MODINT, class MATRIX,
          typename std::enable_if<std::is_same<MATRIX, matrix<MODINT>>::value>::type * = nullptr>
matrix<MODINT> gen_random_matrix() {
    int H = uniform_int_distribution<int>(1, 20)(mt),
        W = max(H, uniform_int_distribution<int>(1, 20)(mt));
    matrix<MODINT> M(H, W);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            MODINT v = uniform_int_distribution<int>(0, MODINT::mod() - 1)(mt);
            M[i][j] = v;
        }
    }
    return M;
}

template <typename MATRIX, typename mint> void blackbox_mat_checker(int n_try) {
    for (int i = 0; i < n_try; i++) {
        const MATRIX M = gen_random_matrix<mint, MATRIX>();
        vector<vector<mint>> Mvv = M.vecvec();
        const int H = M.height(), W = M.width();
        const auto b = gen_random_vector<mint>(H);
        // Check linear eq. solver
        const auto x = linear_system_solver_lanczos(M, b);
        assert(M.prod(x) == b);

        // Check prod()
        const auto c = gen_random_vector<mint>(W);
        const auto Mc = M.prod(c);
        vector<mint> Mc2(H);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) Mc2[i] += Mvv[i][j] * c[j];
        }
        assert(Mc == Mc2);

        // Check prod_left()
        const auto a = gen_random_vector<mint>(H);
        const auto aM = M.prod_left(a);
        vector<mint> aM2(W);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) aM2[j] += Mvv[i][j] * a[i];
        }
        assert(aM == aM2);

        // Check black_box_determinant()
        if (H == W) {
            mint det = blackbox_determinant<MATRIX, mint>(M);
            mint det2 = matrix<mint>(Mvv).gauss_jordan().determinant_of_upper_triangle();
            assert(det == det2);
        }
    }
}

int main() {
    using mint = ModInt<998244353>;
    blackbox_mat_checker<toeplitz_ntt<mint>, mint>(1000);
    blackbox_mat_checker<square_toeplitz_ntt<mint>, mint>(1000);
    blackbox_mat_checker<sparse_matrix<mint>, mint>(1000);
    blackbox_mat_checker<matrix<mint>, mint>(1000);
    puts("Hello World");
}
