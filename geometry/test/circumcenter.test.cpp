#include "../geometry.hpp"
#include "../triangle.hpp"
#include <iomanip>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C"
#define ERROR 0.000001
using namespace std;

int main() {
    Point2d<long double> X, Y, Z;
    cin >> X >> Y >> Z;
    auto c = circumcenter(X, Y, Z);
    cout << fixed << setprecision(10) << c.x << ' ' << c.y << ' ' << (X - c).norm() << '\n';
}
