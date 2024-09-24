---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"multithread/parallel_runner.hpp\"\n\n\n\n#include <chrono>\n\
    #include <concepts>\n#include <exception>\n#include <future>\n#include <iostream>\n\
    #include <mutex>\n#include <optional>\n#include <vector>\n\ntemplate <class T>\n\
    concept ISolver = requires(const T ct, T t) {\n    t = {};\n    { t.solve() }\
    \ -> std::same_as<typename T::Ret>;\n    { t.read_stdin() } -> std::same_as<void>;\n\
    \    { ct.dump_stdout(std::declval<typename T::Ret>()) } -> std::same_as<void>;\n\
    };\n\ntemplate <ISolver Solver> class ParallelRunner {\npublic:\n    int num_threads_;\n\
    \    std::vector<Solver> instances;\n    std::vector<std::optional<typename Solver::Ret>>\
    \ rets;\n\n    std::mutex mtx;\n\n    ParallelRunner(int num_threads = std::thread::hardware_concurrency())\n\
    \        : num_threads_(num_threads > 0 ? num_threads : 1) {\n        std::cerr\
    \ << \"num_threads: \" << num_threads_ << std::endl;\n    }\n\n    void read_all(int\
    \ num_testcases) {\n        instances.clear();\n        instances.reserve(num_testcases);\n\
    \        for (int i = 0; i < num_testcases; ++i) {\n            instances.emplace_back(Solver{});\n\
    \            instances.back().read_stdin();\n        }\n    }\n\n    void run_sequential()\
    \ {\n        rets.assign(instances.size(), std::nullopt);\n\n        for (int\
    \ index = 0; index < (int)instances.size(); ++index) {\n            run_single_(index);\n\
    \            if (rets.at(index).has_value()) {\n                mhc_stdout_(instances.at(index),\
    \ rets.at(index).value(), index);\n            }\n        }\n    }\n\n    void\
    \ run_parallel(int num_skip = 0) {\n        rets.assign(instances.size(), std::nullopt);\n\
    \n        const int num_inputs = instances.size();\n        std::vector<std::future<void>>\
    \ futures;\n\n        std::atomic<int> index(num_skip < 0 ? 0 : num_skip);\n \
    \       std::vector<bool> is_finished(num_inputs, false);\n        int num_written\
    \ = 0;\n\n        for (int i = 0; i < num_threads_; ++i) {\n            futures.push_back(std::async(std::launch::async,\
    \ [&]() {\n                while (true) {\n                    const int current_index\
    \ = index.fetch_add(1);\n                    if (current_index >= num_inputs)\
    \ break;\n\n                    run_single_(current_index);\n\n              \
    \      {\n                        std::unique_lock<std::mutex> lock(mtx);\n  \
    \                      is_finished.at(current_index) = true;\n               \
    \         while (num_written < num_inputs and is_finished.at(num_written)) {\n\
    \                            if (rets.at(num_written).has_value()) {\n       \
    \                         mhc_stdout_(instances.at(num_written),\n           \
    \                                 rets.at(num_written).value(), num_written);\n\
    \                            }\n                            ++num_written;\n \
    \                       }\n                    }\n                }\n        \
    \    }));\n        }\n\n        for (auto &f : futures) f.get();\n    }\n\n  \
    \  void run_single_(int current_index) {\n        {\n            std::unique_lock<std::mutex>\
    \ lock(mtx);\n            std::cerr << \"[#\" << current_index + 1 << \"] start\"\
    \ << std::endl;\n        }\n\n        auto start = std::chrono::steady_clock::now();\n\
    \n        try {\n            rets.at(current_index) = instances.at(current_index).solve();\n\
    \        } catch (const std::exception &e) {\n            std::unique_lock<std::mutex>\
    \ lock(mtx);\n            std::cerr << \"Error in Case #\" << current_index +\
    \ 1 << \": \" << e.what() << std::endl;\n            return;\n        } catch\
    \ (...) {\n            std::unique_lock<std::mutex> lock(mtx);\n            std::cerr\
    \ << \"Unknown error in Case #\" << current_index + 1 << std::endl;\n        \
    \    return;\n        }\n\n        auto end = std::chrono::steady_clock::now();\n\
    \        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end\
    \ - start).count();\n\n        {\n            std::unique_lock<std::mutex> lock(mtx);\n\
    \            std::cerr << \"[#\" << current_index + 1 << \"] end, \" << msec <<\
    \ \" ms\" << std::endl;\n        }\n    }\n\n    static void mhc_stdout_(const\
    \ Solver &result, const Solver::Ret &sol, int index) {\n        std::cout << \"\
    Case #\" << index + 1 << \": \";\n        result.dump_stdout(sol);\n        std::cout\
    \ << std::flush;\n    }\n};\n\n\n\n/* Usage:\nstruct Solver {\n    using Ret =\
    \ int;\n\n    void read_stdin() {\n        // read input using std::cin\n    }\n\
    \n    Ret solve() {\n        // solve the problem\n    }\n\n    void dump_stdout(const\
    \ Ret &ret) const {\n        // output the result using std::cout\n        //\
    \ std::cout << ret << std::endl;\n    }\n};\n\nint T;\ncin >> T;\n\nParallelRunner<Solver>\
    \ pm;\npm.read_all(T);\npm.run_parallel();\n*/\n"
  code: "#ifndef PARALLEL_RUNNER_HPP\n#define PARALLEL_RUNNER_HPP\n\n#include <chrono>\n\
    #include <concepts>\n#include <exception>\n#include <future>\n#include <iostream>\n\
    #include <mutex>\n#include <optional>\n#include <vector>\n\ntemplate <class T>\n\
    concept ISolver = requires(const T ct, T t) {\n    t = {};\n    { t.solve() }\
    \ -> std::same_as<typename T::Ret>;\n    { t.read_stdin() } -> std::same_as<void>;\n\
    \    { ct.dump_stdout(std::declval<typename T::Ret>()) } -> std::same_as<void>;\n\
    };\n\ntemplate <ISolver Solver> class ParallelRunner {\npublic:\n    int num_threads_;\n\
    \    std::vector<Solver> instances;\n    std::vector<std::optional<typename Solver::Ret>>\
    \ rets;\n\n    std::mutex mtx;\n\n    ParallelRunner(int num_threads = std::thread::hardware_concurrency())\n\
    \        : num_threads_(num_threads > 0 ? num_threads : 1) {\n        std::cerr\
    \ << \"num_threads: \" << num_threads_ << std::endl;\n    }\n\n    void read_all(int\
    \ num_testcases) {\n        instances.clear();\n        instances.reserve(num_testcases);\n\
    \        for (int i = 0; i < num_testcases; ++i) {\n            instances.emplace_back(Solver{});\n\
    \            instances.back().read_stdin();\n        }\n    }\n\n    void run_sequential()\
    \ {\n        rets.assign(instances.size(), std::nullopt);\n\n        for (int\
    \ index = 0; index < (int)instances.size(); ++index) {\n            run_single_(index);\n\
    \            if (rets.at(index).has_value()) {\n                mhc_stdout_(instances.at(index),\
    \ rets.at(index).value(), index);\n            }\n        }\n    }\n\n    void\
    \ run_parallel(int num_skip = 0) {\n        rets.assign(instances.size(), std::nullopt);\n\
    \n        const int num_inputs = instances.size();\n        std::vector<std::future<void>>\
    \ futures;\n\n        std::atomic<int> index(num_skip < 0 ? 0 : num_skip);\n \
    \       std::vector<bool> is_finished(num_inputs, false);\n        int num_written\
    \ = 0;\n\n        for (int i = 0; i < num_threads_; ++i) {\n            futures.push_back(std::async(std::launch::async,\
    \ [&]() {\n                while (true) {\n                    const int current_index\
    \ = index.fetch_add(1);\n                    if (current_index >= num_inputs)\
    \ break;\n\n                    run_single_(current_index);\n\n              \
    \      {\n                        std::unique_lock<std::mutex> lock(mtx);\n  \
    \                      is_finished.at(current_index) = true;\n               \
    \         while (num_written < num_inputs and is_finished.at(num_written)) {\n\
    \                            if (rets.at(num_written).has_value()) {\n       \
    \                         mhc_stdout_(instances.at(num_written),\n           \
    \                                 rets.at(num_written).value(), num_written);\n\
    \                            }\n                            ++num_written;\n \
    \                       }\n                    }\n                }\n        \
    \    }));\n        }\n\n        for (auto &f : futures) f.get();\n    }\n\n  \
    \  void run_single_(int current_index) {\n        {\n            std::unique_lock<std::mutex>\
    \ lock(mtx);\n            std::cerr << \"[#\" << current_index + 1 << \"] start\"\
    \ << std::endl;\n        }\n\n        auto start = std::chrono::steady_clock::now();\n\
    \n        try {\n            rets.at(current_index) = instances.at(current_index).solve();\n\
    \        } catch (const std::exception &e) {\n            std::unique_lock<std::mutex>\
    \ lock(mtx);\n            std::cerr << \"Error in Case #\" << current_index +\
    \ 1 << \": \" << e.what() << std::endl;\n            return;\n        } catch\
    \ (...) {\n            std::unique_lock<std::mutex> lock(mtx);\n            std::cerr\
    \ << \"Unknown error in Case #\" << current_index + 1 << std::endl;\n        \
    \    return;\n        }\n\n        auto end = std::chrono::steady_clock::now();\n\
    \        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end\
    \ - start).count();\n\n        {\n            std::unique_lock<std::mutex> lock(mtx);\n\
    \            std::cerr << \"[#\" << current_index + 1 << \"] end, \" << msec <<\
    \ \" ms\" << std::endl;\n        }\n    }\n\n    static void mhc_stdout_(const\
    \ Solver &result, const Solver::Ret &sol, int index) {\n        std::cout << \"\
    Case #\" << index + 1 << \": \";\n        result.dump_stdout(sol);\n        std::cout\
    \ << std::flush;\n    }\n};\n\n#endif // PARALLEL_RUNNER_HPP\n\n/* Usage:\nstruct\
    \ Solver {\n    using Ret = int;\n\n    void read_stdin() {\n        // read input\
    \ using std::cin\n    }\n\n    Ret solve() {\n        // solve the problem\n \
    \   }\n\n    void dump_stdout(const Ret &ret) const {\n        // output the result\
    \ using std::cout\n        // std::cout << ret << std::endl;\n    }\n};\n\nint\
    \ T;\ncin >> T;\n\nParallelRunner<Solver> pm;\npm.read_all(T);\npm.run_parallel();\n\
    */\n"
  dependsOn: []
  isVerificationFile: false
  path: multithread/parallel_runner.hpp
  requiredBy: []
  timestamp: '2024-09-25 00:21:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: multithread/parallel_runner.hpp
layout: document
title: "Parallel runner \uFF08\u8907\u6570\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\u306E\
  \u30DE\u30EB\u30C1\u30B9\u30EC\u30C3\u30C9\u4E26\u5217\u5B9F\u884C\uFF09"
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
