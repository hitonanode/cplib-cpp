#define PROBLEM "https://yukicoder.me/problems/no/665"
#include "../kth_power_sum.hpp"
#include "../../modint.hpp"
#include <iostream>
using namespace std;

int main() {
    long long n;
    int k;
    cin >> n >> k;

    kth_power_sum<ModInt<1000000007>> kps;

    cout << kps.prefix_sum(k, n) << '\n';
}
