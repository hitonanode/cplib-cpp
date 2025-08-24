#define PROBLEM "https://yukicoder.me/problems/no/950"
#include "number/discrete_logarithm.hpp"
#include "utilities/pow_op.hpp"

#include <array>
#include <iostream>
#include <set>
using namespace std;

using S = array<long long, 4>;

long long P;
S op(S l, S r) {
    return S{(((long long)l[0b00] * r[0b00] % P + (long long)l[0b01] * r[0b10] % P) % P),
             (((long long)l[0b00] * r[0b01] % P + (long long)l[0b01] * r[0b11] % P) % P),
             (((long long)l[0b10] * r[0b00] % P + (long long)l[0b11] * r[0b10] % P) % P),
             (((long long)l[0b10] * r[0b01] % P + (long long)l[0b11] * r[0b11] % P) % P)};
};

long long det(S x) { return ((long long)x[0] * x[3] % P - (long long)x[1] * x[2] % P + P) % P; };

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> P;

    S A, B;
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    const long long det_A = det(A), det_B = det(B);

    if (!det_A and det_B) {
        puts("-1");
        return 0;
    }

    const long long first_det_match = DiscreteLogarithmModNonzero<long long>(det_A, det_B, P);

    if (first_det_match < 0) {
        puts("-1");
        return 0;
    }

    if (pow_op<S>(A, first_det_match, op) == B) {
        cout << first_det_match << '\n';
        return 0;
    }

    const long long det_period = det_A ? DiscreteLogarithmModNonzero<long long>(det_A, 1, P) : 1;
    if (det_period < 0) {
        puts("-1");
        return 0;
    }

    const S init = pow_op<S>(A, first_det_match, op);
    const S x = pow_op<S>(A, det_period, op);

    const long long res = DiscreteLogarithm<S, S, set<S>>(x, init, B, op, op, P * 2);

    if (res < 0) {
        puts("-1");
    } else {
        cout << first_det_match + res * det_period << '\n';
    }
}
