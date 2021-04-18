#include "../range_minimum_query.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

int main() {
    int N, Q;
    cin >> N >> Q;
    RangeMinimumQuery<int, (1LL << 31) - 1> rmq(N);
    for (int q = 0; q < Q; q++) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0) {
            rmq.update(x, y);
        } else {
            cout << rmq.get(x, y + 1) << '\n';
        }
    }
}
