#pragma once
#include <array>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

template <class Uint> class radix_heap_array {
    int sz;
    Uint last;
    std::array<std::vector<std::pair<Uint, int>>, std::numeric_limits<Uint>::digits + 1> v;

    struct smallpii {
        unsigned b : 7;
        int j : 25;
    };
    std::vector<smallpii> i2bj;

    template <class U, typename std::enable_if<sizeof(U) == 4>::type * = nullptr>
    static inline unsigned bucket(U x) noexcept {
        return x ? 32 - __builtin_clz(x) : 0;
    }
    template <class U, typename std::enable_if<sizeof(U) == 8>::type * = nullptr>
    static inline unsigned bucket(U x) noexcept {
        return x ? 64 - __builtin_clzll(x) : 0;
    }

    void pull() {
        if (!v[0].empty()) return;
        int b = 1;
        while (v[b].empty()) ++b;
        last = v[b].back().first;
        for (int j = 0; j < int(v[b].size()); j++) last = std::min(last, v[b][j].first);
        for (int j = 0; j < int(v[b].size()); j++) {
            int i = v[b][j].second;
            auto bnxt = bucket(v[b][j].first ^ last);
            i2bj[i] = {bnxt, int(v[bnxt].size())}, v[bnxt].emplace_back(std::move(v[b][j]));
        }
        v[b].clear();
    }

public:
    radix_heap_array() : sz(0), last(0) {}
    bool empty() const noexcept { return sz == 0; }
    int argmin_pop() {
        pull(), --sz;
        int i = v[0].back().second;
        i2bj[i].j = -1;
        v[0].pop_back();
        return i;
    }
    void chmin(Uint vnew, int i) {
        if (i >= int(i2bj.size())) i2bj.resize(i + 1, {0, -1});
        if (i2bj[i].j < 0) {
            auto b = bucket(vnew ^ last);
            ++sz, i2bj[i] = {b, int(v[b].size())}, v[b].emplace_back(vnew, i);
        } else if (v[i2bj[i].b][i2bj[i].j].first > vnew) {
            auto bold = i2bj[i].b, bnew = bucket(vnew ^ last);
            if (bnew < bold) {
                int ilast = v[bold].back().second, j = i2bj[i].j;
                std::swap(v[bold][j], v[bold].back());
                i2bj[ilast].j = j, i2bj[i] = {bnew, int(v[bnew].size())};
                v[bnew].emplace_back(vnew, i), v[bold].pop_back();
            } else {
                v[bold][i2bj[i].j].first = vnew;
            }
        }
    }

    void pop() { argmin_pop(); }
    std::pair<Uint, int> top() { return pull(), v[0].back(); }
    [[deprecated("NOT usual emplace() opeation!")]] void emplace(Uint vnew, int i) {
        chmin(vnew, i);
    }

    void clear() noexcept { sz = 0, last = 0, i2bj.clear(); }
};
