#include <bitset>
#include <iostream>
#include "string/aho_corasick.hpp"
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

void operator+=(bitset<10000> &l, const bitset<10000> &r) { l |= r; }

int main()
{
    Trie<bitset<10000>> trie;
    string T;
    cin >> T;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string P;
        cin >> P;
        bitset<10000> bs;
        bs.set(i);
        trie.add_keyword(P, bs);
    }
    trie.build_aho_corasick();

    int now = 0;
    bitset<10000> ans;
    for (auto c : T)
    {
        while (now and trie.child[now][c] == 0) now = trie.fail[now];
        now = trie.child[now][c];
        ans |= trie.node_info[now];
    }
    for (int i = 0; i < N; i++) cout << ans[i] << endl;
}
