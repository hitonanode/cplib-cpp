#define PROBLEM "https://yukicoder.me/problems/no/1615"
#include "../mcf_costscaling.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M, K, L;
    cin >> N >> M >> K >> L;
    mcf_costscaling<int, long long, 1, 10> mcf(N + M + 1);
    for (int l = 0; l < L; l++) {
        int x, y, z;
        cin >> x >> y >> z;
        mcf.add_edge(x, y + N, 1, -(1LL << z));
    }
    const int gs = 0;
    for (int i = 0; i < N; i++) mcf.add_edge(gs, i + 1, 1, 0);
    for (int j = 0; j < M; j++) mcf.add_edge(N + j + 1, gs, 1, 0);
    cout << -mcf.solve() << '\n';
}
