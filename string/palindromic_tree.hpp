#pragma once

#include <map>
#include <string>
#include <vector>

// Palindromic tree / Eertree （回文木）
namespace palindromic_tree {

template <class Key> class Node {
    int suffix_link_; // このノードからのsuffix link （suffix の最長回文）
    int length_; // このノードが表す回文の長さ。 -1 となる場合もあるので注意
    std::map<Key, int> children;

public:
    explicit Node(int suffix_link, int length) : suffix_link_(suffix_link), length_(length) {}

    int suffix_link() const { return suffix_link_; }

    int length() const { return length_; }

    int get_child(Key c) const {
        auto it = children.find(c);
        return (it == children.end()) ? -1 : it->second;
    }

    void set_child(int c, int nxt_idx) { children[c] = nxt_idx; }

    template <class OStream> friend OStream &operator<<(OStream &os, const Node &node) {
        os << "Node(suffix_link=" << node.suffix_link() << ", length=" << node.length()
           << ", children={";
        for (const auto &[c, nxt] : node.children) os << c << "->" << nxt << ", ";
        return os << "})";
    }
};

// Palindromic tree
// nodes[0] は長さ -1, nodes[1] は長さ 1 のダミーノード
template <class Key> struct Tree {
    std::vector<Node<Key>> nodes;

    Tree() { nodes = {Node<Key>(-1, -1), Node<Key>(0, 0)}; }

    // nodes[cursor] は s[0:i] の suffix palindrome を表す
    // 本関数はその nodes[cursor] の suffix palindrome であって更に s[0:(i + 1)] の suffix link となりうる最長のものを返す
    int find_next_suffix(const std::vector<Key> &s, int i, int cursor) {
        while (true) {
            if (cursor < 0) return 0;

            const int cur_len = nodes.at(cursor).length();
            const int opposite_pos = i - cur_len - 1;
            if (opposite_pos >= 0 and s.at(opposite_pos) == s.at(i)) return cursor;
            cursor = nodes.at(cursor).suffix_link();
        }
    }

    // 文字列 s を追加する。 Complexity: O(|s|)
    // callback(i, cursor) は s[0:(i + 1)] が追加された後の nodes[cursor] に対して行う処理
    template <class Callback> void add_string(const std::vector<Key> &s, Callback callback) {
        int cursor = 1;

        for (int i = 0; i < (int)s.size(); ++i) {

            cursor = find_next_suffix(s, i, cursor);

            int ch = nodes.at(cursor).get_child(s.at(i));

            if (ch < 0) {
                const int nxt_cursor = nodes.size();
                const int new_length = nodes.at(cursor).length() + 2;

                int new_suffix_link_par = find_next_suffix(s, i, nodes.at(cursor).suffix_link());
                int new_suffix_link = nodes.at(new_suffix_link_par).get_child(s.at(i));
                if (new_suffix_link < 0) new_suffix_link = 1;

                nodes.at(cursor).set_child(s.at(i), nxt_cursor);
                nodes.push_back(Node<Key>(new_suffix_link, new_length));
                cursor = nxt_cursor;

            } else {
                cursor = ch;
            }

            callback(i, cursor);
        }
    }

    template <class Callback> void add_string(const std::string &s, Callback callback) {
        add_string(std::vector<Key>{s.cbegin(), s.cend()}, callback);
    }

    template <class Vec> void add_string(const Vec &s) {
        add_string(s, [](int, int) {});
    }
};

} // namespace palindromic_tree
