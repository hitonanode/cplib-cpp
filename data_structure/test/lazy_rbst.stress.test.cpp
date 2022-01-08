#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../lazy_rbst.hpp"
#include "../../random/xorshift.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct S {
    long long lsum; // a[0] + 2 * a[1] + 3 * a[2] + ... + n * a[n - 1]
    long long rsum; // n * a[0] + (n - 1) * a[1] + ... + a[n - 1]
    long long sum;
    int sz;
};
S genS(long long x) { return S{x, x, x, 1}; }

S op(S l, S r) {
    return {l.lsum + r.lsum + l.sz * r.sum, l.rsum + r.rsum + r.sz * l.sum, l.sum + r.sum,
            l.sz + r.sz};
}
using F = std::pair<bool, long long>;
S reversal(S x) { return {x.rsum, x.lsum, x.sum, x.sz}; }
S mapping(F f, S x) {
    if (!f.first) return x;
    auto add = f.second * x.sz * (x.sz + 1) / 2;
    return {x.lsum + add, x.rsum + add, x.sum + f.second * x.sz, x.sz};
}
F composition(F fnew, F gold) {
    if (!fnew.first) return gold;
    if (!gold.first) return fnew;
    return {true, fnew.second + gold.second};
}
F id() { return {false, 0}; }

long long y;
bool g_binsearch(S x) { return x.lsum <= y; }

void test_lazy_rbst(int hi) {
    auto rndx = [&hi]() -> long long { return rand_int() % hi; };

    for (int t = 0; t < 1000; t++) {
        lazy_rbst<1100, S, op, F, reversal, mapping, composition, id> rbst;
        auto root = rbst.new_tree();
        vector<long long> simulate;

        auto get_lsum = [&](int l, int r) -> long long {
            long long ret = 0;
            for (int i = l; i < r; i++) ret += simulate[i] * (i - l + 1);
            return ret;
        };

        while (simulate.size() < 50) {
            long long x = rndx();
            simulate.push_back(x);
            rbst.insert(root, simulate.size() - 1, genS(x));
        }
        for (int t = 0; t < 1000; t++) {
            const int choice = rand_int() % 8;

            if (choice == 0) {
                // Insert
                int pos = rand_int() % (simulate.size() + 1);
                long long x = rndx();
                simulate.insert(simulate.begin() + pos, x);
                rbst.insert(root, pos, genS(x));
            } else if (choice == 1) {
                // Erase
                if (simulate.empty()) continue;
                int pos = rand_int() % simulate.size();
                simulate.erase(simulate.begin() + pos);
                rbst.erase(root, pos);
            } else if (choice == 2) {
                // Set
                if (simulate.empty()) continue;
                int pos = rand_int() % simulate.size();
                long long x = rndx();
                simulate[pos] = x;
                rbst.set(root, pos, genS(x));
            } else if (choice == 3) {
                // apply
                int l = rand_int() % (simulate.size() + 1), r = rand_int() % (simulate.size() + 1);
                if (l > r) swap(l, r);
                long long x = rndx();
                for (int i = l; i < r; i++) simulate[i] += x;
                rbst.apply(root, l, r, {true, x});
            } else if (choice == 4) {
                // prod
                if (simulate.empty()) continue;
                int l = rand_int() % simulate.size(), r = rand_int() % simulate.size();
                if (l > r) swap(l, r);
                r++;
                S prod = rbst.prod(root, l, r);
                long long lsum = 0, rsum = 0, sum = 0;
                int sz = 0;
                for (int i = l; i < r; i++) {
                    lsum += simulate[i] * (i - l + 1);
                    rsum += simulate[i] * (r - i);
                    sum += simulate[i];
                    sz++;
                }
                assert(prod.lsum == lsum and prod.rsum == rsum and prod.sum == sum and prod.sz == sz);
            } else if (choice == 5) {
                // max_right
                if (simulate.empty()) continue;
                int l = rand_int() % simulate.size(), r = rand_int() % (simulate.size() + 1);
                if (l > r) swap(l, r);
                // l から始めて答が r あたりになりそうなクエリを作る
                y = get_lsum(l, r);
                while (r < int(simulate.size()) and simulate[r] == 0) r++;
                auto p = rbst.split(root, l);
                assert(rbst.max_right(p.second, S{0, 0, 0, 0}, g_binsearch) == r - l);
                root = rbst.merge(p.first, p.second);
            } else if (choice == 6) {
                if (simulate.empty()) continue;
                // min_left
                int l = rand_int() % (simulate.size() + 1), r = rand_int() % simulate.size() + 1;
                if (l > r) swap(l, r);
                // r から始めて答が l あたりになりそうなクエリを作る
                y = get_lsum(l, r);
                while (y == 0 and l and simulate[l - 1] == 0) l--;
                auto p = rbst.split(root, r);
                assert(rbst.min_left(p.first, S{0, 0, 0, 0}, g_binsearch) == l);
                root = rbst.merge(p.first, p.second);
            } else if (choice == 7) {
                // reverse
                if (simulate.empty()) continue;
                int l = rand_int() % simulate.size(), r = rand_int() % simulate.size();
                if (l > r) swap(l, r);
                r++;
                reverse(simulate.begin() + l, simulate.begin() + r);
                rbst.reverse(root, l, r);
            } else {
                throw;
            }
        }
        vector<S> ret;
        rbst.dump(root, ret);
        for (int i = 0; i < int(simulate.size()); i++) assert(simulate[i] == ret[i].sum);
    }
}

int main() {
    test_lazy_rbst(2);
    test_lazy_rbst(3);
    test_lazy_rbst(10);
    cout << "Hello World\n";
}
