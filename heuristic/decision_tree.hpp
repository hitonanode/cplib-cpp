#pragma once
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

struct decision_tree {
    decision_tree() = default;

    using ull = unsigned long long;
    static const int D = 64;

    struct Node {
        bool is_leaf = false;
        bool mixed = false;
        bool label = false;

        int split_by = -1;
        int ch1 = -1;
        int ch0 = -1;
        std::string encode() const {
            int x = is_leaf * 4 + mixed * 2 + label;
            return char('0' + x) + std::to_string(split_by) + "/" + std::to_string(ch1) + "/" +
                   std::to_string(ch0);
        }
        static Node decode(const std::string &s) {
            int x = s.at(0) - '0';
            int split_by = -1, ch1 = -1, ch0 = -1;
            char tmp;
            std::stringstream ss(s.substr(1));
            ss >> split_by >> tmp >> ch1 >> tmp >> ch0;
            return Node{bool(x / 4 % 2), bool(x / 2 % 2), bool(x % 2), split_by, ch1, ch0};
        }
    };

    std::vector<Node> nodes;

    std::string encode() const {
        std::string ret;
        for (const Node &n : nodes) ret += n.encode() + " ";
        if (!ret.empty()) ret.pop_back();
        return ret;
    }

    static decision_tree decode(const std::string &s) {
        std::stringstream ss(s);
        decision_tree ret;
        while (!ss.eof()) {
            std::string s;
            ss >> s;
            ret.nodes.push_back(Node::decode(s));
        }
        return ret;
    }

    static double GiniImpurity(double p) { return 2 * p * (1 - p); }

    int rec_fit(std::vector<ull> &Xy, std::vector<int> &pos_xsum, std::vector<int> &neg_xsum,
                int npos, int nneg, int dim) {
        const int node_id = nodes.size();
        // dbg(make_tuple("Call", node_id, Xy.size(), nneg, npos));
        nodes.push_back(Node());
        if (!npos or !nneg) {
            nodes.back().is_leaf = true;
            nodes.back().label = npos ? true : false;
        } else {
            double piv_max = 1e30;
            int arg_piv_max = -1;

            for (int c = 0; c < dim; ++c) {
                double ch1_rate = 1.0 * (pos_xsum[c] + neg_xsum[c]) / (npos + nneg);
                if (0.0 < ch1_rate and ch1_rate < 1.0) {
                    double tmp =
                        ch1_rate * GiniImpurity(1.0 * pos_xsum[c] / (pos_xsum[c] + neg_xsum[c])) +
                        (1 - ch1_rate) * GiniImpurity(1.0 * (npos - pos_xsum[c]) /
                                                      (npos + nneg - pos_xsum[c] - neg_xsum[c]));
                    if (tmp < piv_max) piv_max = tmp, arg_piv_max = c;
                }
            }

            if (arg_piv_max >= 0) {
                const int nb_ch1 = pos_xsum.at(arg_piv_max) + neg_xsum.at(arg_piv_max);
                std::vector<ull> Xy1;
                std::vector<int> pos_xsum1(dim), neg_xsum1(dim);
                int npos1 = 0, nneg1 = 0;

                const bool mode = (nb_ch1 >= npos + nneg);

                for (int i = 0; i < int(Xy.size());) {
                    if (mode ^ ((Xy[i] >> arg_piv_max) & 1)) {
                        Xy1.push_back(Xy[i]);
                        const bool y = (Xy[i] >> (D - 1)) & 1;
                        --(y ? npos : nneg);
                        ++(y ? npos1 : nneg1);
                        for (int j = 0; j < dim; ++j) {
                            if ((Xy[i] >> j) & 1) {
                                --(y ? pos_xsum : neg_xsum)[j];
                                ++(y ? pos_xsum1 : neg_xsum1)[j];
                            }
                        }
                        std::swap(Xy[i], Xy.back());
                        Xy.pop_back();
                    } else {
                        ++i;
                    }
                }

                nodes.at(node_id).split_by = arg_piv_max;
                nodes.at(node_id).ch1 = rec_fit(Xy, pos_xsum, neg_xsum, npos, nneg, dim);
                nodes.at(node_id).ch0 = rec_fit(Xy1, pos_xsum1, neg_xsum1, npos1, nneg1, dim);

                if (!mode) std::swap(nodes[node_id].ch0, nodes[node_id].ch1);
            } else {
                nodes.at(node_id).is_leaf = true;
                nodes.at(node_id).mixed = true;
                nodes.at(node_id).label = npos > nneg;
            }
        }
        return node_id;
    }

    template <class T1, class T2>
    void fit(const std::vector<std::vector<T1>> &X, const std::vector<T2> &y, int dim = 0) {
        if (dim == 0 and !X.empty()) dim = X.front().size();
        assert(dim <= 63);
        assert(X.size() == y.size());

        std::vector<ull> Xy(X.size());
        std::vector<int> pos_xsum(dim), neg_xsum(dim);
        int npos = 0, nneg = 0;
        for (int i = 0; i < int(X.size()); ++i) {
            bool yi = y[i];
            ++(yi ? npos : nneg);
            ull xy = ull(yi) << (D - 1);
            for (int j = 0; j < dim; ++j) {
                if (X[i][j]) {
                    xy |= ull(1) << j;
                    ++(yi ? pos_xsum : neg_xsum)[j];
                }
            }
            Xy[i] = xy;
        }
        rec_fit(Xy, pos_xsum, neg_xsum, npos, nneg, dim);
    }

    template <class T> bool predict(const std::vector<T> &x) {
        int now = 0;
        while (!nodes.at(now).is_leaf) {
            now = x.at(nodes.at(now).split_by) ? nodes.at(now).ch1 : nodes.at(now).ch0;
        }
        return nodes.at(now).label;
    }
};
