---
title: Symmetric traveling salesperson problem （Symmetric TSP, 対称巡回セールスマン問題）
documentation_of: ./symmetric_tsp.hpp
---

対称巡回セールスマン問題のヒューリスティック解法． 2-opt, 3-opt, double-bridge 近傍による近傍探索や，Held–Karp 下界を利用した距離行列の前処理が可能．

## 問題例

### [競技プログラミングの鉄則　演習問題集 A46 - Heuristic 1](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_at)

実際の利用例を示す（以下は処理時間が長すぎるためそのまま貼っても TLE となる）。

```cpp
int main() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) cin >> X.at(i) >> Y.at(i);

    vector dmat(N, vector<long long>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) dmat.at(i).at(j) = roundl(hypot(X.at(i) - X.at(j), Y.at(i) - Y.at(j)) * 1000000LL);
    }

    dense_distance_matrix<long long> distance_matrix(dmat);

    // LKH で採用されている手法．
    // Held–Karp 下界を求める際の双対変数をもとに距離行列を変形し，
    // より短い辺を最適解に含まれやすくする．
    auto [w, pi] = held_karp_lower_bound(distance_matrix);
    distance_matrix.apply_pi(pi);

    auto adjacent_dmat = build_adjacent_info(distance_matrix, 20);

    SymmetricTSP tsp(distance_matrix, adjacent_dmat);

    decltype(tsp)::Solution best{1LL << 60, {}};

    auto sol = tsp.nearest_neighbor(0);
    mt19937 mt(100);

    for (int start = 0; start < N; ++start) {
        // 初期解の構築
        sol = tsp.nearest_neighbor(start);

        for (int _ = 0; _ < 30; ++_) {
            do {
                // two_opt() は改善可能性がなくなるまで 2-opt を行う
                tsp.two_opt(sol);
            } while (tsp.three_opt(sol));  // three_opt() は一度 3-opt による改善に成功した時点で return する

            if (sol.cost < best.cost) best = sol;
            tsp.double_bridge(sol, mt); // double-bridge 近傍の適用
        }
    }

    rotate(best.path.begin(), find(best.path.begin(), best.path.end(), 0), best.path.end());

    for (int x : best.path) cout << x + 1 << '\n';
    cout << best.path.front() + 1 << '\n';
}
```

なお、 [公開されているテストケース](https://www.dropbox.com/sh/nx3tnilzqz7df8a/AACmMZ47dbcz373G0KzuFRwCa/tessoku-book/A46?dl=0&subfolder_nav_tracking=1) に対して [Concorde](https://www.math.uwaterloo.ca/tsp/concorde.html) を適用して得られた厳密解は以下の通りで、5317 点が現状のテストケースで獲得可能な最高点と思われる．

| testcase | concorde | score |
| -------- | -------- | ----- |
| in01.txt | 9625.526 | 103   |
| in02.txt | 9385.646 | 106   |
| in03.txt | 9002.222 | 111   |
| in04.txt | 9489.165 | 105   |
| in05.txt | 9649.202 | 103   |
| in06.txt | 9177.047 | 108   |
| in07.txt | 9226.318 | 108   |
| in08.txt | 9353.698 | 106   |
| in09.txt | 9259.692 | 107   |
| in10.txt | 9216.752 | 108   |
| in11.txt | 9429.295 | 106   |
| in12.txt | 9290.442 | 107   |
| in13.txt | 9226.807 | 108   |
| in14.txt | 9104.148 | 109   |
| in15.txt | 9488.633 | 105   |
| in16.txt | 9138.817 | 109   |
| in17.txt | 9161.750 | 109   |
| in18.txt | 9353.783 | 106   |
| in19.txt | 9694.808 | 103   |
| in20.txt | 9455.553 | 105   |
| in21.txt | 9537.144 | 104   |
| in22.txt | 9132.504 | 109   |
| in23.txt | 9370.653 | 106   |
| in24.txt | 9264.462 | 107   |
| in25.txt | 9271.141 | 107   |
| in26.txt | 9670.472 | 103   |
| in27.txt | 9610.274 | 104   |
| in28.txt | 8948.458 | 111   |
| in29.txt | 9238.179 | 108   |
| in30.txt | 9348.935 | 106   |
| in31.txt | 9091.568 | 109   |
| in32.txt | 9279.178 | 107   |
| in33.txt | 9389.572 | 106   |
| in34.txt | 9421.150 | 106   |
| in35.txt | 9246.909 | 108   |
| in36.txt | 9420.217 | 106   |
| in37.txt | 9588.017 | 104   |
| in38.txt | 9467.334 | 105   |
| in39.txt | 9741.184 | 102   |
| in40.txt | 9607.822 | 104   |
| in41.txt | 9063.515 | 110   |
| in42.txt | 9450.781 | 105   |
| in43.txt | 9247.381 | 108   |
| in44.txt | 9434.954 | 105   |
| in45.txt | 9739.259 | 102   |
| in46.txt | 9232.337 | 108   |
| in47.txt | 9168.033 | 109   |
| in48.txt | 9509.942 | 105   |
| in49.txt | 9614.630 | 104   |
| in50.txt | 9315.151 | 107   |
| sum      |          | 5317  |

### [第3回 RCO日本橋ハーフマラソン 予選 A - ツーリストXの旅行計画](https://atcoder.jp/contests/rco-contest-2019-qual/tasks/rco_contest_2019_qual_a)

「移動距離の平均をパラメータと思って 3-opt + double bridge で TSP を解く」操作と「得られた TSP の解から移動距離の平均を再計算する」操作を繰り返すことで [本番一位を上回るスコアになる](https://atcoder.jp/contests/rco-contest-2019-qual/submissions/38915876)。

## 参考文献・リンク

- [K. Helsgaun, "An Effective Implementation of the Lin-Kernighan Traveling Salesman Heuristic," DATALOGISKE SKRIFTER (Writings on Computer Science), No. 81, 1998, Roskilde University.](http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf)
- 柳浦 睦憲, 茨木 俊秀, "組合せ最適化―メタ戦略を中心として (経営科学のニューフロンティア)," 2001, 朝倉書店．
- [2022年度 第1回ORセミナー 2022年6月1日 – 公益社団法人 日本オペレーションズ・リサーチ学会](https://orsj.org/?p=4182)
