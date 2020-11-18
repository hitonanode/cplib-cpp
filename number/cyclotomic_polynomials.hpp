#pragma once
#include "number/eratosthenes.hpp"
#include <vector>

// CUT begin
// cyclotomic polynominals : 円分多項式
// ret[i][j] = [x^j]\Phi_i(x) for i <= Nmax, which are known to be integers
std::vector<std::vector<int>> cyclotomic_polynomials(int Nmax) {
    std::vector<int> moebius = SieveOfEratosthenes(Nmax).GenerateMoebiusFunctionTable();
    std::vector<std::vector<int>> ret(Nmax + 1);
    auto multiply = [](const std::vector<int> &a, const std::vector<int> &b) { // a * b
        std::vector<int> ret(int(a.size() + b.size()) - 1);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++) { ret[i + j] += a[i] * b[j]; }
        return ret;
    };
    auto divide = [](std::vector<int> a, const std::vector<int> &b) { // a / b, abs(b[0]) = 1
        std::vector<int> ret(int(a.size()) - int(b.size()) + 1);
        for (size_t i = 0; i < ret.size(); i++) {
            ret[i] = a[i] / b[0];
            for (size_t j = 0; j < b.size(); j++) a[i + j] -= ret[i] * b[j];
        }
        while (ret.size() and !ret.back()) ret.pop_back();
        return ret;
    };

    for (int n = 0; n <= Nmax; n++) {
        std::vector<std::vector<int>> num, den;
        for (int d = 1; d <= n; d++)
            if (n % d == 0 and moebius[d]) {
                std::vector<int> r(n / d + 1);
                r[0] = -1, r.back() = 1;
                (moebius[d] > 0 ? num : den).push_back(r);
            }
        std::vector<int> phi{1};
        for (auto v : num) phi = multiply(phi, v);
        for (auto v : den) phi = divide(phi, v);
        ret[n] = phi;
    }
    return ret;
}
