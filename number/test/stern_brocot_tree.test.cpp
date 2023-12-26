#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"
#include "../stern_brocot_tree.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int Q;
    cin >> Q;
    while (Q--) {
        string type;
        cin >> type;
        if (type == "ENCODE_PATH") {
            long long a, b;
            cin >> a >> b;

            auto path = SternBrocotTree::encode_path(a, b);

            cout << path.size();
            for (auto mv : path) {
                cout << ' ' << (mv.dir == SternBrocotTree::Direction::Left ? 'L' : 'R') << ' '
                     << mv.steps;
            }
            cout << '\n';
        } else if (type == "DECODE_PATH") {
            std::vector<SternBrocotTree::Move> path;
            int k;
            cin >> k;
            while (k--) {
                char dir;
                long long steps;
                cin >> dir >> steps;
                path.push_back({dir == 'L' ? SternBrocotTree::Direction::Left
                                           : SternBrocotTree::Direction::Right,
                                steps});
            }

            auto node = SternBrocotTree::decode_path(path);
            cout << node.num() << ' ' << node.den() << '\n';
        } else if (type == "LCA") {
            long long a, b, c, d;
            cin >> a >> b >> c >> d;

            const auto path1 = SternBrocotTree::encode_path(a, b);
            const auto path2 = SternBrocotTree::encode_path(c, d);
            const auto path = SternBrocotTree::lca_path(path1, path2);
            const auto ret = SternBrocotTree::decode_path(path);
            cout << ret.num() << ' ' << ret.den() << '\n';
        } else if (type == "ANCESTOR") {
            long long k, a, b;
            cin >> k >> a >> b;

            auto path = SternBrocotTree::encode_path(a, b);

            SternBrocotTree::Node node;
            for (const auto &mv : path) {
                long long steps = min(mv.steps, k);
                k -= steps;
                node = SternBrocotTree::apply(node, {mv.dir, steps});
            }

            if (k) {
                cout << "-1\n";
            } else {
                cout << node.num() << ' ' << node.den() << '\n';
            }
        } else if (type == "RANGE") {
            long long a, b;
            cin >> a >> b;

            auto path = SternBrocotTree::encode_path(a, b);
            auto node = SternBrocotTree::decode_path(path);
            cout << node.p << ' ' << node.q << ' ' << node.r << ' ' << node.s << '\n';
        } else {
            assert(false);
        }
    }
}
