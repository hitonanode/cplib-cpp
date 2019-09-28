#include <bits/stdc++.h>
using namespace std;

#define FOR(i, begin, end) for(int i=(begin);i<(end);i++)
#define REP(i, n) FOR(i,0,n)

// [Input] vector<int> f : size: 2^n, 破壊的
// [Output] vector<int> f : size: 2^n

// zeta_pattern1 高速ゼータ変換(1) 入力f[S]に対して、「Sを含む」T全部に対するf[T]の和が出てくる 計算量O(n 2^n)
void zeta_pattern1(vector<int> &f, int n) {
    REP(i, n) REP(b, 1<<n) if (!(b & (1 << i))) f[b] += f[b | (1 << i)];
}

// zeta_pattern2 高速ゼータ変換(2) 入力f[S]に対して、「Sに含まれる」T全部に対するf[T]の和が出てくる 計算量O(n 2^n)
void zeta_pattern2(vector<int> &f, int n) {
    REP(i, n) REP(b, 1<<n) if (b & (1 << i)) f[b] += f[b ^ (1 << i)];
}

// moebius_pattern1 高速メビウス変換(1) zeta_pattern1の逆変換 計算量O(n 2^n)
void moebius_pattern1(vector<int> &g, int n) {
    REP(i, n) REP(b, 1<<n) if (!(b & (1 << i))) g[b] -= g[b | (1 << i)];
}

// moebius_pattern2 高速メビウス変換(2) zeta_pattern2の逆変換 計算量O(n 2^n)
void moebius_pattern2(vector<int> &g, int n) {
    REP(i, n) REP(b, 1<<n) if (b & (1 << i)) g[b] -= g[b ^ (1 << i)];
}

int main()
{
    int N = 3;
    vector<int> x(1 << N);

    x[0] = 0;
    x[1] = 50;
    x[2] = 33;
    x[3] = 67;
    x[4] = 20;
    x[5] = 60;
    x[6] = 47;
    x[7] = 74;

    for (auto v : x) cout << v << " ";
    cout << endl;
    cout << endl;

    vector<int> y = x;

    moebius_pattern1(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;
    zeta_pattern1(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;

    cout << endl;

    moebius_pattern2(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;
    zeta_pattern2(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;

}
