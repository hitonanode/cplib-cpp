#pragma once
#include <map>
#include <utility>

// CUT begin
// Add/erase ranges on \mathbb{Z}
// Basic implementation idea: https://satanic0258.github.io/snippets/data-structure/SegmentMap.html
template <typename Int> struct integer_segments {
    const Int INVALID = -1;
    Int _sz;
    std::map<Int, Int> mp;
    integer_segments() : _sz(0) {}

    // Get the range [l, r] that satisfies l <= x <= r, or [INVALID, INVALID] otherwise
    std::pair<Int, Int> get(Int x) const {
        auto itr = mp.upper_bound(x);
        if (itr == mp.begin() or (--itr)->second < x) return std::make_pair(INVALID, INVALID);
        return *itr;
    }

    void _mp_upd(Int l, Int r) {
        if (mp.count(l)) _sz -= mp[l] - l + 1;
        mp[l] = r, _sz += r - l + 1;
    }

    // Add {l, l + 1, ..., r} and return the merged segment which [l, r] belongs to
    std::pair<Int, Int> insert(Int l, Int r) {
        auto itl = mp.upper_bound(l), itr = mp.upper_bound(r + 1);
        if (itl != mp.begin() and (--itl)->second < l - 1) { ++itl; }
        if (itl != itr) {
            l = std::min(l, itl->first), r = std::max(r, std::prev(itr)->second);
            for (auto i = itl; i != itr; i++) _sz -= i->second - i->first + 1;
            mp.erase(itl, itr);
        }
        if (mp.count(l)) _sz -= mp[l] - l + 1;
        _mp_upd(l, r);
        return std::make_pair(l, r);
    }

    // Remove {l, l + 1, ..., r}
    void remove(Int l, Int r) {
        auto itl = mp.upper_bound(l), itr = mp.upper_bound(r);
        if (itl != mp.begin() and (--itl)->second < l) { ++itl; }
        if (itl == itr) { return; }
        Int tl = std::min(l, itl->first), tr = std::max(r, std::prev(itr)->second);
        for (auto i = itl; i != itr; i++) _sz -= i->second - i->first + 1;
        mp.erase(itl, itr);
        if (tl < l) _mp_upd(tl, l - 1);
        if (r < tr) _mp_upd(r + 1, tr);
    }

    Int count() const { return _sz; }

    // O((# of segments))
    Int find_by_order(Int k) const {
        if (mp.empty()) return -1;
        Int hi = mp.begin()->first - 1;
        for (const auto &p : mp) {
            const Int l = p.first, r = p.second;
            hi = std::max(hi, l - 1);
            Int add = std::max(Int(0), r - hi);
            if (add >= k + 1) return hi + k + 1;
            k -= add;
            hi = std::max(hi, r);
        }
        return -1;
    }

    // Count elements strictly less than x, O((# of segments))
    Int order_of_key(Int x) const {
        Int ret = 0;
        for (auto p : x) {
            if (p.first >= x) break;
            ret += std::min(x - 1, p.second) - p.first + 1;
        }
        return ret;
    }
};
