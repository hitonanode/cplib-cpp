#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

// CUT begin
// LinearProgrammingOnBasePolyhedron : Maximize/minimize linear function on base polyhedron, using Edmonds' algorithm
//
// maximize/minimize cx s.t. (x on some base polyhedron)
// Reference: <https://www.amazon.co.jp/dp/B01N6G0579>, Sec. 2.4, Algorithm 2.2-2.3
//            "Submodular Functions, Matroids, and Certain Polyhedra" [Edmonds+, 1970]
// Used for: <https://yukicoder.me/problems/no/1316>
template <typename Tvalue> struct LinearProgrammingOnBasePolyhedron {
    using Tfunc = std::function<Tvalue(int, const std::vector<Tvalue> &)>;
    static Tvalue EPS;
    int N;
    std::vector<Tvalue> c;
    Tfunc maximize_xi;
    Tvalue xsum;
    bool minimize;

    Tvalue fun;
    std::vector<Tvalue> x;
    bool infeasible;

    void _init(const std::vector<Tvalue> &c_, Tfunc q_, Tvalue xsum_, Tvalue xlowerlimit, bool minimize_) {
        N = c_.size();
        c = c_;
        maximize_xi = q_;
        xsum = xsum_;
        minimize = minimize_;
        fun = 0;
        x.assign(N, xlowerlimit);
        infeasible = false;
    }

    void _solve() {
        std::vector<std::pair<Tvalue, int>> c2i(N);
        for (int i = 0; i < N; i++) c2i[i] = std::make_pair(c[i], i);

        std::sort(c2i.begin(), c2i.end());
        if (!minimize) std::reverse(c2i.begin(), c2i.end());
        for (const auto &p : c2i) {
            const int i = p.second;
            x[i] = maximize_xi(i, x);
        }
        Tvalue error = std::accumulate(x.begin(), x.end(), Tvalue(0)) - xsum;
        if (error > EPS or -error > EPS) {
            infeasible = true;
        } else {
            for (int i = 0; i < N; i++) fun += x[i] * c[i];
        }
    }

    LinearProgrammingOnBasePolyhedron(const std::vector<Tvalue> &c_, Tfunc q_, Tvalue xsum_, Tvalue xlowerlimit, bool minimize_) {
        _init(c_, q_, xsum_, xlowerlimit, minimize_);
        _solve();
    }
};
template <> long long LinearProgrammingOnBasePolyhedron<long long>::EPS = 0;
template <> long double LinearProgrammingOnBasePolyhedron<long double>::EPS = 1e-10;
