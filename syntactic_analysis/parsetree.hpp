#pragma once
#include <string>
#include <utility>
#include <vector>

// CUT begin
// 構文解析木の構築
// Verification: codeFlyer E
// Example: <https://atcoder.jp/contests/bitflyer2018-final-open/submissions/3529930>
struct Parser {
    // 構文木情報
    int root_id;
    std::vector<std::pair<int, int>> child;
    std::string S;

    // 木のノードの情報（問題毎に書き換える）
    struct Node {
        long long val, val2;
        char type;
        int a_id;
        Node() {}
        Node(char type, int a_id) : type(type), a_id(a_id) {}
    };
    std::vector<Node> node;

    int len;
    void allocate(int newlen) {
        len = newlen;
        child.assign(len, std::make_pair(-1, -1));
        node.assign(len, {});
    }

    Parser(int initlen, std::string &str) : S(str) { allocate(initlen); }

    int nodeNow = 0;
    int _new_node() { return nodeNow++; }

    int a_now;
    int iter;
    int interpret() {
        iter = a_now = 0;
        return root_id = expr(iter);
    }

    int expr(int &begin) {
        int left = term(begin);
        while (S[begin] == '+' || S[begin] == '-') {
            char nxt_token = S[begin];
            int new_node = _new_node();
            begin++;
            int right = term(begin);
            node[new_node].type = nxt_token;
            child[new_node] = std::make_pair(left, right);
            left = new_node;
        }
        return left;
    }

    int term(int &begin) {
        int left = value(begin);
        while (S[begin] == '*') {
            int new_node = _new_node();
            begin++;
            int right = value(begin);
            node[new_node].type = '*';
            child[new_node] = std::make_pair(left, right);
            left = new_node;
        }
        return left;
    }

    int value(int &begin) {
        if (S[begin] == '(') {
            begin++;
            int ret = expr(begin);
            begin++;
            return ret;
        } else {
            int ret = _new_node();
            node[ret].type = 'a';
            node[ret].a_id = a_now++;
            begin++;
            return ret;
        }
    }

    void dfs(int now) {
        int l = child[now].first, r = child[now].second;
        /* operations for node[now], node[l], node[r] here */
        if (l >= 0) dfs(child[now].first);
        if (r >= 0) dfs(child[now].second);
        /* operations for node[now], node[l], node[r] here */
    }
};

/* example usage
std::string S;
Parser parser(200000, S);
auto root = parser.interpret();
parser.dfs(root);
*/
