#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"
#include "../../number/factorize.hpp"
#include "../../number/modint_runtime.hpp"
#include "../../random/rand_nondeterministic.hpp"
#include "../chromatic_number.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> to(N);

    long long md = 4;
    do { md = rnd(1LL << 29, 1LL << 30); } while (!is_prime(md));
    cerr << md << '\n';
    ModIntRuntime::set_mod(md);

    while (M--) {
        int u, v;
        cin >> u >> v;
        to[u] |= 1 << v;
        to[v] |= 1 << u;
    }
    cout << ChromaticNumber<ModIntRuntime>(to) << '\n';
}
