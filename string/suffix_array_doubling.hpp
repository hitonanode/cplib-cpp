#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

// CUT begin
// Suffix Array / Longest Common Prefix Array Construction
// Comlexity: O(N(log N)^2)
template <typename T> struct [[deprecated("use ACL based suffix array")]] SuffixArray {
    T S;                   // size: N
    std::vector<int> SA;   // Suffix Array (size: N + 1, SA[0] == N) SA[i] means S[SA[i]:]
    std::vector<int> rank; // Rank (inverse of SA) (size: N + 1, rank[N] == 0)
    std::vector<int> lcp;  // Longest Common Prefix Array (size: N) betw. S[SA[i]:] & S[SA[i + 1]:]

    SuffixArray(const T &str, bool gen_lcp = true) : S(str) {
        int N = S.size();
        SA.resize(N + 1);
        std::iota(SA.begin(), SA.end(), 0);
        rank.assign(N + 1, -1);
        for (int i = 0; i < N; i++) rank[i] = S[i];
        int _ord_mm = 1;

        auto _comp_suffarr = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = i + _ord_mm < (int)rank.size() ? rank[i + _ord_mm] : -1;
            int rj = j + _ord_mm < (int)rank.size() ? rank[j + _ord_mm] : -1;
            return ri < rj;
        };
        std::vector<int> tmp(N + 1);
        for (_ord_mm = 1; _ord_mm <= N; _ord_mm *= 2) {
            std::sort(SA.begin(), SA.end(), _comp_suffarr);
            tmp[SA[0]] = 0;
            for (int i = 1; i <= N; i++) { tmp[SA[i]] = tmp[SA[i - 1]] + _comp_suffarr(SA[i - 1], SA[i]); }
            rank = tmp;
        }
        if (!gen_lcp) return;

        lcp.assign(N, 0);
        int h = 0;
        for (int i = 0; i < N; i++) {
            int j = SA[rank[i] - 1];
            if (h) h--;
            for (; j + h < N and i + h < N; h++)
                if (S[j + h] != S[i + h]) break;
            lcp[rank[i] - 1] = h;
        }
    }
};
