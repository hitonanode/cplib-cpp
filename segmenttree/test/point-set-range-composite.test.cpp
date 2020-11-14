#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#include "modint.hpp"
#include <iostream>
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
using mint = ModInt<998244353>;

template <typename T>
struct PointSetRangeComposite : public NonrecursiveSegmentTree<std::pair<T, T>, std::pair<T, T>, bool>
{
    using T_NODE = std::pair<T, T>;
    using SegTree = NonrecursiveSegmentTree<T_NODE, T_NODE, bool>;
    T_NODE merge_data(const T_NODE &vl, const T_NODE &vr) override { return std::make_pair(vl.first * vr.first, vr.first * vl.second + vr.second); };
    T_NODE data2ret(const T_NODE &v, const bool &q) override { return v; }
    T_NODE merge_ret(const T_NODE &vl, const T_NODE &vr) override { return merge_data(vl, vr); };
    PointSetRangeComposite(const std::vector<T_NODE> &seq) : SegTree::NonrecursiveSegmentTree()
    {
        SegTree::initialize(seq, T_NODE(1, 0));
    };
};

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::pair<mint, mint>> A(N);
    for (auto &p : A)
    {
        std::cin >> p.first >> p.second;
    }
    PointSetRangeComposite<mint> s(A);
    while (Q--)
    {
        int q, l, r, x;
        std::cin >> q >> l >> r >> x;
        if (q)
        {
            auto ret = s.get(l, r);
            std::cout << ret.first * x + ret.second << '\n';
        }
        else
        {
            s.update(l, std::make_pair(r, x));
        }
    }
}
