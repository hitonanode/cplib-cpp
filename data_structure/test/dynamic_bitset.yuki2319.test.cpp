#define PROBLEM "https://yukicoder.me/problems/no/2319"
#include "../dynamic_bitset.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<dynamic_bitset> is_friend(N, dynamic_bitset(N)), world_has(N, dynamic_bitset(N));
    vector<int> P(N);

    for (int i = 0; i < N; ++i) cin >> P.at(i), P.at(i)--, world_has.at(P.at(i)).set(i);

    while (M--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        is_friend.at(a).set(b);
        is_friend.at(b).set(a);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (P.at(x) != P.at(y) and (world_has.at(P.at(y)) & is_friend.at(x)).any()) {
            puts("Yes");
            world_has.at(P.at(x)).reset(x);
            P.at(x) = P.at(y);
            world_has.at(P.at(x)).set(x);
        } else {
            puts("No");
        }
    }
}
