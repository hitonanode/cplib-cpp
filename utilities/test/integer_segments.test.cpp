#define PROBLEM "https://yukicoder.me/problems/no/674"
#include "../integer_segments.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    long long D;
    int Q;
    cin >> D >> Q;
    integer_segments<long long> seg;

    long long ret = 0;
    while (Q--) {
        long long a, b;
        cin >> a >> b;
        auto lr = seg.insert(a, b);
        ret = max(ret, lr.second - lr.first + 1);
        cout << ret << '\n';
    }
}
