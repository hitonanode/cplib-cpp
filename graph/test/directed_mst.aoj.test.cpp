#include "../directed_mst.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B"

int main() {
    int N, M, S;
    cin >> N >> M >> S;
    std::vector<std::tuple<int, int, long long>> edges;
    while (M--) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }
    MinimumSpanningArborescence<long long> msa(N, edges, S);
    cout << msa.ret << '\n';
}
