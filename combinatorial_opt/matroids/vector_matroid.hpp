#pragma once
#include <bitset>
#include <vector>

// CUT begin
// Vector matroid on F2 : linearly independent vectors
// VDIM: max. dimension of vector space
// Verified: SRM526.5 1000 (Used only for linear independence check)
template <int VDIM> class F2VectorMatroid {
    using Element = int;
    static void chxormin(std::bitset<VDIM> &l, const std::bitset<VDIM> &r) {
        int i = r._Find_first();
        if (i < VDIM and l[i]) l ^= r;
    }
    std::vector<std::bitset<VDIM>> mat;
    std::vector<Element> Iset;
    std::vector<std::vector<std::bitset<VDIM>>> bs;

public:
    F2VectorMatroid() = default;
    F2VectorMatroid(const std::vector<std::bitset<VDIM>> &bitmat) : mat(bitmat) {}

    int size() const { return mat.size(); }

    template <class State> void set(const State &I) {
        Iset.clear();
        for (int e = 0; e < size(); e++) {
            if (I[e]) Iset.push_back(e);
        }
        bs.assign(Iset.size() + 1, {});
        for (int i = 0; i < int(Iset.size()); i++) {
            for (int j = i; j < int(Iset.size()); j++) {
                auto v = mat[Iset[j]];
                for (auto b : bs[i]) chxormin(v, b);
                bs[i].push_back(v);
            }
        }
    }
    std::vector<Element> circuit(const Element &e) const {
        std::bitset<VDIM> v = mat[e];
        for (auto b : bs[0]) chxormin(v, b);
        if (v.any()) return {}; // I + {e} is independent

        std::vector<Element> ret{e};
        v = mat[e];
        for (int i = 0; i < int(Iset.size()); i++) {
            std::bitset<VDIM> w = v;
            for (auto b : bs[i + 1]) chxormin(w, b);
            if (w.any()) ret.push_back(Iset[i]);
            chxormin(v, bs[0][i]);
        }
        return ret;
    }
};
