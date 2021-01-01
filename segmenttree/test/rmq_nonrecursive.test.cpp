#include "../point-update-range-get_nonrecursive.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N, (1LL << 31) - 1);
    RangeMinimumQuery<int> rmq(A, A[0]);
    while (Q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0)
            rmq.update(x, y);
        else
            cout << rmq.get(x, y + 1) << endl;
    }
}
