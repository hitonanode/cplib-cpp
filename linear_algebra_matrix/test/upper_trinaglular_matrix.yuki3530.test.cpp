#define PROBLEM "https://yukicoder.me/problems/no/3530"
#include "../upper_triangular_matrix.hpp"
#include "../../modint.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <atcoder/segtree>

using namespace std;
using S = UpperTriangular3d<ModInt998244353>;

S op(const S &l, const S &r) { return l * r; }
S e() {
    return S{
        .a00 = 1,
        .a01 = 0,
        .a02 = 0,
        .a11 = 1,
        .a12 = 0,
        .a22 = 1,
    };
}

S GenR() {
    return S{
        .a00 = ModInt998244353(3) / 4,
        .a01 = ModInt998244353(1) / 4,
        .a02 = 0,
        .a11 = 1,
        .a12 = 0,
        .a22 = 1,
    };
}
S GenL() {
    return S{
        .a00 = 1,
        .a01 = 0,
        .a02 = 0,
        .a11 = ModInt998244353(3) / 4,
        .a12 = ModInt998244353(1) / 4,
        .a22 = 1,
    };
}

ModInt998244353 Solve(vector<pair<int, int>> ps) {
    vector<tuple<int, int, int>> yxis;
    for (int i = 0; i < (int)ps.size(); ++i) {
        auto [x, y] = ps.at(i);
        yxis.emplace_back(y, x, i);
    }
    sort(yxis.begin(), yxis.end());

    const auto L = GenL(), R = GenR();
    const vector<S> init(ps.size(), R);
    atcoder::segtree<S, op, e> seg(init);

    int last_x = -1e9;

    ModInt998244353 ret = 0;

    map<int, vector<pair<int, int>>> x2yis;
    for (int i = 0; i < (int)ps.size(); ++i) {
        auto [x, y] = ps.at(i);
        x2yis[x].emplace_back(y, i);
    }
    for (auto [x, yis] : x2yis) {

        const ModInt998244353 dx = x - last_x;
        ret += dx * seg.all_prod().a02;

        for (auto [y, i] : yis) {
            const int idx =
                lower_bound(yxis.begin(), yxis.end(), make_tuple(y, x, i)) - yxis.begin();
            seg.set(idx, L);
        }

        last_x = x;
    }

    return ret;
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> xy(N);

    for (auto &[x, y] : xy) cin >> x >> y;

    const ModInt998244353 coeff = ModInt998244353(4).pow(N);
    ModInt998244353 ret1 = Solve(xy) * coeff;
    for (auto &[x, y] : xy) swap(x, y);
    ModInt998244353 ret2 = Solve(xy) * coeff;
    cout << (ret1 + ret2) * 2 << '\n';
}
