#pragma once
#include <cassert>
#include <vector>

// Partition matroid (partitional matroid) : direct sum of uniform matroids
class PartitionMatroid {
    using Element = int;
    int M;
    std::vector<std::vector<Element>> parts;
    std::vector<int> belong;
    std::vector<int> R;
    std::vector<int> cnt;
    std::vector<std::vector<Element>> circuits;

public:
    // parts: partition of [0, 1, ..., M - 1]
    // R: only R[i] elements from parts[i] can be chosen for each i.
    PartitionMatroid(int M, const std::vector<std::vector<int>> &parts_, const std::vector<int> &R_)
        : M(M), parts(parts_), belong(M, -1), R(R_) {
        assert(parts.size() == R.size());
        for (int i = 0; i < int(parts.size()); i++) {
            for (Element e : parts[i]) belong[e] = i;
        }
        for (Element e = 0; e < M; e++) {
            // assert(belong[e] != -1);
            if (belong[e] == -1) {
                belong[e] = parts.size();
                parts.push_back({e});
                R.push_back(1);
            }
        }
    }
    int size() const { return M; }

    template <class State> void set(const State &I) {
        cnt = R;
        for (int e = 0; e < M; e++) {
            if (I[e]) cnt[belong[e]]--;
        }
        circuits.assign(cnt.size(), {});
        for (int e = 0; e < M; e++) {
            if (I[e] and cnt[belong[e]] == 0) circuits[belong[e]].push_back(e);
        }
    }

    std::vector<Element> circuit(const Element e) const {
        assert(0 <= e and e < M);
        int p = belong[e];
        if (cnt[p] == 0) {
            auto ret = circuits[p];
            ret.push_back(e);
            return ret;
        }
        return {};
    }
};
