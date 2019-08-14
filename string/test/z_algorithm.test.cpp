#include <iostream>
#include <string>
#include <vector>
#include "string/z_algorithm.hpp"
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
using namespace std;

int main()
{
    string T, P;
    cin >> T >> P;
    vector<int> z = z_algorithm(P + "_" + T);
    int n = P.length();
    for (int i = n + 1; i < (int)z.size(); i++)
    {
        if (z[i] == n) printf("%d\n", i - n - 1);
    }
}