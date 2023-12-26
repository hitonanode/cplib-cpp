#pragma once

#include <algorithm>
#include <utility>
#include <vector>

// Stern–Brocot tree
// Implementation based on https://miscalc.hatenablog.com/entry/2023/12/22/213007
namespace SternBrocotTree {

using T = long long;

struct Node {
    // Subtree contains all rational numbers in (p/q, r/s)
    T p = 0, q = 1, r = 1, s = 0; // root is (0, \infty)

    // (p + r) / (q + s)
    T num() const { return p + r; }
    T den() const { return q + s; }
};

enum class Direction { Left, Right };

struct Move {
    Direction dir;
    T steps;
};

Node apply(Node node, const Move &mv) {
    if (mv.dir == Direction::Left) {
        node.r += node.p * mv.steps;
        node.s += node.q * mv.steps;
    } else {
        node.p += node.r * mv.steps;
        node.q += node.s * mv.steps;
    }
    return node;
}

// path from root to num/den
std::vector<Move> encode_path(T num, T den) {
    std::vector<Move> ret;
    bool left = false;

    while (num != den) {
        T steps = num / den;
        if (den * steps == num) --steps;
        num -= steps * den;
        if (steps) ret.push_back({left ? Direction::Left : Direction::Right, steps});

        std::swap(num, den);
        left = !left;
    }

    return ret;
}

Node decode_path(const std::vector<Move> &path) {
    Node ret{0, 1, 1, 0};
    for (const Move &mv : path) ret = apply(ret, mv);

    return ret;
}

std::vector<Move> lca_path(const std::vector<Move> &path1, const std::vector<Move> &path2) {
    std::vector<Move> ret_path;

    int i1 = 0, i2 = 0;
    T step1 = path1.empty() ? 0 : path1.front().steps;
    T step2 = path2.empty() ? 0 : path2.front().steps;

    while (i1 < (int)path1.size() and i2 < (int)path2.size()) {
        if (!step1) {
            ++i1;
            if (i1 < (int)path1.size()) step1 = path1.at(i1).steps;
        } else if (!step2) {
            ++i2;
            if (i2 < (int)path2.size()) step2 = path2.at(i2).steps;
        } else {
            if (path1.at(i1).dir != path2.at(i2).dir) break;
            T steps = std::min(step1, step2);
            step1 -= steps;
            step2 -= steps;

            if (ret_path.empty() or ret_path.back().dir != path1.at(i1).dir) {
                Move move{path1.at(i1).dir, steps};
                ret_path.push_back(move);
            } else {
                ret_path.back().steps += steps;
            }
        }
    }

    return ret_path;
}

} // namespace SternBrocotTree
