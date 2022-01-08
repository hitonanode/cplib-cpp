#pragma once
#include <array>
#include <cstddef>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

// Radix heap for unsigned integer
// https://github.com/iwiwi/radix-heap
template <class Uint, class Label, typename std::enable_if<std::is_unsigned<Uint>::value>::type * = nullptr>
class radix_heap {
    int sz;
    Uint last;
    std::array<std::vector<std::pair<Uint, Label>>, std::numeric_limits<Uint>::digits + 1> v;

    template <class U, typename std::enable_if<sizeof(U) == 4>::type * = nullptr>
    static inline int bucket(U x) noexcept {
        return x ? 32 - __builtin_clz(x) : 0;
    }
    template <class U, typename std::enable_if<sizeof(U) == 8>::type * = nullptr>
    static inline int bucket(U x) noexcept {
        return x ? 64 - __builtin_clzll(x) : 0;
    }

    void pull() {
        if (!v[0].empty()) return;
        int i = 1;
        while (v[i].empty()) ++i;
        last = v[i].back().first;
        for (int j = 0; j < int(v[i].size()); j++) last = std::min(last, v[i][j].first);
        for (int j = 0; j < int(v[i].size()); j++) {
            v[bucket(v[i][j].first ^ last)].emplace_back(std::move(v[i][j]));
        }
        v[i].clear();
    }

public:
    radix_heap() : sz(0), last(0) {
        static_assert(std::numeric_limits<Uint>::digits > 0, "Invalid type.");
    }
    std::size_t size() const noexcept { return sz; }
    bool empty() const noexcept { return sz == 0; }
    void push(Uint x, const Label &val) { ++sz, v[bucket(x ^ last)].emplace_back(x, val); }
    void push(Uint x, Label &&val) { ++sz, v[bucket(x ^ last)].emplace_back(x, std::move(val)); }
    template <class... Args> void emplace(Uint x, Args &&...args) {
        ++sz, v[bucket(x ^ last)].emplace_back(std::piecewise_construct, std::forward_as_tuple(x),
                                               std::forward_as_tuple(args...));
    }
    void pop() { pull(), --sz, v[0].pop_back(); }
    std::pair<Uint, Label> top() { return pull(), v[0].back(); }
    Uint top_key() { return pull(), last; }
    Label &top_label() { return pull(), v[0].back().second; }
    void clear() noexcept {
        sz = 0, last = 0;
        for (auto &vec : v) vec.clear();
    }
    void swap(radix_heap<Uint, Label> &a) {
        std::swap(sz, a.sz), std::swap(last, a.last), v.swap(a.v);
    }
};
