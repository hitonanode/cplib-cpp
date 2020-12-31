#include "../incremental_matching.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    IncrementalMatching<TrieNodeFL, c2i_0aA> trie(62);
    string T, P;
    int Q;
    cin >> T >> Q;
    while (Q--) cin >> P, trie.add(P);

    for (auto n : trie.match(T)) cout << !!n << '\n';
}
