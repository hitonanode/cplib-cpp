#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template <>
struct std::numeric_limits<__int128>
{
    static __int128 max() noexcept { return ((__int128(1) << 126) - 1) * 2 + 1; }
    static __int128 min() noexcept { return -max() - 1; }
    static __int128 lowest() noexcept { return min(); }
};
__int128 str2i128(std::string str)
{
    __int128 ret = 0;
    bool minus = false;
    for (auto c : str)
    {
        if (c == '-') minus = true;
        else ret = ret * 10 + c - '0';
    }
    return minus ? -ret : ret;
}
std::istream &operator>>(std::istream &is, __int128 &x)
{
    std::string s;
    is >> s;
    x = str2i128(s);
    return is;
}
std::ostream &operator<<(std::ostream &os, const __int128& x)
{
    __int128 tmp = x;
    if (tmp == 0) return os << 0;
    std::vector<int> ds;
    if (tmp < 0)
    {
        os << '-';
        while (tmp)
        {
            int d = tmp % 10;
            if (d > 0) d -= 10;
            ds.emplace_back(-d), tmp = (tmp - d) / 10;
        }
    }
    else
    {
        while (tmp) ds.emplace_back(tmp % 10), tmp /= 10;
    }
    std::reverse(ds.begin(), ds.end());
    for (auto i : ds) os << i;
    return os;
}
