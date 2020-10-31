#include "convolution/fft_double.hpp"
#include "graph-tree/centroid_decomposition.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
using namespace std;

struct frequency_table_of_tree_distance_ {
    vector<unordered_set<int>> tos;
    vector<int> tmp;

    void _dfs(int now, int prv, int depth) {
        if (int(tmp.size()) <= depth) {
            tmp.resize(depth + 1, 0);
        }
        tmp[depth]++;
        for (auto nxt : tos[now]) {
            if (nxt != prv) {
                _dfs(nxt, now, depth + 1);
            }
        }
    }
    vector<int> cnt_dfs(int root) {
        return tmp.clear(), _dfs(root, -1, 0), tmp;
    }
    vector<long long> operator()(const vector<vector<int>>& to)
    {
        tos.clear();
        for (const auto v : to) {
            tos.emplace_back(v.begin(), v.end());
        }
        vector<long long> ret(to.size());
        for (auto root : CentroidDecomposition(to).centroid_decomposition(0)) {
            vector<vector<int>> vv;
            for (auto nxt : tos[root]) {
                tos[nxt].erase(root);
                vector<int> v = cnt_dfs(nxt);
                for (size_t i = 0; i < v.size(); i++) {
                    ret[i + 1] += v[i];
                }
                vv.emplace_back(v);
            }
            sort(vv.begin(), vv.end(), [&](const vector<int>& l, const vector<int>& r) { return l.size() < r.size(); });
            for (size_t j = 1; j < vv.size(); j++) {
                const vector<long long> c = fftconv(vv[j - 1], vv[j]);
                for (size_t i = 0; i < c.size(); i++) {
                    ret[i + 2] += c[i];
                }
                for (size_t i = 0; i < vv[j - 1].size(); i++) {
                    vv[j][i] += vv[j - 1][i];
                }
            }
            tos[root].clear();
        }
        return ret;
    }
} frequency_table_of_tree_distance;


int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<vector<int>> to(N);
    for (int i = 0; i < N - 1; i++) {
        int s, t;
        cin >> s >> t;
        to[s].emplace_back(t), to[t].emplace_back(s);
    }

    const vector<long long> ret = frequency_table_of_tree_distance(to);
    for (int i = 1; i < N; i++) {
        cout << ret[i] << ' ';
    }
    cout << '\n';
}
