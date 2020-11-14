#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"
#include "utilities/int_kth_root.hpp"
#include <iostream>
using namespace std;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        unsigned long long a;
        int k;
        cin >> a >> k;
        cout << int_kth_root(a, k) << '\n';
    }
}
