#pragma once
#include <vector>

struct BinaryTrie
{
    using Int = int;
    int maxD;
    std::vector<int> deg, sz;
    std::vector<int> ch0, ch1, par;

    int _new_node(int id_par)
    {
        deg.emplace_back(0);
        sz.emplace_back(0);
        ch0.emplace_back(-1);
        ch1.emplace_back(-1);
        par.emplace_back(id_par);
        return ch0.size() - 1;
    }

    BinaryTrie(int maxD = 0) : maxD(maxD)
    {
        _new_node(-1);
    }
    int _goto(Int x)
    {
        int now = 0;
        for (int d = maxD - 1; d >= 0; d--)
        {
            int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (nxt == -1)
            {
                nxt = _new_node(now);
                (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;
            }
            now = nxt;
        }
        return now;
    }

    void insert(Int x)
    {
        int now = _goto(x);
        if (deg[now] == 0)
        {
            deg[now] = 1;
            while (now >= 0)
            {
                sz[now]++, now = par[now];
            }
        }
    }

    void erase(Int x)
    {
        int now = _goto(x);
        if (deg[now] > 0)
        {
            deg[now] = 0;
            while (now >= 0)
            {
                sz[now]--, now = par[now];
            }
        }
    }

    Int xor_min(Int x)
    {
        Int ret = 0;
        int now = 0;
        if (!sz[now]) return -1;
        for (int d = maxD - 1; d >= 0; d--)
        {
            int y = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (y != -1 and sz[y])
            {
                now = y;
            }
            else
            {
                ret += Int(1) << d, now = ch0[now] ^ ch1[now] ^ y;
            }
        }
        return ret;
    }
};
