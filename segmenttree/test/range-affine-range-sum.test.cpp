#include "segmenttree/range-update-range-get.hpp"
#include "modint.hpp"
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

// RangeAffineRangeSum
// - update: x_i -> a * x_i + b for i in [l, r)
// - get: return x_l + ... + x_{r - 1}
template <typename T>
struct RangeAffineRangeSum : public LazySegmentTree<std::pair<T, int>, std::pair<T, T>, T, bool>
{
    using TDATA = std::pair<T, int>;
    using TLAZY = std::pair<T, T>;
    using SegTree = LazySegmentTree<TDATA, TLAZY, T, bool>;
    void merge_data(int pos)
    {
        this->data[pos].first = this->data[pos * 2].first + this->data[pos * 2 + 1].first;
        this->data[pos].second = this->data[pos * 2].second + this->data[pos * 2 + 1].second;
    }
    void reflect_lazy(int pos)
    {
        if (pos < this->head)
        {
            overlap_lazy(pos * 2, this->lazy[pos]);
            overlap_lazy(pos * 2 + 1, this->lazy[pos]);
        }
        this->data[pos].first = this->lazy[pos].first * this->data[pos].first + this->lazy[pos].second * this->data[pos].second;
        this->lazy[pos] = this->zero_lazy;
    }
    void overlap_lazy(int pos, const TLAZY &d)
    {
        this->lazy[pos] = std::make_pair(this->lazy[pos].first * d.first, this->lazy[pos].second * d.first + d.second);
    }
    T data2ret(int pos, const bool &)
    {
        return this->data[pos].first;
    }
    T merge_ret(const T &l, const T &r, const bool &)
    {
        return l + r;
    }
    RangeAffineRangeSum(const std::vector<T> &seq) : SegTree::LazySegmentTree()
    {
        std::vector<std::pair<T, int>> vinit;
        for (auto x : seq) vinit.emplace_back(x, 1);
        SegTree::initialize(vinit, std::make_pair(0, 0), std::make_pair(1, 0), T(0));
    };
};

using mint = ModInt<998244353>;

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<mint> A(N);
    for (auto &a : A) std::cin >> a;
    RangeAffineRangeSum<mint> segtree(A);
    while (Q--)
    {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q)
        {
            std::cout << segtree.get(l, r) << '\n';
        }
        else
        {
            mint b, c;
            std::cin >> b >> c;
            segtree.update(l, r, std::make_pair(b, c));
        }
    }
}
