#pragma once
#include "matroid/matroid.hpp"
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
// Vector matroid on F2 : linearly independent vectors
// VDIM: max. dimension of vector space
// Verified: SRM526.5 1000 (Used only for linear independence check)
template <int VDIM>
struct F2VectorMatroid
{
    int M; // # of vectors
    vector<bitset<VDIM>> mat;
    mutable vector<unordered_map<State, vector<Element>>> cache;
    F2VectorMatroid() = default;
    F2VectorMatroid(const vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size()) {}

    // If I is independent and I + {e} is not, return elements of the circuit.
    // If e \in I, or I + {e} is independent, return empty vector.
    // If I is NOT independent, undefined.
    vector<Element> circuit(const State &I, const Element &e) const
    {
        assert(int(I.size()) == M and e < M);
        if (I[e]) return {};
        if (cache[e].count(I)) return cache[e][I];
        vector<bitset<VDIM + 1>> A(VDIM);
        vector<int> eid;
        for (int i = 0; i < M; i++) {
            if (!I[i]) continue;
            for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];
            eid.push_back(i);
            if (eid.size() > VDIM) return {};
        }
        int n = eid.size();
        for (int j = 0; j < VDIM; j++) A[j][n] = mat[e][j];
        for (int c = 0; c < n; c++) {
            int piv = -1;
            for (int r = c; r < VDIM; r++) {
                if (A[r][c]) {
                    piv = r;
                    break;
                }
            }
            if (piv == -1) return cache[e][I] = {};
            swap(A[piv], A[c]);
            for (int r = 0; r < VDIM; r++) {
                if (r != c and A[r][c]) A[r] ^= A[c];
            }
        }
        for (int r = n; r < VDIM; r++) if (A[r][n]) return cache[e][I] = {};
        vector<Element> ret;
        for (size_t i = 0; i < eid.size(); i++) {
            if (A[i][n]) ret.push_back(eid[i]);
        }
        return cache[e][I] = ret;
    }
};
