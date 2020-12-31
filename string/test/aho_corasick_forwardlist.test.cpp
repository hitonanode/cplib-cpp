#include "../aho_corasick.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    AhoCorasick<TrieNodeFL, c2i0aA> trie(62);
    string T, P;
    int Q;
    cin >> T >> Q;
    while (Q--) cin >> P, trie.add(P);

    trie.build_aho_corasick();
    for (auto n : trie.match(T)) cout << !!n << '\n';
}
