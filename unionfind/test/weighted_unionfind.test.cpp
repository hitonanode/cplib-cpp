#include <iostream>
#include "unionfind/weighted_unionfind.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp"
using namespace std;

int main()
{
    int N, Q, x, y, z;
    cin >> N >> Q;
    WeightedUnionFind<int> uf(N);
    for (int i = 0; i < Q; i++)
    {
        int c;
        cin >> c;
        if (c)
        {
            cin >> x >> y;
            if (uf.same(x, y))
            {
                cout << uf.diff(x, y) << endl;
            }
            else
            {
                cout << "?" << endl;
            }
        }
        else
        {
            cin >> x >> y >> z;
            uf.unite(x, y, z);
        }
    }
}
