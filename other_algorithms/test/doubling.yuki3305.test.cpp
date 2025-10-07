#define PROBLEM "https://yukicoder.me/problems/no/3305"
#include "../doubling.hpp"

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> nexts(N, N);

    vector<pair<int, int>> st;
    st.emplace_back(N, N);
    for (int i = N - 1; i >= 0; --i) {
        while (st.back().first < A.at(i)) st.pop_back();
        nexts.at(i) = st.back().second;
        st.emplace_back(A.at(i), i);
    }

    const BinaryLifting binary_lifting(nexts);

    while (Q--) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << r - l - binary_lifting.distance(l, r) << '\n';
    }
}
