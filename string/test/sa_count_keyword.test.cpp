#include "../suffix_array.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    string T, P;
    int Q;
    cin >> T >> Q;
    const std::vector<int> sa = suffix_array(T);
    while (Q--) cin >> P, cout << !!count_keyword_occurence(T, sa, P) << '\n';
}
