#pragma once
#include <map>
#include <utility>
#include <vector>
using namespace std;
using lint = long long;


vector<int> gen_primes(int N) // primes in [2, N]
{
    vector<int> ans;
    vector<int> alive(N + 1, 1);
    lint now = 2;
    for (; now * now <= N; now++)
    {
        if (alive[now]) ans.push_back(now);
        for (int t = now; t <= N; t += now) alive[t] = 0;
    }
    for (; now <= N; now++) if (alive[now]) ans.push_back(now);
    return ans;
}

map<lint, int> prime_factorization(lint N, const vector<int> &primes)
{
    if (N == 0) exit(1);
    map<lint, int> ans;
    for (auto v : primes)
    {
        while (!(N % v))
        {
            N /= v;
            ans[v]++;
        }
        if (N == 1) return ans;
    }
    ans[N]++;
    return ans;
    // exit(1);
}

vector<lint> divisors(lint n, const vector<int> &primes)
{
    map<lint, int> factor = prime_factorization(n, primes);
    vector<lint> now{1}, nxt;
    for (auto pa : factor)
    {
        nxt.clear();
        for (auto v : now)
        {
            for (int i = 0; i < pa.second + 1; i++)
            {
                nxt.push_back(v);
                v *= pa.first;
            }
        }
        swap(now, nxt);
    }
    return now;
}
