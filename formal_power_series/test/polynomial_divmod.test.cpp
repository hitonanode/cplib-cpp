#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
#include "../polynomial_divmod.hpp"
#include "../../modint.hpp"
#include <tuple>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<mint> f(N), g(M), q, r;
    for (auto &x : f) cin >> x;
    for (auto &x : g) cin >> x;
    tie(q, r) = polynomial_division(f, g);
    cout << q.size() << ' ' << r.size() << '\n';
    for (auto x : q) cout << x << ' ';
    cout << '\n';
    for (auto x : r) cout << x << ' ';
    cout << '\n';
}
