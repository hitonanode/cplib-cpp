#define PROBLEM "https://yukicoder.me/problems/no/3392"
#include "../manacher.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> D(N - 1);
    for (int i = 0; i < N - 1; ++i) D.at(i) = A.at(i + 1) - A.at(i);

    long long ret = N;
    for (auto [l, r] : enumerate_palindromes(D)) ret += (r - l + 1) / 2;

    cout << ret << '\n';
}
