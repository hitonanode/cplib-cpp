#pragma once
#include "characteristic_poly.hpp"
#include "hessenberg_reduction.hpp"
#include "matrix.hpp"
#include <utility>
#include <vector>

// det(M_0 + M_1 x), M0 , M1: n x n matrix of F_p
// Complexity: O(n^3)
// Verified: https://yukicoder.me/problems/no/1907
template <class T>
std::vector<T> determinant_of_first_degree_poly_mat(std::vector<std::vector<T>> M0,
                                                    std::vector<std::vector<T>> M1) {
    const int N = M0.size();

    int multiply_by_x = 0;
    T detAdetBinv = 1;

    for (int p = 0; p < N; ++p) {
        int pivot = -1;
        for (int row = p; row < N; ++row) {
            if (M1[row][p] != T()) {
                pivot = row;
                break;
            }
        }

        if (pivot < 0) {
            ++multiply_by_x;
            if (multiply_by_x > N) return std::vector<T>(N + 1);

            for (int row = 0; row < p; ++row) {
                T v = M1[row][p];
                M1[row][p] = 0;
                for (int i = 0; i < N; ++i) M0[i][p] -= v * M0[i][row];
            }
            for (int i = 0; i < N; ++i) std::swap(M0[i][p], M1[i][p]);

            --p;
            continue;
        }

        if (pivot != p) {
            M1[pivot].swap(M1[p]);
            M0[pivot].swap(M0[p]);
            detAdetBinv *= -1;
        }

        T v = M1[p][p], vinv = v.inv();
        detAdetBinv *= v;
        for (int col = 0; col < N; ++col) {
            M0[p][col] *= vinv;
            M1[p][col] *= vinv;
        }

        for (int row = 0; row < N; ++row) {
            if (row == p) continue;
            T v = M1[row][p];
            for (int col = 0; col < N; ++col) {
                M0[row][col] -= M0[p][col] * v;
                M1[row][col] -= M1[p][col] * v;
            }
        }
    }

    for (auto &vec : M0) {
        for (auto &x : vec) x = -x;
    }
    matrix<T> tmp_mat(M0);
    hessenberg_reduction(tmp_mat);
    auto poly = characteristic_poly_of_hessenberg(tmp_mat);
    for (auto &x : poly) x *= detAdetBinv;

    poly.erase(poly.begin(), poly.begin() + multiply_by_x);
    poly.resize(N + 1);
    return poly;
}
