#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"
#include "../../utilities/reader.hpp"
#include "../suffix_array.hpp"
#include <cstdio>
using namespace std;

int main() {
    const string T = rdstr();
    int Q = rdi();
    const std::vector<int> sa = suffix_array(T);
    while (Q--) {
        string P = rdstr();
        printf("%d\n", !!count_keyword_occurence(T, sa, P));
    }
}
