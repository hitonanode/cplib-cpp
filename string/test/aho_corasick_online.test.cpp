#include "../aho_corasick_online.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    OnlineAhoCorasick oac;
    string T, P;
    int Q;
    cin >> T >> Q;
    while (Q--) cin >> P, oac.add(P);

    for (auto n : oac.match(T)) cout << !!n << '\n';
}
