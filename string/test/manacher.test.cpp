#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../manacher.hpp"

#include <iostream>
#include <string>
using namespace std;

int main() {
    string S;
    cin >> S;
    auto palindromes = enumerate_palindromes(S);
    for (auto [x, y] : palindromes) cout << y - x << ' ';
    cout << endl;
}
