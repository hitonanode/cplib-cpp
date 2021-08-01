#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A"
#include "../factorize.hpp"
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    auto facs = FactorizeLonglong(n);
    cout << n << ':';
    for (auto x : facs) cout << ' ' << x;
    cout << '\n';
}
