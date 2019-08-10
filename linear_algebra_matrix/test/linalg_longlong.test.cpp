#include <iostream>
#include "linear_algebra_matrix/linalg_longlong.hpp"
using namespace std;
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D&lang=jp
using lint = long long;
template<typename T> istream &operator>>(istream &is, vector<T> &vec){ for (auto &v : vec) is >> v; return is; }

int main()
{
    int N, M, L;
    cin >> N >> M >> L;
    vector<vector<lint>> A(N, vector<lint>(M)), B(M, vector<lint>(L));
    cin >> A >> B;
    auto C = matmul(A, B, 1e13);
    REP(i, N)
    {
        REP(j, L - 1) printf("%lld ", C[i][j]);
        printf("%lld\n", C[i].back());
    }
}
