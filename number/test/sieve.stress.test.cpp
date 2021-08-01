#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../sieve.hpp"
#include "../modint_runtime.hpp"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct Case {
    int SIEVE_SIZE;
    int MAX;
};

int euler_phi(int x) {
    int ret = 0;
    for (int d = 1; d <= x; d++) ret += (std::__gcd(d, x) == 1);
    return ret;
}

void test_divisors(Case testcase) {
    const Sieve sieve(testcase.SIEVE_SIZE);
    for (int x = 1; x <= testcase.MAX; x++) {
        auto divs = sieve.divisors(x);
        std::vector<int> is_div(x + 1);
        for (auto d : divs) is_div.at(d) = 1;
        for (int y = 1; y <= x; y++) assert(is_div.at(y) == (x % y == 0));
    }

    cerr << "divisors(): passed" << endl;
}

void test_euler_of_divisors(Case testcase) {
    const Sieve sieve(testcase.SIEVE_SIZE);
    for (int x = 1; x <= testcase.MAX; x++) {
        auto div2euler = sieve.euler_of_divisors(x);
        for (auto de : div2euler) {
            assert(euler_phi(de.first) == de.second);
            assert(x % de.first == 0);
        }
        assert(div2euler.size() == sieve.divisors(x).size());
    }

    cerr << "euler_of_divisors(): passed" << endl;
}

void test_moebius_table(int HI) {
    const Sieve sieve_hi(HI);
    const auto answer = sieve_hi.GenerateMoebiusFunctionTable();
    assert(int(answer.size()) == HI + 1);

    for (int x = 1; x <= HI; x++) {
        int ret = 1;
        for (auto p : sieve_hi.primes) {
            if (x % (p * p) == 0) ret = 0;
            if (x % p == 0) ret *= -1;
        }
        assert(answer[x] == ret);
    }

    for (int x = 1; x <= HI - 1; x++) {
        auto mu = Sieve(x).GenerateMoebiusFunctionTable();
        assert(int(mu.size()) == x + 1);
        for (int i = 0; i < x + 1; i++) assert(mu[i] == answer[i]);
    }

    cerr << "GenerateMoebiusFunctionTable(): passed" << endl;
}

void test_enumerate_kth_pows(int hi_sieve_size) {
    for (int sieve_size = 1; sieve_size <= hi_sieve_size; sieve_size++) {
        const Sieve sieve(sieve_size);
        for (int nmax = 1; nmax <= sieve_size; nmax++) {
            for (int p = 1; p <= 20; p++) {
                using mint = ModIntRuntime;
                mint::set_mod(p);
                for (int k = 0; k < 10; k++) {
                    auto ret = sieve.enumerate_kth_pows<mint>(k, nmax);
                    assert(int(ret.size()) == nmax + 1);
                    for (int i = 0; i <= nmax; i++) assert(ret[i] == mint(i).pow(k));
                }
            }
        }
    }
    cerr << "enumerate_kth_pows(): passed" << endl;
}

int main() {
    std::vector<Case> cases{{31, 31 * 31}, {100, 1000}, {2, 4}};
    for (auto testcase : cases) {
        test_divisors(testcase);
        test_euler_of_divisors(testcase);
    }

    test_moebius_table(1000);
    test_enumerate_kth_pows(100);

    puts("Hello World");
}
