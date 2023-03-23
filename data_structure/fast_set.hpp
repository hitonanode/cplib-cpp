#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

// Sorted set of integers [0, n)
// Space complexity: (64 / 63) n + O(log n) bit
class fast_set {
    static constexpr int B = 64;

    int n;
    int cnt;
    std::vector<std::vector<uint64_t>> _d;

    static int bsf(uint64_t x) { return __builtin_ctzll(x); }
    static int bsr(uint64_t x) { return 63 - __builtin_clzll(x); }

public:
    // 0 以上 n_ 未満の整数が入れられる sorted set を作成
    fast_set(int n_) : n(n_), cnt(0) {
        do { n_ = (n_ + B - 1) / B, _d.push_back(std::vector<uint64_t>(n_)); } while (n_ > 1);
    }

    bool contains(int i) const {
        assert(0 <= i and i < n);
        return (_d.front().at(i / B) >> (i % B)) & 1;
    }

    void insert(int i) {
        assert(0 <= i and i < n);
        if (contains(i)) return;
        ++cnt;
        for (auto &vec : _d) {
            bool f = vec.at(i / B);
            vec.at(i / B) |= 1ULL << (i % B), i /= B;
            if (f) break;
        }
    }

    void erase(int i) {
        assert(0 <= i and i < n);
        if (!contains(i)) return;
        --cnt;
        for (auto &vec : _d) {
            vec.at(i / B) &= ~(1ULL << (i % B)), i /= B;
            if (vec.at(i)) break;
        }
    }

    // i 以上の最小要素 なければ default_val
    int next(int i, const int default_val) const {
        assert(0 <= i and i <= n);

        for (auto itr = _d.cbegin(); itr != _d.cend(); ++itr, i = i / B + 1) {
            if (i / B >= int(itr->size())) break;

            if (auto d = itr->at(i / B) >> (i % B); d) {
                i += bsf(d);
                while (itr != _d.cbegin()) i = i * B + bsf((--itr)->at(i));
                return i;
            }
        }

        return default_val;
    }
    int next(const int i) const { return next(i, n); }

    // i 以下の最小要素 なければ default_val
    int prev(int i, int default_val = -1) const {
        assert(-1 <= i and i < n);

        for (auto itr = _d.cbegin(); itr != _d.cend() and i >= 0; ++itr, i = i / B - 1) {
            if (auto d = itr->at(i / B) << (B - 1 - i % B); d) {
                i += bsr(d) - (B - 1);
                while (itr != _d.cbegin()) i = i * B + bsr((--itr)->at(i));
                return i;
            }
        }

        return default_val;
    }

    // return minimum element (if exists) or `n` (empty)
    int min() const { return next(0); }
    // return maximum element (if exists) or `-1` (empty)
    int max() const { return prev(n - 1); }
    int size() const { return cnt; }
    bool empty() const { return cnt == 0; }

    void clear() {
        if (!cnt) return;
        cnt = 0;
        auto rec = [&](auto &&self, int d, int x) -> void {
            if (d) {
                for (auto m = _d.at(d).at(x); m;) {
                    int i = bsf(m);
                    m -= 1ULL << i, self(self, d - 1, x * B + i);
                }
            }
            _d.at(d).at(x) = 0;
        };
        rec(rec, _d.size() - 1, 0);
    }
};
