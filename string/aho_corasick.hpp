#pragma once
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

template<typename T>
struct Trie
{
    vector<map<char, int>> child;
    vector<int> fail;
    vector<T> node_info;
    int root;
    Trie() : child(1), fail(1), node_info(1), root(0) {}
    void add_keyword(string str, T info)
    {
        int now = 0;
        for (auto c : str)
        {
            if (child[now].count(c) == 0)
            {
                child[now][c] = fail.size();
                child.emplace_back(map<char, int>());
                fail.emplace_back(root);
                node_info.emplace_back(0);
            }
            now = child[now][c];
        }
        node_info[now] += info;
    }

    void build_aho_corasick()
    {
        queue<int> q;
        for (auto pa : child[root]) q.push(pa.second);
        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            for (auto pa : child[s])
            {
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
