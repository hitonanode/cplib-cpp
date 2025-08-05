#define PROBLEM "https://yukicoder.me/problems/no/3148"
#include "../tree_pop_order_optimization.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    string str;
    cin >> N >> str;
    vector<vector<int>> child(N + 1);
    {
        vector<int> stk{0};
        int openid = 1;
        for (auto c : str) {
            if (c == '(') {
                stk.push_back(openid++);
            } else {
                int v = stk.back();
                stk.pop_back();
                if (stk.size()) child.at(stk.back()).push_back(v);
            }
        }
    }

    vector<long long> A(N);
    for (auto &a : A) cin >> a;
    A.insert(A.begin(), 0);

    vector<long long> B(A.size(), 1);
    B.at(0) = 0;

    vector<int> seq = Solve01OnTree(child, A, B, 0).first;
    std::reverse(seq.begin(), seq.end());

    long long dy = 0, ans = 0;
    for (int i : seq) {
        if (i == 0) continue;
        dy += A.at(i);
        ans += dy;
    }

    cout << ans << '\n';
}
