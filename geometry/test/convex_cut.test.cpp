#include "../geometry.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
#define ERROR 0.000001

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    using Pt = Point2d<double>;
    vector<Pt> G(N);
    for (auto &x : G) cin >> x;

    cout << fixed << setprecision(8);
    int Q;
    cin >> Q;
    while (Q--) {
        Pt P1, P2;
        cin >> P1 >> P2;
        auto polygon = convex_cut(G, P1, P2);
        cout << signed_area_of_polygon(polygon) << '\n';
    }
}
