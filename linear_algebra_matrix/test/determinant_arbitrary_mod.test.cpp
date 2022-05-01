#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"
#if __cplusplus < 201402L
#define IGNORE
#endif
#include "../characteristic_poly.hpp"
#include "../hessenberg_reduction.hpp"
#include "../matrix.hpp"
#include <atcoder/modint>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    using mint = atcoder::modint;
    mint::set_mod(M);
    matrix<mint> mat(N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int v;
            cin >> v;
            mat[i][j] = v;
        }
    }
    mat = -mat;
    ring_hessenberg_reduction(mat);
    cout << characteristic_poly_of_hessenberg(mat)[0].val() << '\n';
}
