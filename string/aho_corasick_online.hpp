#pragma once
#include "aho_corasick.hpp"
#include <string>
#include <vector>

// CUT begin
// Aho-Corasick, Online keyword addition
// Implementation idea: <https://codeforces.com/blog/entry/10725?#comment-160742>
struct OnlineAhoCorasick {
    int n_keywords;
    int D = 62;
    using AC = AhoCorasick<TrieNodeFL, c2i0aA>;
    std::vector<std::string> keywords;
    std::vector<std::vector<int>> kwd_ids;
    std::vector<AC> automata;
    OnlineAhoCorasick() : n_keywords(0), kwd_ids(30), automata(30, D) {}

    // O(lg(n_keywords) |keyword|) amortized
    void add(const std::string &keyword) {
        int pos = __builtin_clz(~n_keywords);
        keywords.push_back(keyword), kwd_ids[pos].push_back(n_keywords);
        automata[pos].add(keyword);
        n_keywords++;
        for (int p = 0; p < pos; p++) {
            for (auto i : kwd_ids[p]) automata[pos].add(keywords[i]);
            kwd_ids[pos].insert(kwd_ids[pos].end(), kwd_ids[p].begin(), kwd_ids[p].end());
            kwd_ids[p].clear(), automata[p] = AC(D);
        }
    }

    // O(lg(n_keywords) |str| + \sum_i |keyword_i|)
    std::vector<int> match(const std::string &str) {
        std::vector<int> ret(keywords.size());
        for (unsigned p = 0; p < kwd_ids.size(); p++) {
            std::vector<int> subret = automata[p].match(str);
            for (unsigned i = 0; i < kwd_ids[p].size(); i++) ret[kwd_ids[p][i]] = subret[i];
        }
        return ret;
    }
};
