#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include "../linear_sum_assignment.hpp"

#include "../../utilities/reader.hpp"
#include "../../utilities/writer.hpp"

#include <vector>
using namespace std;

int main() {
    const int N = rdi();
    vector A(N, vector<long long>(N));
    for (auto &v : A) {
        for (auto &x : v) x = rdi();
    }

    auto [ret, vs, f, g] = linear_sum_assignment::solve(N, N, A);

    wt_integer(ret, '\n');
    for (int i = 0; i < N - 1; ++i) wt_integer(vs.at(i), ' ');
    wt_integer(vs.back(), '\n');
}
