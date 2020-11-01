#pragma once
#include <cassert>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

// CUT begin
// Static Range Inversion Query (Online)
// Complexity: O((N + Q)sqrt(N)) time, O(Nsqrt(N)) space (~128MB for N=1e5)
// Reference: <https://stackoverflow.com/questions/21763392/counting-inversions-in-ranges>
template <typename T>
struct StaticRangeInversion {
    const int N;
    const int bs;    // bucket size
    const int nb_bc; // # of buckets
    std::vector<int> vals;
    std::vector<std::pair<int, int>> vals_sorted;
    std::vector<std::vector<int>> presuf;
    std::vector<int> sufG, preH;
    std::vector<std::vector<long long>> R;

    StaticRangeInversion(const std::vector<T> &sequence) : N(sequence.size()), bs(ceil(sqrt(std::max(N, 1)))), nb_bc((N + bs - 1) / bs) {
        std::vector<T> dict = sequence;
        std::sort(dict.begin(), dict.end()), dict.erase(std::unique(dict.begin(), dict.end()), dict.end());
        const int D = dict.size();
        vals.reserve(N), vals_sorted.reserve(N);
        for (auto x : sequence) {
            vals.emplace_back(std::lower_bound(dict.begin(), dict.end(), x) - dict.begin());
            vals_sorted.emplace_back(vals.back(), int(vals.size()) - 1);
        }

        presuf.assign(nb_bc, std::vector<int>(N));
        sufG.resize(N), preH.resize(N);

        for (int ibc = 0; ibc < nb_bc; ibc++) {
            const int L = ibc * bs, R = std::min(L + bs, N);
            std::sort(vals_sorted.begin() + L, vals_sorted.begin() + R);
            std::vector<int> cnt(D + 1);
            for (int i = L; i < R; i++) {
                cnt[vals[i] + 1]++;
            }
            for (int i = 0; i < D; i++) {
                cnt[i + 1] += cnt[i];
            }
            for (int b = 0; b < ibc; b++) {
                for (int i = (b + 1) * bs - 1; i >= b * bs; i--) {
                    presuf[ibc][i] = presuf[ibc][i + 1] + cnt[vals[i]];
                }
            }
            for (int b = ibc + 1; b < bs; b++) {
                for (int i = b * bs; i < std::min((b + 1) * bs, N); i++) {
                    presuf[ibc][i] = (i == b * bs ? 0 : presuf[ibc][i - 1]) + cnt.back() - cnt[vals[i] + 1];
                }
            }
            for (int i = L + 1; i < R; i++) {
                preH[i] = preH[i - 1] + std::count_if(vals.begin() + L, vals.begin() + i, [&](int x) { return x > vals[i]; });
            }
            for (int i = R - 2; i >= L; i--) {
                sufG[i] = sufG[i + 1] + std::count_if(vals.begin() + i + 1, vals.begin() + R, [&](int x) { return x < vals[i]; });
            }
        }

        R.resize(nb_bc, std::vector<long long>(nb_bc));
        for (int i = nb_bc - 1; i >= 0; i--) {
            R[i][i] = sufG[i * bs];
            for (int j = i + 1; j < nb_bc; j++) {
                R[i][j] = R[i][j - 1] + R[i + 1][j] - R[i + 1][j - 1] + presuf[j][i * bs];
            }
        }
    }
    long long get(int l, int r) const {
        assert(l >= 0 and l <= N and r >= 0 and r <= N and l <= r);
        const int lb = (l + bs - 1) / bs, rb = (r == N ? nb_bc : r / bs) - 1;
        long long ret = 0;
        if (l / bs == (r - 1) / bs) {
            const int b = l / bs;
            ret += preH[r - 1] - (l % bs ? preH[l - 1] : 0);
            int less_cnt = 0;
            for (int p = b * bs, q = std::min((b + 1) * bs, N); p < q; p++) {
                less_cnt += (vals_sorted[p].second >= l and vals_sorted[p].second < r);
                ret -= less_cnt * (vals_sorted[p].second < l);
            }
            return ret;
        }
        ret += R[lb][rb];
        if (bs * lb > l) {
            ret += sufG[l];
            for (int b = lb; b <= rb; b++) {
                ret += presuf[b][l];
            }
        }
        if (bs * (rb + 1) < r) {
            ret += preH[r - 1];
            for (int b = lb; b <= rb; b++) {
                ret += presuf[b][r - 1];
            }
        }
        int less_cnt = 0, j = (rb + 1) * bs;
        for (int p = std::max(0, (lb - 1) * bs), q = lb * bs; p < q; p++) {
            if (vals_sorted[p].second >= l) {
                while (j < std::min(N, (rb + 2) * bs) and (vals_sorted[j].second >= r or vals_sorted[j].first < vals_sorted[p].first)) {
                    less_cnt += (vals_sorted[j].second < r), j++;
                }
                ret += less_cnt;
            }
        }
        return ret;
    }
};
