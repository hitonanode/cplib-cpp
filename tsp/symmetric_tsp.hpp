#pragma once

#include <algorithm>
#include <array>
#include <random>
#include <vector>

template <class DistanceMatrix, class Adjacents> struct SymmetricTSP {
    DistanceMatrix dist;
    Adjacents adjacents;
    using T = decltype((*dist.adjacents(0).begin()).second);

    struct Solution {
        T cost;
        std::vector<int> path;

        template <class OStream> friend OStream &operator<<(OStream &os, const Solution &x) {
            os << "[cost=" << x.cost << ", path=(";
            for (int i : x.path) os << i << ",";
            return os << x.path.front() << ")]";
        }
    };

    T eval(const Solution &sol) const {
        T ret = T();
        int now = sol.path.back();
        for (int nxt : sol.path) ret += dist(now, nxt), now = nxt;
        return ret;
    }

    SymmetricTSP(const DistanceMatrix &distance_matrix, const Adjacents &adjacents)
        : dist(distance_matrix), adjacents(adjacents) {}

    Solution nearest_neighbor(int init) const {
        if (n() == 0) return {T(), {}};
        int now = init;
        std::vector<int> ret{now}, alive(n(), 1);
        T len = T();
        ret.reserve(n());
        alive.at(now) = 0;
        while (int(ret.size()) < n()) {
            int nxt = -1;
            for (int i = 0; i < n(); ++i) {
                if (alive.at(i) and (nxt < 0 or dist(now, i) < dist(now, nxt))) nxt = i;
            }
            ret.push_back(nxt);
            alive.at(nxt) = 0;
            len += dist(now, nxt);
            now = nxt;
        }
        len += dist(ret.back(), ret.front());
        return Solution{len, ret};
    }

    void two_opt(Solution &sol) const {
        static std::vector<int> v_to_i;
        v_to_i.resize(n());
        for (int i = 0; i < n(); ++i) v_to_i.at(sol.path.at(i)) = i;
        while (true) {
            bool updated = false;
            for (int i = 0; i < n() and !updated; ++i) {
                const int u = sol.path.at(i), nxtu = sol.path.at(modn(i + 1));
                const T dunxtu = dist(u, nxtu);

                for (auto [v, duv] : adjacents(u)) {
                    if (duv >= dunxtu) break;
                    int j = v_to_i.at(v), nxtv = sol.path.at(modn(j + 1));
                    T diff = duv + dist(nxtu, nxtv) - dunxtu - dist(v, nxtv);
                    if (diff < 0) {
                        sol.cost += diff;
                        int l, r;
                        if (modn(j - i) < modn(i - j)) {
                            l = modn(i + 1), r = j;
                        } else {
                            l = modn(j + 1), r = i;
                        }
                        while (l != r) {
                            std::swap(sol.path.at(l), sol.path.at(r));
                            v_to_i.at(sol.path.at(l)) = l;
                            v_to_i.at(sol.path.at(r)) = r;
                            l = modn(l + 1);
                            if (l == r) break;
                            r = modn(r - 1);
                        }
                        updated = true;
                        break;
                    }
                }
                if (updated) break;

                for (auto [nxtv, dnxtunxtv] : adjacents(nxtu)) {
                    if (dnxtunxtv >= dunxtu) break;
                    int j = modn(v_to_i.at(nxtv) - 1), v = sol.path.at(j);
                    T diff = dist(u, v) + dnxtunxtv - dunxtu - dist(v, nxtv);
                    if (diff < 0) {
                        sol.cost += diff;
                        int l, r;
                        if (modn(j - i) < modn(i - j)) {
                            l = modn(i + 1), r = j;
                        } else {
                            l = modn(j + 1), r = i;
                        }
                        while (l != r) {
                            std::swap(sol.path.at(l), sol.path.at(r));
                            v_to_i.at(sol.path.at(l)) = l;
                            v_to_i.at(sol.path.at(r)) = r;
                            l = modn(l + 1);
                            if (l == r) break;
                            r = modn(r - 1);
                        }
                        updated = true;
                        break;
                    }
                }
            }
            if (!updated) break;
        }
    }

    bool three_opt(Solution &sol) const {
        static std::vector<int> v_to_i;
        v_to_i.resize(n());
        for (int i = 0; i < n(); ++i) v_to_i.at(sol.path.at(i)) = i;

        auto check_uvw_order = [](int u, int v, int w) {
            int i = v_to_i.at(u);
            int j = v_to_i.at(v);
            int k = v_to_i.at(w);
            if (i < j and j < k) return true;
            if (j < k and k < i) return true;
            if (k < i and i < j) return true;
            return false;
        };

        auto rev = [&](const int u, const int v) -> void {
            int l = v_to_i.at(u), r = v_to_i.at(v);
            while (l != r) {
                std::swap(sol.path.at(l), sol.path.at(r));
                l = modn(l + 1);
                if (l == r) break;
                r = modn(r - 1);
            }
        };

        static int i = 0;
        for (int nseen = 0; nseen < n(); ++nseen, i = modn(i + 1)) {
            const int u = sol.path.at(modn(i - 1)), nxtu = sol.path.at(i);
            const T dunxtu = dist(u, nxtu);

            // type 1 / 3
            for (const auto &[nxtv, dunxtv] : adjacents(u)) {
                if (dunxtv >= dunxtu) break;
                const int v = sol.path.at(modn(v_to_i.at(nxtv) - 1));
                const T dvnxtv = dist(v, nxtv);

                // type 1
                for (const auto &[nxtw, dvnxtw] : adjacents(v)) {
                    if (nxtw == nxtv or nxtw == nxtu) continue;
                    if (dunxtv + dvnxtw >= dunxtu + dvnxtv) break;
                    const int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));

                    if (!check_uvw_order(u, v, w)) continue;

                    const T current = dunxtu + dvnxtv + dist(w, nxtw);
                    if (T diff = dunxtv + dist(w, nxtu) + dvnxtw - current; diff < T()) {
                        sol.cost += diff;
                        rev(nxtu, v);
                        rev(nxtv, w);
                        rev(nxtw, u);
                        return true;
                    }
                }

                // type 3
                for (const auto &[w, dvw] : adjacents(v)) {
                    if (dunxtv + dvw >= dunxtu + dvnxtv) break;
                    if (!check_uvw_order(u, v, w)) continue;

                    const int nxtw = sol.path.at(modn(v_to_i.at(w) + 1));

                    const T current = dunxtu + dvnxtv + dist(w, nxtw);

                    if (T diff = dunxtv + dvw + dist(nxtu, nxtw) - current; diff < T()) {
                        sol.cost += diff;
                        rev(nxtw, u);
                        rev(nxtv, w);
                        return true;
                    }
                }
            }

            // type 2
            for (const auto &[nxtv, dnxtunxtv] : adjacents(nxtu)) {
                if (dnxtunxtv >= dunxtu) break;
                const int v = sol.path.at(modn(v_to_i.at(nxtv) - 1));
                const T dvnxtv = dist(v, nxtv);

                for (const auto &[nxtw, dvnxtw] : adjacents(v)) {
                    const int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));
                    if (dnxtunxtv + dvnxtw >= dunxtu + dvnxtv) break;
                    if (!check_uvw_order(u, v, w)) continue;

                    const T current = dunxtu + dvnxtv + dist(w, nxtw);
                    if (T diff = dist(u, w) + dnxtunxtv + dvnxtw - current; diff < T()) {
                        sol.cost += diff;
                        rev(nxtu, v);
                        rev(nxtw, u);
                        return true;
                    }
                }
            }

            // type 4
            for (const auto &[v, duv] : adjacents(u)) {
                if (duv >= dunxtu) break;
                const int nxtv = sol.path.at(modn(v_to_i.at(v) + 1));
                const T dvnxtv = dist(v, nxtv);

                for (const auto &[nxtw, dnxtvnxtw] : adjacents(nxtv)) {
                    const int w = sol.path.at(modn(v_to_i.at(nxtw) - 1));
                    if (duv + dnxtvnxtw >= dunxtu + dvnxtv) break;
                    if (!check_uvw_order(u, v, w)) continue;

                    const T current = dunxtu + dvnxtv + dist(w, nxtw);
                    if (T diff = duv + dist(nxtu, w) + dnxtvnxtw - current; diff < T()) {
                        sol.cost += diff;
                        rev(nxtu, v);
                        rev(nxtv, w);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    template <class Rng> bool double_bridge(Solution &sol, Rng &rng) const {
        if (n() < 8) return false;

        std::vector<int> &p = sol.path;
        int rand_rot = std::uniform_int_distribution<int>(0, n() - 1)(rng);
        std::rotate(p.begin(), p.begin() + rand_rot, p.end());

        static std::array<int, 3> arr;
        for (int &y : arr) y = std::uniform_int_distribution<int>(2, n() - 6)(rng);
        std::sort(arr.begin(), arr.end());
        const int i = arr.at(0), j = arr.at(1) + 2, k = arr.at(2) + 4;
        static std::array<T, 2> diffs;
        for (int d = 0; d < 2; ++d) {
            int u = p.at(n() - 1), nxtu = p.at(0);
            int v = p.at(i - 1), nxtv = p.at(i);
            int w = p.at(j - 1), nxtw = p.at(j);
            int x = p.at(k - 1), nxtx = p.at(k);
            diffs.at(d) = dist(u, nxtu) + dist(v, nxtv) + dist(w, nxtw) + dist(x, nxtx);
            if (d == 1) break;
            std::reverse(p.begin(), p.begin() + i);
            std::reverse(p.begin() + i, p.begin() + j);
            std::reverse(p.begin() + j, p.begin() + k);
            std::reverse(p.begin() + k, p.end());
        }
        sol.cost += diffs.at(1) - diffs.at(0);
        return true;
    }

    int n() const noexcept { return dist.n(); }
    int modn(int x) const noexcept {
        if (x < 0) return x + n();
        if (x >= n()) return x - n();
        return x;
    }
};
