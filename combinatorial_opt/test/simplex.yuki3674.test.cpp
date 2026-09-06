#define PROBLEM "https://yukicoder.me/problems/no/3674"
#define ERROR 1e-6
#include "../simplex.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector A(N, vector<double>(M));
        for (auto &a : A) {
            for (auto &x : a) cin >> x;
        };

        // Minimize v = v_pos - v_neg over Bob's distribution q:
        // A q <= v, sum(q) = 1, q >= 0.
        for (auto &a : A) {
            a.push_back(-1);
            a.push_back(1);
        }

        A.push_back({});
        for (int t = 0; t < M; ++t) A.back().push_back(1);
        A.back().push_back(0);
        A.back().push_back(0);

        A.push_back({});
        for (int t = 0; t < M; ++t) A.back().push_back(-1);
        A.back().push_back(0);
        A.back().push_back(0);

        vector<double> B(A.size() - 2, 0);
        B.push_back(1);
        B.push_back(-1);

        vector<double> C(A.front().size());
        C.at(C.size() - 2) = -1;
        C.back() = 1;

        Simplex<double> simplex{A, B, C};
        cout << fixed << setprecision(15) << -simplex.ans << '\n';
    }
}
