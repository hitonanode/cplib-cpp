#include <vector>

// CUT begin
template <typename T>
std::vector<std::vector<T>> trans(std::vector<std::vector<T>> v)
{
    int H = v.size(), W = v[0].size();
    std::vector<std::vector<T>> ret(W, std::vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ret[j][i] = v[i][j];
        }
    }
    return ret;
}
