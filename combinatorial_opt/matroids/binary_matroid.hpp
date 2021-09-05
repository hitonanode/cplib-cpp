#pragma once
#include <bitset>
#include <vector>

// CUT begin
// Binary matroid (vector matroid on F2) : linearly independent vectors
// VDIM: max. dimension of vector space
// Verified: SRM526.5 1000 (Used only for linear independence check)
// Verified: CF102156D 2019 Petrozavodsk Winter Camp, Yandex Cup D. Pick Your Own Nim
template <int VDIM> class BinaryMatroid {
    using Element = int;
    static void chxormin(std::bitset<VDIM> &l, const std::bitset<VDIM> &r) {
        int i = r._Find_first();
        if (i < VDIM and l[i]) l ^= r;
    }
    std::vector<std::bitset<VDIM>> mat;
    std::vector<Element> Iset;
    std::vector<std::vector<std::bitset<VDIM>>> bs;

public:
    BinaryMatroid() = default;
    BinaryMatroid(const std::vector<std::bitset<VDIM>> &bitmat) : mat(bitmat) {}

    int size() const { return mat.size(); }

    template <class State> void set(const State &I) {
        Iset.clear();
        for (int e = 0; e < size(); e++) {
            if (I[e]) Iset.push_back(e);
        }
        bs.assign(Iset.size() + 1, {});
        for (int i = 0; i < int(Iset.size()) + 1; i++) {
            for (int j = 0; j < int(Iset.size()); j++) {
                if (i == j) continue;
                auto v = mat[Iset[j]];
                for (const auto &b : bs[i]) chxormin(v, b);
                if (v.any()) bs[i].push_back(v);
            }
        }
    }
    std::vector<Element> circuit(const Element &e) const {
        std::bitset<VDIM> v = mat[e];
        for (const auto &b : bs.back()) chxormin(v, b);
        if (v.any()) return {}; // I + {e} is independent

        std::vector<Element> ret{e};
        for (int i = 0; i < int(Iset.size()); i++) {
            std::bitset<VDIM> w = mat[e];
            for (const auto &b : bs[i]) chxormin(w, b);
            if (w.any()) ret.push_back(Iset[i]);
        }
        return ret;
    }
};
