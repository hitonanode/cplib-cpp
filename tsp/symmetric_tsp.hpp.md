---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tsp/symmetric_tsp.hpp\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <random>\n#include <vector>\n\ntemplate <class DistanceMatrix,\
    \ class Adjacents> struct SymmetricTSP {\n    DistanceMatrix dist;\n    Adjacents\
    \ adjacents;\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\n\
    \    struct Solution {\n        T cost;\n        std::vector<int> path;\n\n  \
    \      template <class OStream> friend OStream &operator<<(OStream &os, const\
    \ Solution &x) {\n            os << \"[cost=\" << x.cost << \", path=(\";\n  \
    \          for (int i : x.path) os << i << \",\";\n            return os << x.path.front()\
    \ << \")]\";\n        }\n    };\n\n    T eval(const Solution &sol) const {\n \
    \       T ret = T();\n        int now = sol.path.back();\n        for (int nxt\
    \ : sol.path) ret += dist(now, nxt), now = nxt;\n        return ret;\n    }\n\n\
    \    SymmetricTSP(const DistanceMatrix &distance_matrix, const Adjacents &adjacents)\n\
    \        : dist(distance_matrix), adjacents(adjacents) {}\n\n    Solution nearest_neighbor(int\
    \ init) const {\n        if (n() == 0) return {T(), {}};\n        int now = init;\n\
    \        std::vector<int> ret{now}, alive(n(), 1);\n        T len = T();\n   \
    \     ret.reserve(n());\n        alive.at(now) = 0;\n        while (int(ret.size())\
    \ < n()) {\n            int nxt = -1;\n            for (int i = 0; i < n(); ++i)\
    \ {\n                if (alive.at(i) and (nxt < 0 or dist(now, i) < dist(now,\
    \ nxt))) nxt = i;\n            }\n            ret.push_back(nxt);\n          \
    \  alive.at(nxt) = 0;\n            len += dist(now, nxt);\n            now = nxt;\n\
    \        }\n        len += dist(ret.back(), ret.front());\n        return Solution{len,\
    \ ret};\n    }\n\n    void two_opt(Solution &sol) const {\n        static std::vector<int>\
    \ v_to_i;\n        v_to_i.resize(n());\n        for (int i = 0; i < n(); ++i)\
    \ v_to_i.at(sol.path.at(i)) = i;\n        while (true) {\n            bool updated\
    \ = false;\n            for (int i = 0; i < n() and !updated; ++i) {\n       \
    \         const int u = sol.path.at(i), nxtu = sol.path.at(modn(i + 1));\n   \
    \             const T dunxtu = dist(u, nxtu);\n\n                for (auto [v,\
    \ duv] : adjacents(u)) {\n                    if (duv >= dunxtu) break;\n    \
    \                int j = v_to_i.at(v), nxtv = sol.path.at(modn(j + 1));\n    \
    \                T diff = duv + dist(nxtu, nxtv) - dunxtu - dist(v, nxtv);\n \
    \                   if (diff < 0) {\n                        sol.cost += diff;\n\
    \                        int l, r;\n                        if (modn(j - i) <\
    \ modn(i - j)) {\n                            l = modn(i + 1), r = j;\n      \
    \                  } else {\n                            l = modn(j + 1), r =\
    \ i;\n                        }\n                        while (l != r) {\n  \
    \                          std::swap(sol.path.at(l), sol.path.at(r));\n      \
    \                      v_to_i.at(sol.path.at(l)) = l;\n                      \
    \      v_to_i.at(sol.path.at(r)) = r;\n                            l = modn(l\
    \ + 1);\n                            if (l == r) break;\n                    \
    \        r = modn(r - 1);\n                        }\n                       \
    \ updated = true;\n                        break;\n                    }\n   \
    \             }\n                if (updated) break;\n\n                for (auto\
    \ [nxtv, dnxtunxtv] : adjacents(nxtu)) {\n                    if (dnxtunxtv >=\
    \ dunxtu) break;\n                    int j = modn(v_to_i.at(nxtv) - 1), v = sol.path.at(j);\n\
    \                    T diff = dist(u, v) + dnxtunxtv - dunxtu - dist(v, nxtv);\n\
    \                    if (diff < 0) {\n                        sol.cost += diff;\n\
    \                        int l, r;\n                        if (modn(j - i) <\
    \ modn(i - j)) {\n                            l = modn(i + 1), r = j;\n      \
    \                  } else {\n                            l = modn(j + 1), r =\
    \ i;\n                        }\n                        while (l != r) {\n  \
    \                          std::swap(sol.path.at(l), sol.path.at(r));\n      \
    \                      v_to_i.at(sol.path.at(l)) = l;\n                      \
    \      v_to_i.at(sol.path.at(r)) = r;\n                            l = modn(l\
    \ + 1);\n                            if (l == r) break;\n                    \
    \        r = modn(r - 1);\n                        }\n                       \
    \ updated = true;\n                        break;\n                    }\n   \
    \             }\n            }\n            if (!updated) break;\n        }\n\
    \    }\n\n    bool three_opt(Solution &sol) const {\n        static std::vector<int>\
    \ v_to_i;\n        v_to_i.resize(n());\n        for (int i = 0; i < n(); ++i)\
    \ v_to_i.at(sol.path.at(i)) = i;\n\n        auto check_uvw_order = [](int u, int\
    \ v, int w) {\n            int i = v_to_i.at(u);\n            int j = v_to_i.at(v);\n\
    \            int k = v_to_i.at(w);\n            if (i < j and j < k) return true;\n\
    \            if (j < k and k < i) return true;\n            if (k < i and i <\
    \ j) return true;\n            return false;\n        };\n\n        auto rev =\
    \ [&](const int u, const int v) -> void {\n            int l = v_to_i.at(u), r\
    \ = v_to_i.at(v);\n            while (l != r) {\n                std::swap(sol.path.at(l),\
    \ sol.path.at(r));\n                l = modn(l + 1);\n                if (l ==\
    \ r) break;\n                r = modn(r - 1);\n            }\n        };\n\n \
    \       static int i = 0;\n        for (int nseen = 0; nseen < n(); ++nseen, i\
    \ = modn(i + 1)) {\n            const int u = sol.path.at(modn(i - 1)), nxtu =\
    \ sol.path.at(i);\n            const T dunxtu = dist(u, nxtu);\n\n           \
    \ // type 1 / 3\n            for (const auto &[nxtv, dunxtv] : adjacents(u)) {\n\
    \                if (dunxtv >= dunxtu) break;\n                const int v = sol.path.at(modn(v_to_i.at(nxtv)\
    \ - 1));\n                const T dvnxtv = dist(v, nxtv);\n\n                //\
    \ type 1\n                for (const auto &[nxtw, dvnxtw] : adjacents(v)) {\n\
    \                    if (nxtw == nxtv or nxtw == nxtu) continue;\n           \
    \         if (dunxtv + dvnxtw >= dunxtu + dvnxtv) break;\n                   \
    \ const int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));\n\n                  \
    \  if (!check_uvw_order(u, v, w)) continue;\n\n                    const T current\
    \ = dunxtu + dvnxtv + dist(w, nxtw);\n                    if (T diff = dunxtv\
    \ + dist(w, nxtu) + dvnxtw - current; diff < T()) {\n                        sol.cost\
    \ += diff;\n                        rev(nxtu, v);\n                        rev(nxtv,\
    \ w);\n                        rev(nxtw, u);\n                        return true;\n\
    \                    }\n                }\n\n                // type 3\n     \
    \           for (const auto &[w, dvw] : adjacents(v)) {\n                    if\
    \ (dunxtv + dvw >= dunxtu + dvnxtv) break;\n                    if (!check_uvw_order(u,\
    \ v, w)) continue;\n\n                    const int nxtw = sol.path.at(modn(v_to_i.at(w)\
    \ + 1));\n\n                    const T current = dunxtu + dvnxtv + dist(w, nxtw);\n\
    \n                    if (T diff = dunxtv + dvw + dist(nxtu, nxtw) - current;\
    \ diff < T()) {\n                        sol.cost += diff;\n                 \
    \       rev(nxtw, u);\n                        rev(nxtv, w);\n               \
    \         return true;\n                    }\n                }\n           \
    \ }\n\n            // type 2\n            for (const auto &[nxtv, dnxtunxtv] :\
    \ adjacents(nxtu)) {\n                if (dnxtunxtv >= dunxtu) break;\n      \
    \          const int v = sol.path.at(modn(v_to_i.at(nxtv) - 1));\n           \
    \     const T dvnxtv = dist(v, nxtv);\n\n                for (const auto &[nxtw,\
    \ dvnxtw] : adjacents(v)) {\n                    const int w = sol.path.at(modn(v_to_i.at(nxtw)\
    \ - 1));\n                    if (dnxtunxtv + dvnxtw >= dunxtu + dvnxtv) break;\n\
    \                    if (!check_uvw_order(u, v, w)) continue;\n\n            \
    \        const T current = dunxtu + dvnxtv + dist(w, nxtw);\n                \
    \    if (T diff = dist(u, w) + dnxtunxtv + dvnxtw - current; diff < T()) {\n \
    \                       sol.cost += diff;\n                        rev(nxtu, v);\n\
    \                        rev(nxtw, u);\n                        return true;\n\
    \                    }\n                }\n            }\n\n            // type\
    \ 4\n            for (const auto &[v, duv] : adjacents(u)) {\n               \
    \ if (duv >= dunxtu) break;\n                const int nxtv = sol.path.at(modn(v_to_i.at(v)\
    \ + 1));\n                const T dvnxtv = dist(v, nxtv);\n\n                for\
    \ (const auto &[nxtw, dnxtvnxtw] : adjacents(nxtv)) {\n                    const\
    \ int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));\n                    if (duv\
    \ + dnxtvnxtw >= dunxtu + dvnxtv) break;\n                    if (!check_uvw_order(u,\
    \ v, w)) continue;\n\n                    const T current = dunxtu + dvnxtv +\
    \ dist(w, nxtw);\n                    if (T diff = duv + dist(nxtu, w) + dnxtvnxtw\
    \ - current; diff < T()) {\n                        sol.cost += diff;\n      \
    \                  rev(nxtu, v);\n                        rev(nxtv, w);\n    \
    \                    return true;\n                    }\n                }\n\
    \            }\n        }\n        return false;\n    }\n\n    template <class\
    \ Rng> bool double_bridge(Solution &sol, Rng &rng) const {\n        if (n() <\
    \ 8) return false;\n\n        std::vector<int> &p = sol.path;\n        int rand_rot\
    \ = std::uniform_int_distribution<int>(0, n() - 1)(rng);\n        std::rotate(p.begin(),\
    \ p.begin() + rand_rot, p.end());\n\n        static std::array<int, 3> arr;\n\
    \        for (int &y : arr) y = std::uniform_int_distribution<int>(2, n() - 6)(rng);\n\
    \        std::sort(arr.begin(), arr.end());\n        const int i = arr.at(0),\
    \ j = arr.at(1) + 2, k = arr.at(2) + 4;\n        static std::array<T, 2> diffs;\n\
    \        for (int d = 0; d < 2; ++d) {\n            int u = p.at(n() - 1), nxtu\
    \ = p.at(0);\n            int v = p.at(i - 1), nxtv = p.at(i);\n            int\
    \ w = p.at(j - 1), nxtw = p.at(j);\n            int x = p.at(k - 1), nxtx = p.at(k);\n\
    \            diffs.at(d) = dist(u, nxtu) + dist(v, nxtv) + dist(w, nxtw) + dist(x,\
    \ nxtx);\n            if (d == 1) break;\n            std::reverse(p.begin(),\
    \ p.begin() + i);\n            std::reverse(p.begin() + i, p.begin() + j);\n \
    \           std::reverse(p.begin() + j, p.begin() + k);\n            std::reverse(p.begin()\
    \ + k, p.end());\n        }\n        sol.cost += diffs.at(1) - diffs.at(0);\n\
    \        return true;\n    }\n\n    int n() const noexcept { return dist.n();\
    \ }\n    int modn(int x) const noexcept {\n        if (x < 0) return x + n();\n\
    \        if (x >= n()) return x - n();\n        return x;\n    }\n};\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <array>\n#include <random>\n\
    #include <vector>\n\ntemplate <class DistanceMatrix, class Adjacents> struct SymmetricTSP\
    \ {\n    DistanceMatrix dist;\n    Adjacents adjacents;\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\
    \n    struct Solution {\n        T cost;\n        std::vector<int> path;\n\n \
    \       template <class OStream> friend OStream &operator<<(OStream &os, const\
    \ Solution &x) {\n            os << \"[cost=\" << x.cost << \", path=(\";\n  \
    \          for (int i : x.path) os << i << \",\";\n            return os << x.path.front()\
    \ << \")]\";\n        }\n    };\n\n    T eval(const Solution &sol) const {\n \
    \       T ret = T();\n        int now = sol.path.back();\n        for (int nxt\
    \ : sol.path) ret += dist(now, nxt), now = nxt;\n        return ret;\n    }\n\n\
    \    SymmetricTSP(const DistanceMatrix &distance_matrix, const Adjacents &adjacents)\n\
    \        : dist(distance_matrix), adjacents(adjacents) {}\n\n    Solution nearest_neighbor(int\
    \ init) const {\n        if (n() == 0) return {T(), {}};\n        int now = init;\n\
    \        std::vector<int> ret{now}, alive(n(), 1);\n        T len = T();\n   \
    \     ret.reserve(n());\n        alive.at(now) = 0;\n        while (int(ret.size())\
    \ < n()) {\n            int nxt = -1;\n            for (int i = 0; i < n(); ++i)\
    \ {\n                if (alive.at(i) and (nxt < 0 or dist(now, i) < dist(now,\
    \ nxt))) nxt = i;\n            }\n            ret.push_back(nxt);\n          \
    \  alive.at(nxt) = 0;\n            len += dist(now, nxt);\n            now = nxt;\n\
    \        }\n        len += dist(ret.back(), ret.front());\n        return Solution{len,\
    \ ret};\n    }\n\n    void two_opt(Solution &sol) const {\n        static std::vector<int>\
    \ v_to_i;\n        v_to_i.resize(n());\n        for (int i = 0; i < n(); ++i)\
    \ v_to_i.at(sol.path.at(i)) = i;\n        while (true) {\n            bool updated\
    \ = false;\n            for (int i = 0; i < n() and !updated; ++i) {\n       \
    \         const int u = sol.path.at(i), nxtu = sol.path.at(modn(i + 1));\n   \
    \             const T dunxtu = dist(u, nxtu);\n\n                for (auto [v,\
    \ duv] : adjacents(u)) {\n                    if (duv >= dunxtu) break;\n    \
    \                int j = v_to_i.at(v), nxtv = sol.path.at(modn(j + 1));\n    \
    \                T diff = duv + dist(nxtu, nxtv) - dunxtu - dist(v, nxtv);\n \
    \                   if (diff < 0) {\n                        sol.cost += diff;\n\
    \                        int l, r;\n                        if (modn(j - i) <\
    \ modn(i - j)) {\n                            l = modn(i + 1), r = j;\n      \
    \                  } else {\n                            l = modn(j + 1), r =\
    \ i;\n                        }\n                        while (l != r) {\n  \
    \                          std::swap(sol.path.at(l), sol.path.at(r));\n      \
    \                      v_to_i.at(sol.path.at(l)) = l;\n                      \
    \      v_to_i.at(sol.path.at(r)) = r;\n                            l = modn(l\
    \ + 1);\n                            if (l == r) break;\n                    \
    \        r = modn(r - 1);\n                        }\n                       \
    \ updated = true;\n                        break;\n                    }\n   \
    \             }\n                if (updated) break;\n\n                for (auto\
    \ [nxtv, dnxtunxtv] : adjacents(nxtu)) {\n                    if (dnxtunxtv >=\
    \ dunxtu) break;\n                    int j = modn(v_to_i.at(nxtv) - 1), v = sol.path.at(j);\n\
    \                    T diff = dist(u, v) + dnxtunxtv - dunxtu - dist(v, nxtv);\n\
    \                    if (diff < 0) {\n                        sol.cost += diff;\n\
    \                        int l, r;\n                        if (modn(j - i) <\
    \ modn(i - j)) {\n                            l = modn(i + 1), r = j;\n      \
    \                  } else {\n                            l = modn(j + 1), r =\
    \ i;\n                        }\n                        while (l != r) {\n  \
    \                          std::swap(sol.path.at(l), sol.path.at(r));\n      \
    \                      v_to_i.at(sol.path.at(l)) = l;\n                      \
    \      v_to_i.at(sol.path.at(r)) = r;\n                            l = modn(l\
    \ + 1);\n                            if (l == r) break;\n                    \
    \        r = modn(r - 1);\n                        }\n                       \
    \ updated = true;\n                        break;\n                    }\n   \
    \             }\n            }\n            if (!updated) break;\n        }\n\
    \    }\n\n    bool three_opt(Solution &sol) const {\n        static std::vector<int>\
    \ v_to_i;\n        v_to_i.resize(n());\n        for (int i = 0; i < n(); ++i)\
    \ v_to_i.at(sol.path.at(i)) = i;\n\n        auto check_uvw_order = [](int u, int\
    \ v, int w) {\n            int i = v_to_i.at(u);\n            int j = v_to_i.at(v);\n\
    \            int k = v_to_i.at(w);\n            if (i < j and j < k) return true;\n\
    \            if (j < k and k < i) return true;\n            if (k < i and i <\
    \ j) return true;\n            return false;\n        };\n\n        auto rev =\
    \ [&](const int u, const int v) -> void {\n            int l = v_to_i.at(u), r\
    \ = v_to_i.at(v);\n            while (l != r) {\n                std::swap(sol.path.at(l),\
    \ sol.path.at(r));\n                l = modn(l + 1);\n                if (l ==\
    \ r) break;\n                r = modn(r - 1);\n            }\n        };\n\n \
    \       static int i = 0;\n        for (int nseen = 0; nseen < n(); ++nseen, i\
    \ = modn(i + 1)) {\n            const int u = sol.path.at(modn(i - 1)), nxtu =\
    \ sol.path.at(i);\n            const T dunxtu = dist(u, nxtu);\n\n           \
    \ // type 1 / 3\n            for (const auto &[nxtv, dunxtv] : adjacents(u)) {\n\
    \                if (dunxtv >= dunxtu) break;\n                const int v = sol.path.at(modn(v_to_i.at(nxtv)\
    \ - 1));\n                const T dvnxtv = dist(v, nxtv);\n\n                //\
    \ type 1\n                for (const auto &[nxtw, dvnxtw] : adjacents(v)) {\n\
    \                    if (nxtw == nxtv or nxtw == nxtu) continue;\n           \
    \         if (dunxtv + dvnxtw >= dunxtu + dvnxtv) break;\n                   \
    \ const int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));\n\n                  \
    \  if (!check_uvw_order(u, v, w)) continue;\n\n                    const T current\
    \ = dunxtu + dvnxtv + dist(w, nxtw);\n                    if (T diff = dunxtv\
    \ + dist(w, nxtu) + dvnxtw - current; diff < T()) {\n                        sol.cost\
    \ += diff;\n                        rev(nxtu, v);\n                        rev(nxtv,\
    \ w);\n                        rev(nxtw, u);\n                        return true;\n\
    \                    }\n                }\n\n                // type 3\n     \
    \           for (const auto &[w, dvw] : adjacents(v)) {\n                    if\
    \ (dunxtv + dvw >= dunxtu + dvnxtv) break;\n                    if (!check_uvw_order(u,\
    \ v, w)) continue;\n\n                    const int nxtw = sol.path.at(modn(v_to_i.at(w)\
    \ + 1));\n\n                    const T current = dunxtu + dvnxtv + dist(w, nxtw);\n\
    \n                    if (T diff = dunxtv + dvw + dist(nxtu, nxtw) - current;\
    \ diff < T()) {\n                        sol.cost += diff;\n                 \
    \       rev(nxtw, u);\n                        rev(nxtv, w);\n               \
    \         return true;\n                    }\n                }\n           \
    \ }\n\n            // type 2\n            for (const auto &[nxtv, dnxtunxtv] :\
    \ adjacents(nxtu)) {\n                if (dnxtunxtv >= dunxtu) break;\n      \
    \          const int v = sol.path.at(modn(v_to_i.at(nxtv) - 1));\n           \
    \     const T dvnxtv = dist(v, nxtv);\n\n                for (const auto &[nxtw,\
    \ dvnxtw] : adjacents(v)) {\n                    const int w = sol.path.at(modn(v_to_i.at(nxtw)\
    \ - 1));\n                    if (dnxtunxtv + dvnxtw >= dunxtu + dvnxtv) break;\n\
    \                    if (!check_uvw_order(u, v, w)) continue;\n\n            \
    \        const T current = dunxtu + dvnxtv + dist(w, nxtw);\n                \
    \    if (T diff = dist(u, w) + dnxtunxtv + dvnxtw - current; diff < T()) {\n \
    \                       sol.cost += diff;\n                        rev(nxtu, v);\n\
    \                        rev(nxtw, u);\n                        return true;\n\
    \                    }\n                }\n            }\n\n            // type\
    \ 4\n            for (const auto &[v, duv] : adjacents(u)) {\n               \
    \ if (duv >= dunxtu) break;\n                const int nxtv = sol.path.at(modn(v_to_i.at(v)\
    \ + 1));\n                const T dvnxtv = dist(v, nxtv);\n\n                for\
    \ (const auto &[nxtw, dnxtvnxtw] : adjacents(nxtv)) {\n                    const\
    \ int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));\n                    if (duv\
    \ + dnxtvnxtw >= dunxtu + dvnxtv) break;\n                    if (!check_uvw_order(u,\
    \ v, w)) continue;\n\n                    const T current = dunxtu + dvnxtv +\
    \ dist(w, nxtw);\n                    if (T diff = duv + dist(nxtu, w) + dnxtvnxtw\
    \ - current; diff < T()) {\n                        sol.cost += diff;\n      \
    \                  rev(nxtu, v);\n                        rev(nxtv, w);\n    \
    \                    return true;\n                    }\n                }\n\
    \            }\n        }\n        return false;\n    }\n\n    template <class\
    \ Rng> bool double_bridge(Solution &sol, Rng &rng) const {\n        if (n() <\
    \ 8) return false;\n\n        std::vector<int> &p = sol.path;\n        int rand_rot\
    \ = std::uniform_int_distribution<int>(0, n() - 1)(rng);\n        std::rotate(p.begin(),\
    \ p.begin() + rand_rot, p.end());\n\n        static std::array<int, 3> arr;\n\
    \        for (int &y : arr) y = std::uniform_int_distribution<int>(2, n() - 6)(rng);\n\
    \        std::sort(arr.begin(), arr.end());\n        const int i = arr.at(0),\
    \ j = arr.at(1) + 2, k = arr.at(2) + 4;\n        static std::array<T, 2> diffs;\n\
    \        for (int d = 0; d < 2; ++d) {\n            int u = p.at(n() - 1), nxtu\
    \ = p.at(0);\n            int v = p.at(i - 1), nxtv = p.at(i);\n            int\
    \ w = p.at(j - 1), nxtw = p.at(j);\n            int x = p.at(k - 1), nxtx = p.at(k);\n\
    \            diffs.at(d) = dist(u, nxtu) + dist(v, nxtv) + dist(w, nxtw) + dist(x,\
    \ nxtx);\n            if (d == 1) break;\n            std::reverse(p.begin(),\
    \ p.begin() + i);\n            std::reverse(p.begin() + i, p.begin() + j);\n \
    \           std::reverse(p.begin() + j, p.begin() + k);\n            std::reverse(p.begin()\
    \ + k, p.end());\n        }\n        sol.cost += diffs.at(1) - diffs.at(0);\n\
    \        return true;\n    }\n\n    int n() const noexcept { return dist.n();\
    \ }\n    int modn(int x) const noexcept {\n        if (x < 0) return x + n();\n\
    \        if (x >= n()) return x - n();\n        return x;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/symmetric_tsp.hpp
  requiredBy: []
  timestamp: '2023-02-16 23:07:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/symmetric_tsp.hpp
layout: document
title: "Symmetric traveling salesperson problem \uFF08Symmetric TSP, \u5BFE\u79F0\u5DE1\
  \u56DE\u30BB\u30FC\u30EB\u30B9\u30DE\u30F3\u554F\u984C\uFF09"
---

対称巡回セールスマン問題のヒューリスティック解法． 2-opt, 3-opt, double-bridge 近傍による近傍探索や，Held–Karp 下界を利用した距離行列の前処理が可能．

## 問題例

### [競技プログラミングの鉄則　演習問題集 A46 - Heuristic 1](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_at)

実際の利用例を示す（以下は処理時間が長すぎるためそのまま貼っても TLE となる）。

```cpp
int main() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) cin >> X.at(i) >> Y.at(i);

    vector dmat(N, vector<long long>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) dmat.at(i).at(j) = roundl(hypot(X.at(i) - X.at(j), Y.at(i) - Y.at(j)) * 1000000LL);
    }

    dense_distance_matrix<long long> distance_matrix(dmat);

    // LKH で採用されている手法．
    // Held–Karp 下界を求める際の双対変数をもとに距離行列を変形し，
    // より短い辺を最適解に含まれやすくする．
    auto [w, pi] = held_karp_lower_bound(distance_matrix);
    distance_matrix.apply_pi(pi);

    auto adjacent_dmat = build_adjacent_info(distance_matrix, 20);

    SymmetricTSP tsp(distance_matrix, adjacent_dmat);

    decltype(tsp)::Solution best{1LL << 60, {}};

    auto sol = tsp.nearest_neighbor(0);
    mt19937 mt(100);

    for (int start = 0; start < N; ++start) {
        // 初期解の構築
        sol = tsp.nearest_neighbor(start);

        for (int _ = 0; _ < 30; ++_) {
            do {
                // two_opt() は改善可能性がなくなるまで 2-opt を行う
                tsp.two_opt(sol);
            } while (tsp.three_opt(sol));  // three_opt() は一度 3-opt による改善に成功した時点で return する

            if (sol.cost < best.cost) best = sol;
            tsp.double_bridge(sol, mt); // double-bridge 近傍の適用
        }
    }

    rotate(best.path.begin(), find(best.path.begin(), best.path.end(), 0), best.path.end());

    for (int x : best.path) cout << x + 1 << '\n';
    cout << best.path.front() + 1 << '\n';
}
```

なお、 [公開されているテストケース](https://www.dropbox.com/sh/nx3tnilzqz7df8a/AACmMZ47dbcz373G0KzuFRwCa/tessoku-book/A46?dl=0&subfolder_nav_tracking=1) に対して [Concorde](https://www.math.uwaterloo.ca/tsp/concorde.html) を適用して得られた厳密解は以下の通りで、5317 点が現状のテストケースで獲得可能な最高点と思われる．

| testcase | concorde | score |
| -------- | -------- | ----- |
| in01.txt | 9625.526 | 103   |
| in02.txt | 9385.646 | 106   |
| in03.txt | 9002.222 | 111   |
| in04.txt | 9489.165 | 105   |
| in05.txt | 9649.202 | 103   |
| in06.txt | 9177.047 | 108   |
| in07.txt | 9226.318 | 108   |
| in08.txt | 9353.698 | 106   |
| in09.txt | 9259.692 | 107   |
| in10.txt | 9216.752 | 108   |
| in11.txt | 9429.295 | 106   |
| in12.txt | 9290.442 | 107   |
| in13.txt | 9226.807 | 108   |
| in14.txt | 9104.148 | 109   |
| in15.txt | 9488.633 | 105   |
| in16.txt | 9138.817 | 109   |
| in17.txt | 9161.750 | 109   |
| in18.txt | 9353.783 | 106   |
| in19.txt | 9694.808 | 103   |
| in20.txt | 9455.553 | 105   |
| in21.txt | 9537.144 | 104   |
| in22.txt | 9132.504 | 109   |
| in23.txt | 9370.653 | 106   |
| in24.txt | 9264.462 | 107   |
| in25.txt | 9271.141 | 107   |
| in26.txt | 9670.472 | 103   |
| in27.txt | 9610.274 | 104   |
| in28.txt | 8948.458 | 111   |
| in29.txt | 9238.179 | 108   |
| in30.txt | 9348.935 | 106   |
| in31.txt | 9091.568 | 109   |
| in32.txt | 9279.178 | 107   |
| in33.txt | 9389.572 | 106   |
| in34.txt | 9421.150 | 106   |
| in35.txt | 9246.909 | 108   |
| in36.txt | 9420.217 | 106   |
| in37.txt | 9588.017 | 104   |
| in38.txt | 9467.334 | 105   |
| in39.txt | 9741.184 | 102   |
| in40.txt | 9607.822 | 104   |
| in41.txt | 9063.515 | 110   |
| in42.txt | 9450.781 | 105   |
| in43.txt | 9247.381 | 108   |
| in44.txt | 9434.954 | 105   |
| in45.txt | 9739.259 | 102   |
| in46.txt | 9232.337 | 108   |
| in47.txt | 9168.033 | 109   |
| in48.txt | 9509.942 | 105   |
| in49.txt | 9614.630 | 104   |
| in50.txt | 9315.151 | 107   |
| sum      |          | 5317  |

### [第3回 RCO日本橋ハーフマラソン 予選 A - ツーリストXの旅行計画](https://atcoder.jp/contests/rco-contest-2019-qual/tasks/rco_contest_2019_qual_a)

「移動距離の平均をパラメータと思って 3-opt + double bridge で TSP を解く」操作と「得られた TSP の解から移動距離の平均を再計算する」操作を繰り返すことで [本番一位を上回るスコアになる](https://atcoder.jp/contests/rco-contest-2019-qual/submissions/38915876)。

## 参考文献・リンク

- [K. Helsgaun, "An Effective Implementation of the Lin-Kernighan Traveling Salesman Heuristic," DATALOGISKE SKRIFTER (Writings on Computer Science), No. 81, 1998, Roskilde University.](http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf)
- 柳浦 睦憲, 茨木 俊秀, "組合せ最適化―メタ戦略を中心として (経営科学のニューフロンティア)," 2001, 朝倉書店．
- [2022年度 第1回ORセミナー 2022年6月1日 – 公益社団法人 日本オペレーションズ・リサーチ学会](https://orsj.org/?p=4182)
