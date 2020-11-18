#pragma once
#include <cmath>
#include <vector>

constexpr double minusloginf = -300;
std::vector<double> logfac;
void facInit(int nmax) {
    logfac.assign(nmax + 1, 0);
    for (int i = 2; i <= nmax; i++) { logfac[i] = logfac[i - 1] + log(i); }
}
double lognCr(int n, int r) {
    if (n < r or r < 0) return minusloginf;
    return logfac[n] - logfac[r] - logfac[n - r];
}
