#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
#include "../floor_sum.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int N, M, A, B;
        cin >> N >> M >> A >> B;
        cout << floor_sum(N, M, A, B) << '\n';
    }
}
