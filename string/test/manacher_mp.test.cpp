#include "../manacher.hpp"
#include "../mp_algorithm.hpp"
#include <iostream>
#include <string>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934"
using namespace std;

int main() {
    int N;
    string T;
    cin >> N >> T;

    vector<int> mp = mp_algorithm(T);
    vector<int> mana = manacher(T);

    int rep = N - mp[N];
    for (int i = 2; i <= N; i++) {
        if (i + mana[i - 1] - 1 == N) {
            cout << i << '\n';
            return 0;
        }
        if (mana[i - 1] < i) continue;
        if ((2 * i - 2) % rep == 0) {
            cout << i << '\n';
            return 0;
        }
    }
}
