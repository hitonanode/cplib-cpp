#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../hessenberg_system.hpp"
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using mint = ModInt<1000000007>;

void test_lower_hessenberg_random() {
    for (int t = 0; t < 10000; ++t) {
        int N = t / 100;
        vector<vector<mint>> A(N, vector<mint>(N));
        vector<mint> x(N);

        const double p = rand_double();
        for (int i = 0; i < N; ++i) {
            x[i] = rand_int() % mint::mod();

            for (int j = 0; j < i; ++j) A[i][j] = rand_int() % mint::mod();
            A[i][i] = 1 + rand_int() % (mint::mod() - 1);
            if (i + 1 < N and rand_double() < p) A[i][i + 1] = rand_int() % mint::mod();
        }

        vector<mint> b(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) b[i] += A[i][j] * x[j];
        }

        assert(x == solve_lower_hessenberg<mint>(A, b));
    }
}

void test_upper_hessenberg_random() {
    for (int t = 0; t < 10000; ++t) {
        int N = t / 100;
        vector<vector<mint>> A(N, vector<mint>(N));
        vector<mint> x(N);

        const double p = rand_double();
        for (int i = 0; i < N; ++i) {
            x[i] = rand_int() % mint::mod();

            for (int j = i + 1; j < N; ++j) A[i][j] = rand_int() % mint::mod();
            A[i][i] = 1 + rand_int() % (mint::mod() - 1);
            if (i and rand_double() < p) A[i][i - 1] = rand_int() % mint::mod();
        }

        vector<mint> b(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) b[i] += A[i][j] * x[j];
        }

        assert(x == solve_upper_hessenberg<mint>(A, b));
    }
}

void test_lower_hessenberg_hand() {
    vector<vector<mint>> A{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
    vector<mint> b{2, 3, 4}, x{4, 2, 3};
    assert(solve_lower_hessenberg<mint>(A, b) == x);
}

int main() {
    test_lower_hessenberg_random();
    test_lower_hessenberg_hand();
    test_upper_hessenberg_random();
    cout << "Hello World\n";
}
