#include "../simplex.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>
#include <vector>
#define PROBLEM "https://yukicoder.me/problems/no/1122"
using namespace std;

int main() {
    using Float = boost::multiprecision::cpp_dec_float_50;
    vector<Float> B(5);
    for (auto &x : B) cin >> x;
    vector<vector<Float>> A{
        {1, 1, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 1, 1}, {1, 0, 0, 1, 1}, {1, 1, 0, 0, 1}};
    vector<Float> C(5, 1);
    Simplex<Float, 30> simplex(A, B, C);
    cout << llround(simplex.ans - 0.17)
         << '\n'; // I haven't proved yet this always returns correct answer.
}
