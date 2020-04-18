#pragma once
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Fully persistent queue
template<typename T, int D>
struct pqueue
{
    int now;

    std::vector<T> data;               // Elements on each node of tree
    std::vector<std::vector<int>> par; // binary-lifted parents

    std::vector<int> back_id; // back_id[t] = leaf id of the tree at time t
    std::vector<int> size;    // size[t] = size of the queue at time t

    pqueue() : now(0), data(1), par(1, std::vector<int>(D)), back_id(1, 0), size(1, 0) {}

    // Complexity: O(lgD)
    // return: (curret_time, popped element)
    std::pair<int, T> pop(int t)
    {
        now++;
        assert(now < 1 << (D + 1));
        int r = back_id[t], len = size[t] - 1;
        back_id.emplace_back(r), size.emplace_back(len);
        for (int d = 0; d < D; d++) if ((len >> d) & 1) r = par[r][d];
        return std::make_pair(now, data[r]);
    }

    // Complexity: O(lgD)
    // return: curret_time
    int push(int t, const T &dat)
    {
        now++;
        assert(now < 1 << (D + 1));
        int newid = data.size();
        data.emplace_back(dat);
        par.emplace_back(std::vector<int>(D, back_id[t]));
        back_id.emplace_back(newid), size.emplace_back(size[t] + 1);
        for (int d = 1; d < D; d++) par[newid][d] = par[par[newid][d - 1]][d - 1];
        return now;
    }
};
