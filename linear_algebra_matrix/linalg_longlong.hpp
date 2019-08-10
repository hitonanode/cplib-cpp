#include <cstdlib>
#include <vector>
using namespace std;
using lint = long long int;
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)


// Solve ax+by=gcd(a, b)
lint extgcd(lint a, lint b, lint &x, lint &y)
{
    lint d = a;
    if (b != 0) d = extgcd(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}
// Calc a^(-1) (MOD m)
lint mod_inverse(lint a, lint m)
{
    lint x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}
vector<vector<lint>> gauss_jordan(vector<vector<lint>> mtr, lint mod)
{
    // Gauss-Jordan elimination 行基本変形のみを用いるガウス消去法
    int H = mtr.size(), W = mtr[0].size(), c = 0;
    REP(h, H)
    {
        if (c == W) break;
        int piv = -1;
        FOR(j, h, H) if (mtr[j][c])
        {
            if (piv == -1 or abs(mtr[j][c]) > abs(mtr[piv][c])) piv = j;
        }
        if (piv == -1) { c++; h--; continue; }
        swap(mtr[piv], mtr[h]);
        if (h != piv) REP(w, W) mtr[piv][w] = mtr[piv][w] ? mod - mtr[piv][w] : 0; // 行列式符号不変
        lint pivinv = mod_inverse(mtr[h][c], mod);
        FOR(hh, h + 1, H) IFOR(w, c, W) mtr[hh][w] = (mtr[hh][w] - mtr[h][w] * mtr[hh][c] % mod * pivinv % mod + mod) % mod;
        c++;
    }
    return mtr;
}

lint mod_determinant(vector<vector<lint>> mtr, lint mod)
{
    lint ans = 1;
    mtr = gauss_jordan(mtr, mod);
    REP(i, mtr.size()) ans = ans * mtr[i][i] % mod;
    return ans;
}
vector<vector<lint>> matmul(const vector<vector<lint>> &A, const vector<vector<lint>> &B, lint mod)
{
    int H = A.size(), W = B[0].size(), K = B.size();
    vector<vector<lint>> C(H, vector<lint>(W));
    REP(i, H) REP(j, W) REP(k, K) (C[i][j] += A[i][k] * B[k][j]) %= mod;
    return C;
}
vector<lint> matmul(const vector<vector<lint>> &A, const vector<lint> &v, lint mod)
{
    vector<lint> res(A.size());
    REP(i, A.size()) REP(j, v.size()) (res[i] += A[i][j] * v[j]) %= mod;
    return res;
}
vector<vector<lint>> matpower(vector<vector<lint>> X, lint n, lint mod)
{
    vector<vector<lint>> res(X.size(), vector<lint>(X.size()));
    REP(i, res.size()) res[i][i] = 1;
    while (n)
    {
        if (n & 1) res = matmul(res, X, mod);
        X = matmul(X, X, mod); n >>= 1;
    }
    return res;
}
