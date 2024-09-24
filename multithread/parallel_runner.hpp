#ifndef PARALLEL_RUNNER_HPP
#define PARALLEL_RUNNER_HPP

#include <chrono>
#include <concepts>
#include <exception>
#include <future>
#include <iostream>
#include <mutex>
#include <optional>
#include <vector>

template <class T>
concept ISolver = requires(const T ct, T t) {
    t = {};
    { t.solve() } -> std::same_as<typename T::Ret>;
    { t.read_stdin() } -> std::same_as<void>;
    { ct.dump_stdout(std::declval<typename T::Ret>()) } -> std::same_as<void>;
};

template <ISolver Solver> class ParallelRunner {
public:
    int num_threads_;
    std::vector<Solver> instances;
    std::vector<std::optional<typename Solver::Ret>> rets;

    std::mutex mtx;

    ParallelRunner(int num_threads = std::thread::hardware_concurrency())
        : num_threads_(num_threads > 0 ? num_threads : 1) {
        std::cerr << "num_threads: " << num_threads_ << std::endl;
    }

    void read_all(int num_testcases) {
        instances.clear();
        instances.reserve(num_testcases);
        for (int i = 0; i < num_testcases; ++i) {
            instances.emplace_back(Solver{});
            instances.back().read_stdin();
        }
    }

    void run_sequential() {
        rets.assign(instances.size(), std::nullopt);

        for (int index = 0; index < (int)instances.size(); ++index) {
            run_single_(index);
            if (rets.at(index).has_value()) {
                mhc_stdout_(instances.at(index), rets.at(index).value(), index);
            }
        }
    }

    void run_parallel(int num_skip = 0) {
        rets.assign(instances.size(), std::nullopt);

        const int num_inputs = instances.size();
        std::vector<std::future<void>> futures;

        std::atomic<int> index(num_skip < 0 ? 0 : num_skip);
        std::vector<bool> is_finished(num_inputs, false);
        int num_written = 0;

        for (int i = 0; i < num_threads_; ++i) {
            futures.push_back(std::async(std::launch::async, [&]() {
                while (true) {
                    const int current_index = index.fetch_add(1);
                    if (current_index >= num_inputs) break;

                    run_single_(current_index);

                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        is_finished.at(current_index) = true;
                        while (num_written < num_inputs and is_finished.at(num_written)) {
                            if (rets.at(num_written).has_value()) {
                                mhc_stdout_(instances.at(num_written),
                                            rets.at(num_written).value(), num_written);
                            }
                            ++num_written;
                        }
                    }
                }
            }));
        }

        for (auto &f : futures) f.get();
    }

    void run_single_(int current_index) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            std::cerr << "[#" << current_index + 1 << "] start" << std::endl;
        }

        auto start = std::chrono::steady_clock::now();

        try {
            rets.at(current_index) = instances.at(current_index).solve();
        } catch (const std::exception &e) {
            std::unique_lock<std::mutex> lock(mtx);
            std::cerr << "Error in Case #" << current_index + 1 << ": " << e.what() << std::endl;
            return;
        } catch (...) {
            std::unique_lock<std::mutex> lock(mtx);
            std::cerr << "Unknown error in Case #" << current_index + 1 << std::endl;
            return;
        }

        auto end = std::chrono::steady_clock::now();
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        {
            std::unique_lock<std::mutex> lock(mtx);
            std::cerr << "[#" << current_index + 1 << "] end, " << msec << " ms" << std::endl;
        }
    }

    static void mhc_stdout_(const Solver &result, const Solver::Ret &sol, int index) {
        std::cout << "Case #" << index + 1 << ": ";
        result.dump_stdout(sol);
        std::cout << std::flush;
    }
};

#endif // PARALLEL_RUNNER_HPP

/* Usage:
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

int T;
cin >> T;

ParallelRunner<Solver> pm;
pm.read_all(T);
pm.run_parallel();
*/
