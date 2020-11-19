#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"
#include "../modint_runtime.hpp"
#include <iostream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    ModIntRuntime::set_mod(M);
    vector<ModIntRuntime> montmort(N + 1);
    montmort[0] = 1, montmort[1] = 0;
    for (int i = 2; i <= N; i++) montmort[i] = (montmort[i - 1] + montmort[i - 2]) * (i - 1);
    for (int i = 1; i <= N; i++) cout << montmort[i] << (i == N ? '\n' : ' ');
}
