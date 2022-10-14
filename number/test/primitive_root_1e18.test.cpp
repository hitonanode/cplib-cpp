#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"
#include "../primitive_root.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int Q;
    cin >> Q;
    while (Q--) {
        long long p;
        cin >> p;
        cout << find_smallest_primitive_root(p) << '\n';
    }
}
