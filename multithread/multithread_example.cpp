// マルチスレッドでローカル実行高速化 コンパイル時のオプションに -pthread が必要
#include <bits/stdc++.h>
using namespace std;
using pint = pair<int, int>;
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define dbg(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ") " << __FILE__ << endl;

struct SingleCaseInput
{
    int N, M;
    vector<pint> query;
    SingleCaseInput(int n, int m, const vector<pint> &q) : N(n), M(m), query(q) {}
};
vector<SingleCaseInput> testcase;


vector<string> ret;

/* 各テストケースの完了状況を保持 */
mutex mtx;
vector<int> done;

void solve(int tc)
{
    /* tc個目のテストケースを処理する関数 */
}

void run()
{
    /* 未完了で最も番号が若いテストケースを処理 */
    int i = 0;
    while (true)
    {
        mtx.lock();
        while (i < done.size() and done[i]) i++;
        if (i < done.size()) done[i] = 1;
        mtx.unlock();
        if (i >= done.size()) break;
        solve(i);
    }
}

int main()
{
    auto START = chrono::system_clock::now();
    cin.tie(0);
    ios::sync_with_stdio(false);

    int TC;
    cin >> TC;
    REP(tc, TC)
    {
        int N, M;
        cin >> N >> M;
        vector<pint> q(M);
        REP(i, M) cin >> q[i].first >> q[i].second;
        testcase.emplace_back(N, M, q);
    }
    ret.resize(TC);
    done.assign(TC, 0);

    size_t n_thread = thread::hardware_concurrency(); // スレッド数を自動取得． 8や16と手で設定してもよい
    if (n_thread == 0) n_thread = 1;

    vector<thread> threads(n_thread);
    REP(i, n_thread)
    {
        threads[i] = thread(run);
    }
    REP(i, n_thread)
    {
        threads[i].join();
    }
    REP(tc, TC)
    {
        cout << "Case #" << tc + 1 << ": " << ret[tc] << endl;
    }
    dbg(chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - START).count());
}
