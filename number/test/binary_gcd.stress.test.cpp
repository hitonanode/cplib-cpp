#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../binary_gcd.hpp"
#include <algorithm> // __gcd
#include <iostream>
using namespace std;

template <typename Int> void test_binary_gcd(Int lo, Int hi) {
    for (Int x = lo; x <= hi; x++) {
        for (Int y = lo; y <= hi; y++) {
            auto g = __gcd<Int>(x, y);
            if (g < 0) g = -g;
            if (binary_gcd(x, y) != g) {
                cerr << "Did not match : (x, y) = " << x << ',' << y << ')' << endl;
                throw;
            }
        }
    }
}

int main() {
    test_binary_gcd<int>(-1000, 1000);
    test_binary_gcd<unsigned int>(0, 2000);
    test_binary_gcd<long long>(-1000, 1000);
    test_binary_gcd<unsigned long long>(0, 2000);
    cout << "Hello World" << endl;
}
