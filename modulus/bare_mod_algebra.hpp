#pragma once
#include <algorithm>
#include <vector>
using namespace std;
using lint = long long;
using plint = pair<lint, lint>;

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

// 蟻本 P.262
// 中国剰余定理を利用して，色々な素数で割った余りから元の値を復元
// 連立線形合同式 A * x = B mod M の解
// Output: x = first MOD second
plint linear_congruence(const vector<lint> &A, const vector<lint> &B, const vector<lint> &M)
{
    lint x = 0, m = 1;
    for (int i = 0; i < (int)A.size(); i++)
    {
        lint a = A[i] * m, b = B[i] - A[i] * x, d = __gcd(M[i], a);
        if (b % d != 0)
            return plint(0, -1); // 解なし
        lint t = b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d);
        x += m * t;
        m *= M[i] / d;
    }
    return plint((x < 0 ? x + m : x), m);
}

lint power(lint x, lint n, lint MOD)
{
    lint ans = 1;
    while (n>0)
    {
        if (n & 1) (ans *= x) %= MOD;
        (x *= x) %= MOD;
       n >>= 1;
    }
   return ans;
}
