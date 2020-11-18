#pragma once
#include <map>
#include <utility>

// CUT begin
// Add/erase ranges on \mathbb{Z}
// Reference: <https://satanic0258.github.io/snippets/data-structure/SegmentMap.html> (Almost transcribed from this code)
template <typename Int> struct integer_segments {
    const Int INVALID = -1;
    std::map<Int, Int> mp;
    integer_segments() = default;

    // Get the range [l, r] that satisfies l <= x <= r, or [INVALID, INVALID] otherwise
    std::pair<Int, Int> get(Int x) const {
        auto itr = mp.upper_bound(x);
        if (itr == mp.begin() or (--itr)->second < x) { return std::make_pair(INVALID, INVALID); }
        return *itr;
    }

    // Add {l, l + 1, ..., r} and return the merged segment which [l, r] belongs to
    std::pair<Int, Int> insert(Int l, Int r) {
        auto itl = mp.upper_bound(l), itr = mp.upper_bound(r + 1);
        if (itl != mp.begin() and (--itl)->second < l - 1) { ++itl; }
        if (itl != itr) {
            l = std::min(l, itl->first), r = std::max(r, std::prev(itr)->second);
            mp.erase(itl, itr);
        }
        mp[l] = r;
        return std::make_pair(l, r);
    }

    // Remove {l, l + 1, ..., r}
    void remove(Int l, Int r) {
        auto itl = mp.upper_bound(l), itr = mp.upper_bound(r);
        if (itl != mp.begin() and (--itl)->second < l) { ++itl; }
        if (itl == itr) { return; }
        Int tl = std::min(l, itl->first), tr = std::max(r, std::prev(itr)->second);
        mp.erase(itl, itr);
        if (tl < l) { mp[tl] = l - 1; }
        if (r < tr) { mp[r + 1] = tr; }
    }
};
