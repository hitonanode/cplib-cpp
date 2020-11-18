#pragma once
#include <map>
#include <queue>
#include <string>
#include <vector>

// CUT begin
// Aho-Corasick algorithm
// Complexity:
// - add_keyword(): O(|str|)
// - build_aho_corasick(): O(\sum_i |str_i|)
template <typename T> struct Trie {
    std::vector<std::map<char, int>> child;
    std::vector<int> fail;
    std::vector<T> node_info;
    int root;
    Trie() : child(1), fail(1), node_info(1), root(0) {}
    void add_keyword(const std::string &str, T info) {
        int now = 0;
        for (auto c : str) {
            if (child[now].count(c) == 0) {
                child[now][c] = fail.size();
                child.emplace_back();
                fail.emplace_back(root);
                node_info.emplace_back(0);
            }
            now = child[now][c];
        }
        node_info[now] += info;
    }

    void build_aho_corasick() {
        std::queue<int> q;
        for (auto pa : child[root]) q.push(pa.second);
        while (!q.empty()) {
            int s = q.front();
            q.pop();
            for (auto pa : child[s]) {
                int t = fail[s];
                while (t and child[t].count(pa.first) == 0) t = fail[t];
                int u = (child[t].count(pa.first) ? child[t][pa.first] : root);
                fail[pa.second] = u;
                node_info[pa.second] += node_info[u];
                q.push(pa.second);
            }
        }
    }
};
