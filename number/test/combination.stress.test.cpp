#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../combination.hpp"
#include "../sieve.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    constexpr int maxn = 100, maxr = 100, maxmd = 1000;

    for (int md = 1; md <= maxmd; ++md) {

        combination nCr(Sieve(md).factorize(md));

        vector<vector<int>> ncrs(maxn, vector<int>(maxr));
        for (int n = 0; n < maxn; ++n) ncrs[n][0] = 1 % md;
        for (int n = 1; n < maxn; ++n) {
            for (int r = 1; r < maxr; ++r) ncrs[n][r] = (ncrs[n - 1][r] + ncrs[n - 1][r - 1]) % md;
        }

        for (int n = 0; n < maxn; ++n) {
            for (int r = 0; r < maxr; ++r) assert(ncrs[n][r] == nCr(n, r));
        }
    }
    cout << "Hello World" << endl;
}
