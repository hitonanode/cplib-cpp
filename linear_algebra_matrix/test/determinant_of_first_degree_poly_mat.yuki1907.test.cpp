#define PROBLEM "https://yukicoder.me/problems/no/1907"
#include "../determinant_of_first_degree_poly_mat.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<vector<mint>> M0(n, vector<mint>(n));
    auto M1 = M0;

    for (auto &v : M0) {
        for (auto &x : v) cin >> x;
    }

    for (auto &v : M1) {
        for (auto &x : v) cin >> x;
    }

    vector<mint> ret = determinant_of_first_degree_poly_mat(M0, M1);
    for (auto x : ret) cout << x << '\n';
}
