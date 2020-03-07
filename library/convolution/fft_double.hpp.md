---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: convolution/fft_double.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a9595c1c24c33b16056d2ad07e71682d">convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/convolution/fft_double.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <complex>
#include <utility>
#include <vector>

// CUT begin
// Convolution by FFT (Fast Fourier Transform)
// Algorithm based on <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
// Verified: ATC001C (168 ms) <https://atcoder.jp/contests/atc001/submissions/9243440>
using cmplx = std::complex<double>;
void fft(int N, std::vector<cmplx> &a, double dir)
{
    int i = 0;
    for (int j = 1; j < N - 1; j++) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1);
        if (j < i) std::swap(a[i], a[j]);
    }

    std::vector<cmplx> zeta_pow(N);
    for (int i = 0; i < N; i++) {
        double theta = M_PI / N * i * dir;
        zeta_pow[i] = {cos(theta), sin(theta)};
    }

    for (int m = 1; m < N; m *= 2) {
        for (int y = 0; y < m; y++) {
            cmplx fac = zeta_pow[N / m * y];
            for (int x = 0; x < N; x += 2 * m) {
                int u = x + y;
                int v = x + y + m;
                cmplx s = a[u] + fac * a[v];
                cmplx t = a[u] - fac * a[v];
                a[u] = s;
                a[v] = t;
            }
        }
    }
}
template<typename T>
std::vector<cmplx> conv_cmplx(const std::vector<T> &a, const std::vector<T> &b)
{
    int N = 1;
    while (N < (int)a.size() + (int)b.size()) N *= 2;
    std::vector<cmplx> a_(N), b_(N);
    for (int i = 0; i < (int)a.size(); i++) a_[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) b_[i] = b[i];
    fft(N, a_, 1);
    fft(N, b_, 1);
    for (int i = 0; i < N; i++) a_[i] *= b_[i];
    fft(N, a_, -1);
    for (int i = 0; i < N; i++) a_[i] /= N;
    return a_;
}
// retval[i] = \sum_j a[j]b[i - j]
// Requirement: length * max(a) * max(b) < 10^15
template<typename T>
std::vector<long long int> fftconv(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<cmplx> ans = conv_cmplx(a, b);
    std::vector<long long int> ret(ans.size());
    for (int i = 0; i < (int)ans.size(); i++) ret[i] = floor(ans[i].real() + 0.5);
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "convolution/fft_double.hpp"
#include <complex>
#include <utility>
#include <vector>

// CUT begin
// Convolution by FFT (Fast Fourier Transform)
// Algorithm based on <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
// Verified: ATC001C (168 ms) <https://atcoder.jp/contests/atc001/submissions/9243440>
using cmplx = std::complex<double>;
void fft(int N, std::vector<cmplx> &a, double dir)
{
    int i = 0;
    for (int j = 1; j < N - 1; j++) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1);
        if (j < i) std::swap(a[i], a[j]);
    }

    std::vector<cmplx> zeta_pow(N);
    for (int i = 0; i < N; i++) {
        double theta = M_PI / N * i * dir;
        zeta_pow[i] = {cos(theta), sin(theta)};
    }

    for (int m = 1; m < N; m *= 2) {
        for (int y = 0; y < m; y++) {
            cmplx fac = zeta_pow[N / m * y];
            for (int x = 0; x < N; x += 2 * m) {
                int u = x + y;
                int v = x + y + m;
                cmplx s = a[u] + fac * a[v];
                cmplx t = a[u] - fac * a[v];
                a[u] = s;
                a[v] = t;
            }
        }
    }
}
template<typename T>
std::vector<cmplx> conv_cmplx(const std::vector<T> &a, const std::vector<T> &b)
{
    int N = 1;
    while (N < (int)a.size() + (int)b.size()) N *= 2;
    std::vector<cmplx> a_(N), b_(N);
    for (int i = 0; i < (int)a.size(); i++) a_[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) b_[i] = b[i];
    fft(N, a_, 1);
    fft(N, b_, 1);
    for (int i = 0; i < N; i++) a_[i] *= b_[i];
    fft(N, a_, -1);
    for (int i = 0; i < N; i++) a_[i] /= N;
    return a_;
}
// retval[i] = \sum_j a[j]b[i - j]
// Requirement: length * max(a) * max(b) < 10^15
template<typename T>
std::vector<long long int> fftconv(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<cmplx> ans = conv_cmplx(a, b);
    std::vector<long long int> ret(ans.size());
    for (int i = 0; i < (int)ans.size(); i++) ret[i] = floor(ans[i].real() + 0.5);
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

