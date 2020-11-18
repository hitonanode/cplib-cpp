#include <algorithm>
#include <numeric>
#include <vector>

// CUT begin
// Enumerate Partitions of number <= N （自然数の分割の列挙）
// - can be used for N less than ~50
// - Example:
//   - 1 => [[1,],]
//   - 2 => [[1,],[1,1,],[2,],]
//   - 3 => [[1,],[1,1,],[1,1,1,],[2,],[2,1,],[3,],]
struct {
    std::vector<std::vector<int>> ret;
    std::vector<int> now;
    int num;
    void _partition_dfs() {
        int rem = num - std::accumulate(now.begin(), now.end(), 0);
        if (!now.empty()) rem = std::min(rem, now.back());

        now.push_back(0);
        for (int j = 1; j <= rem; j++) {
            now.back() = j;
            ret.push_back(now);
            _partition_dfs();
        }
        now.pop_back();
    }

    std::vector<std::vector<int>> operator()(int N) {
        ret.clear();
        now.clear();
        num = N;
        _partition_dfs();
        return ret;
    }
} EnumeratePartitions;
