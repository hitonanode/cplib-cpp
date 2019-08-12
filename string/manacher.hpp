#include <string>
#include <vector>


std::vector<int> manacher(std::string S)
{
    std::vector<int> res(S.size());
    int i = 0, j = 0;
    while (i < (int)S.size())
    {
        while (i - j >= 0 and i + j < (int)S.size() and S[i - j] == S[i + j]) j++;
        res[i] = j;
        int k = 1;
        while (i - k >= 0 and i + k < (int)S.size() and k + res[i - k] < j) res[i + k] = res[i - k], k++;
        i += k, j -= k;
    }
    return res;
}
