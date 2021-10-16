#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"
#include "../hafnian.hpp"
#include "../../modint.hpp"
#include <vector>
using namespace std;

using mint = ModInt<998244353>;

int main() {
    int N;
    cin >> N;
    vector<vector<mint>> A(N, vector<mint>(N));
    for (auto &vec : A) {
        for (auto &x : vec) cin >> x;
    }
    cout << hafnian(A) << '\n';
}
