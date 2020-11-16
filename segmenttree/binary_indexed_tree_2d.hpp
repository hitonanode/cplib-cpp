#pragma once
#include <array>

// CUT begin
// 2-dimentional 1-indexed BIT (i : [1, lenX][1, lenY])
template <typename T, int lenX, int lenY>
struct BIT_2D
{
    std::array<T, (lenX + 1) * (lenY + 1)> val;
    constexpr static int M = lenY + 1;
    BIT_2D() {}
    void add(int posx, int posy, T v) noexcept {
        for (int x = posx; x <= lenX; x += x & -x) {
            for (int y = posy; y <= lenY; y += y & -y) val[x * M + y] += v;
        }
    }
    // [1, posx] * [1, posy] の和
    T sum(int posx, int posy) const noexcept {
        T res = 0;
        for (int x = posx; x > 0; x -= x & -x) {
            for (int y = posy; y > 0; y -= y & -y) {
                res += val[x * M + y];
            }
        }
        return res;
    }
    // [xmin, xmax] * [ymin, ymax] の和（閉区間）
    T sum(int xmin, int xmax, int ymin, int ymax) const noexcept {
        return sum(xmax, ymax) - sum(xmin - 1, ymax) - sum(xmax, ymin - 1) + sum(xmin - 1, ymin - 1);
    }
};
