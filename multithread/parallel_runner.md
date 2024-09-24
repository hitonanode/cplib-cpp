---
title: Parallel runner （複数テストケースのマルチスレッド並列実行）
documentation_of: ./parallel_runner.hpp
---

ダウンロードしたテストケースに対してプログラムを手元で実行して結果を提出する形式の競技において，複数テストケースの並列処理を行うためのコード．

## 使用例

``` cpp
struct Solver {
    using Ret = int;

    void read_stdin() {
        // read input using std::cin
    }

    Ret solve() {
        // solve the problem
    }

    void dump_stdout(const Ret &ret) const {
        // output the result using std::cout
        // std::cout << ret << std::endl;
    }
};

int main() {
    int T;
    cin >> T;

    ParallelRunner<Solver> pm;
    pm.read_all(T);
    pm.run_parallel();
}
```
