#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163"

#include "../linear_sum_assignment.hpp"

#include "../../utilities/reader.hpp"
#include "../../utilities/writer.hpp"

#include <numeric>
#include <vector>
using namespace std;

int main() {
    while (true) {
        const int nr = rdi(), nc = rdi();
        if (!nr) break;

        std::vector<int> B(nr), R(nc);
        for (auto &x : B) x = rdi();
        for (auto &x : R) x = rdi();

        std::vector C(nr, vector<int>(nc));
        for (int i = 0; i < nr; ++i) {
            for (int j = 0; j < nc; ++j) { C.at(i).at(j) = -(std::gcd(B.at(i), R.at(j)) > 1); }
        }

        auto [ret, vs, f, g] = linear_sum_assignment::solve(nr, nc, C);

        wt_integer(-ret, '\n');
    }
}
