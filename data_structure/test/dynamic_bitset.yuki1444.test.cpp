#define PROBLEM "https://yukicoder.me/problems/no/1444"
#include "../dynamic_bitset.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &x : A) cin >> x;

    int retu = 0;
    dynamic_bitset bs(1 << 10), bsu(1 << 10);
    bs.set(1);

    bool zero = false;

    for (int i = 0; i < N; ++i) {
        if (A[i] == 0) { zero = true; }

        if (zero) {
            cout << "1\n";
            continue;
        }
        dynamic_bitset bsnxt(1 << 10), bsunxt(1 << 10);
        for (int s = 0; s < (1 << 10); ++s)
            if (bs.test(s)) {
                if (s * A[i] < (1 << 10))
                    bsnxt.set(s * A[i]);
                else {
                    retu++;
                    bsunxt.set(s * A[i] % (1 << 10));
                }
            }
        for (int s = 0; s < (1 << 10); ++s) {
            if (bsu.test(s)) bsunxt.set(s * A[i] % (1 << 10));
        }
        for (int s = 0; s < (1 << 10); ++s) {
            if (bs.test(s) or bsu.test(s)) bsnxt.set(s & A[i]);
        }

        bsu = bsunxt;
        bs = bsnxt;
        cout << bs.count() + retu << '\n';
    }
}
