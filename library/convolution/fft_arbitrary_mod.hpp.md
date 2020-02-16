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


# :warning: convolution/fft_arbitrary_mod.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a9595c1c24c33b16056d2ad07e71682d">convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/convolution/fft_arbitrary_mod.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-13 15:48:40+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <cmath>
#include <vector>
using namespace std;

// Arbitrary mod (<1e9) FFT/convolution
// MAXA*MAXB*N <= 1e15 (double), 1e19 (long double)
// Based on <https://ei1333.github.io/luzhiled/snippets/math/arbitrary-mod-convolution.html>
using T_FFT = long double;
constexpr int D_FFT = 15;
struct cmplx{
    T_FFT x, y;
    cmplx() : x(0), y(0) {}
    cmplx(T_FFT x, T_FFT y) : x(x), y(y) {}
    inline cmplx operator+(const cmplx &r) const { return cmplx(x + r.x, y + r.y); }
    inline cmplx operator-(const cmplx &r) const { return cmplx(x - r.x, y - r.y); }
    inline cmplx operator*(const cmplx &r) const { return cmplx(x * r.x - y * r.y, x * r.y + y * r.x); }
    inline cmplx conj() const { return cmplx(x, -y); }
};
int fftbase = 1;
vector<cmplx> fftrts = {{0, 0}, {1, 0}};
vector<int> fftrev = {0, 1};
void ensure_base(int nbase) {
    if (nbase <= fftbase) return;
    fftrev.resize(1 << nbase);
    fftrts.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
        fftrev[i] = (fftrev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    while (fftbase < nbase) {
        T_FFT angle = acosl(-1.0L) * 2.0L / (1 << (fftbase + 1));
        for (int i = 1 << (fftbase - 1); i < (1 << fftbase); i++) {
            fftrts[i << 1] = fftrts[i];
            T_FFT angle_i = angle * (2 * i + 1 - (1 << fftbase));
            fftrts[(i << 1) + 1] = {cos(angle_i), sin(angle_i)};
        }
        ++fftbase;
    }
}
void fft(int n, vector<cmplx> &a) {
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = fftbase - zeros;
    for (int i = 0; i < n; i++) {
        if (i < (fftrev[i] >> shift)) {
            swap(a[i], a[fftrev[i] >> shift]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                cmplx z = a[i + j + k] * fftrts[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}


// Convolution for ModInt class
// retval[i] = \sum_j a[j] b[i - j]
template <typename MODINT>
vector<MODINT> convolution_mod(vector<MODINT> a, vector<MODINT> b)
{
    int need = int(a.size() + b.size()) - 1;
    int nbase = 0;
    while ((1 << nbase) < need) nbase++;
    int sz = 1 << nbase;
    vector<cmplx> fa(sz);
    for (int i = 0; i < (int)a.size(); i++) fa[i] = {(T_FFT)(a[i].val & ((1LL << D_FFT) - 1)), (T_FFT)(a[i].val >> D_FFT)};
    fft(sz, fa);
    vector<cmplx> fb(sz);
    if (a == b) fb = fa;
    else {
        for (int i = 0; i < (int)b.size(); i++) fb[i] = {(T_FFT)(b[i].val & ((1LL << D_FFT) - 1)), (T_FFT)(b[i].val >> D_FFT)};
        fft(sz, fb);
    }
    T_FFT ratio = 0.25L / sz;
    cmplx r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        cmplx a1 = (fa[i] + fa[j].conj());
        cmplx a2 = (fa[i] - fa[j].conj()) * r2;
        cmplx b1 = (fb[i] + fb[j].conj()) * r3;
        cmplx b2 = (fb[i] - fb[j].conj()) * r4;
        if (i != j) {
            cmplx c1 = (fa[j] + fa[i].conj());
            cmplx c2 = (fa[j] - fa[i].conj()) * r2;
            cmplx d1 = (fb[j] + fb[i].conj()) * r3;
            cmplx d2 = (fb[j] - fb[i].conj()) * r4;
            fa[i] = c1 * d1 + c2 * d2 * r5;
            fb[i] = c1 * d2 + c2 * d1;
        }
        fa[j] = a1 * b1 + a2 * b2 * r5;
        fb[j] = a1 * b2 + a2 * b1;
    }
    fft(sz, fa);
    fft(sz, fb);
    vector<MODINT> ret(sz);
    long long int bp = MODINT(2).power(D_FFT);
    long long int cp = MODINT(2).power(D_FFT * 2);
    for (int i = 0; i < need; i++) {
        long long int aa = llround(fa[i].x);
        long long int bb = llround(fb[i].x);
        long long int cc = llround(fa[i].y);
        aa = MODINT(aa).val, bb = MODINT(bb).val, cc = MODINT(cc).val;
        ret[i] = aa + (bb * bp) + (cc * cp);
        //   ret[i] = aa + (bb << DFFT) + (cc << (DFFT * 2));
    }
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "convolution/fft_arbitrary_mod.hpp"
#include <cassert>
#include <cmath>
#include <vector>
using namespace std;

// Arbitrary mod (<1e9) FFT/convolution
// MAXA*MAXB*N <= 1e15 (double), 1e19 (long double)
// Based on <https://ei1333.github.io/luzhiled/snippets/math/arbitrary-mod-convolution.html>
using T_FFT = long double;
constexpr int D_FFT = 15;
struct cmplx{
    T_FFT x, y;
    cmplx() : x(0), y(0) {}
    cmplx(T_FFT x, T_FFT y) : x(x), y(y) {}
    inline cmplx operator+(const cmplx &r) const { return cmplx(x + r.x, y + r.y); }
    inline cmplx operator-(const cmplx &r) const { return cmplx(x - r.x, y - r.y); }
    inline cmplx operator*(const cmplx &r) const { return cmplx(x * r.x - y * r.y, x * r.y + y * r.x); }
    inline cmplx conj() const { return cmplx(x, -y); }
};
int fftbase = 1;
vector<cmplx> fftrts = {{0, 0}, {1, 0}};
vector<int> fftrev = {0, 1};
void ensure_base(int nbase) {
    if (nbase <= fftbase) return;
    fftrev.resize(1 << nbase);
    fftrts.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
        fftrev[i] = (fftrev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    while (fftbase < nbase) {
        T_FFT angle = acosl(-1.0L) * 2.0L / (1 << (fftbase + 1));
        for (int i = 1 << (fftbase - 1); i < (1 << fftbase); i++) {
            fftrts[i << 1] = fftrts[i];
            T_FFT angle_i = angle * (2 * i + 1 - (1 << fftbase));
            fftrts[(i << 1) + 1] = {cos(angle_i), sin(angle_i)};
        }
        ++fftbase;
    }
}
void fft(int n, vector<cmplx> &a) {
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = fftbase - zeros;
    for (int i = 0; i < n; i++) {
        if (i < (fftrev[i] >> shift)) {
            swap(a[i], a[fftrev[i] >> shift]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                cmplx z = a[i + j + k] * fftrts[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}


// Convolution for ModInt class
// retval[i] = \sum_j a[j] b[i - j]
template <typename MODINT>
vector<MODINT> convolution_mod(vector<MODINT> a, vector<MODINT> b)
{
    int need = int(a.size() + b.size()) - 1;
    int nbase = 0;
    while ((1 << nbase) < need) nbase++;
    int sz = 1 << nbase;
    vector<cmplx> fa(sz);
    for (int i = 0; i < (int)a.size(); i++) fa[i] = {(T_FFT)(a[i].val & ((1LL << D_FFT) - 1)), (T_FFT)(a[i].val >> D_FFT)};
    fft(sz, fa);
    vector<cmplx> fb(sz);
    if (a == b) fb = fa;
    else {
        for (int i = 0; i < (int)b.size(); i++) fb[i] = {(T_FFT)(b[i].val & ((1LL << D_FFT) - 1)), (T_FFT)(b[i].val >> D_FFT)};
        fft(sz, fb);
    }
    T_FFT ratio = 0.25L / sz;
    cmplx r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        cmplx a1 = (fa[i] + fa[j].conj());
        cmplx a2 = (fa[i] - fa[j].conj()) * r2;
        cmplx b1 = (fb[i] + fb[j].conj()) * r3;
        cmplx b2 = (fb[i] - fb[j].conj()) * r4;
        if (i != j) {
            cmplx c1 = (fa[j] + fa[i].conj());
            cmplx c2 = (fa[j] - fa[i].conj()) * r2;
            cmplx d1 = (fb[j] + fb[i].conj()) * r3;
            cmplx d2 = (fb[j] - fb[i].conj()) * r4;
            fa[i] = c1 * d1 + c2 * d2 * r5;
            fb[i] = c1 * d2 + c2 * d1;
        }
        fa[j] = a1 * b1 + a2 * b2 * r5;
        fb[j] = a1 * b2 + a2 * b1;
    }
    fft(sz, fa);
    fft(sz, fb);
    vector<MODINT> ret(sz);
    long long int bp = MODINT(2).power(D_FFT);
    long long int cp = MODINT(2).power(D_FFT * 2);
    for (int i = 0; i < need; i++) {
        long long int aa = llround(fa[i].x);
        long long int bb = llround(fb[i].x);
        long long int cc = llround(fa[i].y);
        aa = MODINT(aa).val, bb = MODINT(bb).val, cc = MODINT(cc).val;
        ret[i] = aa + (bb * bp) + (cc * cp);
        //   ret[i] = aa + (bb << DFFT) + (cc << (DFFT * 2));
    }
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

