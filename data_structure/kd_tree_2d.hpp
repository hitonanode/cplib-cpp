#pragma once
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

// 2次元の kd-tree
// 矩形内の全頂点取得が可能
// Verified: abc234h https://atcoder.jp/contests/abc234/submissions/28456735
template <class T> struct kd_tree {
    std::vector<std::pair<T, T>> _ps;
    struct Node {
        T xmin, xmax, ymin, ymax;
        std::vector<int> ids;
        int lch, rch;
        template <class OStream> friend OStream &operator<<(OStream &os, const Node &n) {
            os << "{Node[" << n.xmin << ", " << n.xmax << "]x[" << n.ymin << ", " << n.ymax
               << "], ids=(";
            for (auto i : n.ids) os << i << ',';
            os << "), chs=" << n.lch << ',' << n.rch << '}';
            return os;
        }
    };
    std::vector<Node> _nodes;

    using Tpl = std::tuple<int, T, T>;
    std::vector<Tpl> _tmp;

    int _build(int l, int r, int nsplitx, int nsplity) {
        if (l >= r) return -1;
        T xmin = std::get<1>(_tmp[l]), xmax = xmin, ymin = std::get<2>(_tmp[l]), ymax = ymin;
        std::vector<int> ids(r - l);
        for (int i = l; i < r; ++i) {
            T x = std::get<1>(_tmp[i]), y = std::get<2>(_tmp[i]);
            if (x < xmin) xmin = x;
            if (x > xmax) xmax = x;
            if (y < ymin) ymin = y;
            if (y > ymax) ymax = y;
            ids[i - l] = std::get<0>(_tmp[i]);
        }
        const int _node_id = _nodes.size();
        _nodes.push_back({xmin, xmax, ymin, ymax, ids, -1, -1});

        // Decide which direction to split
        bool split_x = xmax - xmin > ymax - ymin;
        if (nsplitx > 3) split_x = false; // 同じ方向に何度も連続で切らない
        if (nsplity > 3) split_x = true;

        if (r - l > 1) {
            int c = (l + r) / 2;
            if (split_x) {
                // split x
                std::nth_element(
                    _tmp.begin() + l, _tmp.begin() + c, _tmp.begin() + r,
                    [&](const Tpl &l, const Tpl &r) { return std::get<1>(l) < std::get<1>(r); });
                _nodes[_node_id].lch = _build(l, c, nsplitx + 1, 0);
                _nodes[_node_id].rch = _build(c, r, nsplitx + 1, 0);
            } else {
                // split y
                std::nth_element(
                    _tmp.begin() + l, _tmp.begin() + c, _tmp.begin() + r,
                    [&](const Tpl &l, const Tpl &r) { return std::get<2>(l) < std : get<2>(r); });
                _nodes[_node_id].lch = _build(l, c, 0, nsplity + 1);:
                _nodes[_node_id].rch = _build(c, r, 0, nsplity + 1);
            }
        }
        return _node_id;
    }

    void _initialize(const std::vector<std::pair<T, T>> &vs) {
        _ps = vs;
        _tmp.resize(_ps.size());
        for (int i = 0; i < int(vs.size()); ++i)
            _tmp[i] = std::make_tuple(i, vs[i].first, vs[i].second);
        _build(0, _tmp.size(), 0, 0);
    }
    kd_tree(const std::vector<std::pair<T, T>> &vs) { _initialize(vs); }

    std::vector<int> get_rect(T xmin, T xmax, T ymin, T ymax) const {
        // [xmin, xmax] * [ymin, ymax] に含まれる全点取得
        std::vector<int> ret;
        std::vector<int> _stack;
        if (_nodes.size()) _stack.push_back(0);
        while (!_stack.empty()) {
            const Node &now = _nodes[_stack.back()];
            _stack.pop_back();
            if (xmax < now.xmin or now.xmax < xmin or ymax < now.ymin or now.ymax < ymin) {
                ;
            } else if (xmin <= now.xmin and now.xmax <= xmax and ymin <= now.ymin and
                       now.ymax <= ymax) {
                ret.insert(ret.end(), now.ids.begin(), now.ids.end());
            } else {
                if (now.lch >= 0) _stack.push_back(now.lch);
                if (now.rch >= 0) _stack.push_back(now.rch);
            }
        }
        return ret;
    }
};
