#include "../simplex.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
#define PROBLEM "https://yukicoder.me/problems/771"
#define ERROR 1e-6
using namespace std;

int main() {
    double C, D;
    cin >> C >> D;
    vector<vector<double>> A{{3.0 / 4.0, 2.0 / 7.0}, {1.0 / 4.0, 5.0 / 7.0}};
    vector<double> b{C, D};
    vector<double> c{1000, 2000};
    Simplex<> simplex(A, b, c);
    cout << fixed << setprecision(10) << simplex.ans << '\n';
}
