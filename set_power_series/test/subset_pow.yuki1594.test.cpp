#define PROBLEM "https://yukicoder.me/problems/no/1594"
#include "../../modint.hpp"
#include "../subset_convolution.hpp"
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &x : A) cin >> x;
    int sum = accumulate(A.begin(), A.end(), 0);
    vector<ModInt<1000000007>> f(1 << N);
    for (int S = 0; S < 1 << N; S++) {
        int tot = 0;
        for (int d = 0; d < N; d++) tot += A[d] * ((S >> d) & 1);
        if (tot * 3 == sum) f[S] = 1;
    }
    subset_pow(f, 3);
    cout << (f.back() ? "Yes" : "No") << '\n';
}
