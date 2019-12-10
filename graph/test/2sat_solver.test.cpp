#include "graph/strongly_connected_components.hpp"
#include <cassert>
#include <iostream>
#include <stdio.h>
#include <string>


int main() {

    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::string s;
    int N, M;
    std::cin >> s >> s >> N >> M;
    SATSolver solver(N);
    while (M--) {
        int a, b;
        std::cin >> a >> b >> s;
        solver.add_x_or_y_constraint(a > 0, abs(a) - 1, b > 0, abs(b) - 1);
    }
    if (solver.run()) {
        puts("s SATISFIABLE");
        printf("v ");
        for (int i = 0; i < N; i++) printf("%d ", (solver.solution[i] ? 1 : -1) * (i + 1));
        puts("0");
    }
    else {
        puts("s UNSATISFIABLE");
    }
}
