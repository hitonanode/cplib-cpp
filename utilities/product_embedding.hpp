#pragma once
#include <cassert>
#include <fstream>
#include <vector>

// 結合法則が成立する要素の列について連続部分列の積を前計算を利用し高速に求める
template <class S, S (*op)(S, S), S (*e)(), S (*getter)(long long), int Bucket>
struct product_embedding {
    std::vector<S> pre_; // pre_[i] = S[i * Bucket] * ... * S[(i + 1) * Bucket - 1]

    product_embedding(std::vector<S> pre) : pre_(pre) {}

    S prod(long long l, long long r) { // S[l] * ... * S[r - 1]
        assert(0 <= l);
        assert(l <= r);
        assert(r <= (long long)Bucket * (long long)pre_.size());

        if (r - l <= Bucket) {
            S ret = e();
            while (l < r) ret = op(ret, getter(l++));
            return ret;
        }

        long long lb = (l + Bucket - 1) / Bucket, rb = r / Bucket;
        S ret = e();
        for (long long i = l; i < lb * Bucket; ++i) ret = op(ret, getter(i));
        for (int i = lb; i < rb; ++i) ret = op(ret, pre_[i]);
        for (long long i = rb * Bucket; i < r; ++i) ret = op(ret, getter(i));
        return ret;
    }

    static void prerun(std::string filename, long long upper_lim) {
        std::ofstream ofs(filename);

        long long cur = 0;
        long long num_bucket = (upper_lim + Bucket - 1) / Bucket;

        ofs << "({";
        while (num_bucket--) {
            S p = e();
            for (int t = 0; t < Bucket; ++t) { p = op(p, getter(cur++)); }
            ofs << p;
            if (num_bucket) ofs << ",";
        }
        ofs << "});";
    }
};
/* Usage:
using S = int;
constexpr S md = 1000000007;
S op(S l, S r) { return (long long)l * r % md; }
S e() { return 1; }
S getter(long long i) { return i + 1 >= md ? (i + 1) % md : i + 1; }
using PE = product_embedding<S, op, e, getter, 500000>;

int main() {
    PE::prerun("tmp.txt", md);  // -> copy & paste the content of dumped file
}
*/
