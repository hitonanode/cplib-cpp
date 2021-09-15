#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"
#include "../li_chao_tree.hpp"
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    std::vector<std::tuple<bool, int, int, int, long long>> qs;
    std::vector<long long> xs;

    int tp, l, r, a, p;
    long long b;

    while (N--) {
        cin >> l >> r >> a >> b;
        qs.emplace_back(false, l, r, a, b);
    }
    while (Q--) {
        cin >> tp;
        if (tp == 0) {
            cin >> l >> r >> a >> b;
            qs.emplace_back(false, l, r, a, b);
        } else {
            cin >> p;
            qs.emplace_back(true, p, 0, 0, 0);
            xs.push_back(p);
        }
    }
    li_chao_tree<long long, long long> tree;
    tree.init(xs);

    for (auto q : qs) {
        tie(tp, l, r, a, b) = q;
        if (tp == 0) tree.add_segment(l, r, a, b, 0);
        if (tp == 1) {
            auto ret = tree.get(l);
            if (ret.is_valid) {
                cout << ret.minval << '\n';
            } else {
                cout << "INFINITY\n";
            }
        }
    }
}
