#include <string>
#include <vector>

// CUT begin
struct Trie {
    char a_init;
    int D;
    int INVALID = -1;
    std::vector<std::vector<int>> child;
    using T_NODE = int;
    std::vector<T_NODE> v_info;
    Trie(char a_init = 'a', int D = 26) : a_init(a_init), D(D), child(1, std::vector<int>(D, INVALID)), v_info(1) {}
    void add_word(const std::string &str, T_NODE info) {
        int now = 0;
        for (auto &c : str) {
            if (child[now][c - a_init] == INVALID) {
                child[now][c - a_init] = child.size();
                child.emplace_back(std::vector<int>(D, INVALID));
                v_info.resize(child.size());
            }
            now = child[now][c - a_init];
        }
        v_info[now] += info;
    }
};
