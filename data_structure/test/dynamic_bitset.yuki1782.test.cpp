#define PROBLEM "https://yukicoder.me/problems/no/1782"
#include "../dynamic_bitset.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    long long L;
    cin >> N >> L;
    vector<int> W(N);
    for (auto &x : W) cin >> x;
    sort(W.begin(), W.end());
    dynamic_bitset bs(W.back() + 1);
    long long ret = -1;
    vector<int> newcomer{0};
    int non = 0;
    const int rec = W.back();
    for (long long lo = 0; lo <= L; lo += rec) {
        vector<int> next_comer;
        while (!newcomer.empty()) {
            int x = newcomer.back();
            newcomer.pop_back();
            if (bs.test(x)) continue;
            bs.set(x);
            ++non;
            for (auto w : W) {
                if (x + w >= rec) {
                    int d = x + w - rec;
                    if (!bs.test(d)) next_comer.push_back(d);
                } else if (!bs.test(x + w)) {
                    newcomer.push_back(x + w);
                }
            }
        }
        newcomer = next_comer;
        if (next_comer.empty()) {
            long long dx = max(0LL, (L - lo) / rec - 10);
            lo += dx * rec;
            ret += dx * non;
        }
        ret += non;
        if (lo + rec > L) {
            for (int i = 0; i < rec; ++i) {
                if (lo + i > L) ret -= bs.test(i);
            }
            break;
        }
    }
    cout << ret << '\n';
}
