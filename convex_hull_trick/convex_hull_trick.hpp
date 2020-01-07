/*
Convex Hull Trick
- y = ax + b が順次追加されつつ，最大値/最小値クエリに答える
- y = c(x - a)^2 + b 型の関数を表す(a, b)たちが順次追加されつつ，最小値クエリに答える
Verify:
CF 1179D <https://codeforces.com/contest/1179/submission/59448330>
CF 1137E <https://codeforces.com/contest/1137/submission/59448399>
*/
#pragma once
#include <limits>
#include <set>
#include <vector>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>
using mpint = boost::multiprecision::cpp_int;

/*
Convex Hull Trick
Implementation Idea: <https://github.com/satanic0258/Cpp_snippet/blob/master/src/technique/ConvexHullTrick.cpp>
*/
using T_CHT = long long int;
struct ConvexHullTrick
{
    static const T_CHT T_MIN = numeric_limits<T_CHT>::lowest() + 1;
    struct Line
    {
        T_CHT a, b; // y = ax + b
        mutable pair<T_CHT, T_CHT> rp; // (numerator, denominator) `x` coordinate of the crossing point with next line
        Line(T_CHT a, T_CHT b) : a(a), b(b), rp(T_MIN, T_MIN) {}
        static pair<T_CHT, T_CHT> cross(const Line &ll, const Line &lr)
        {
            return make_pair(ll.b - lr.b, lr.a - ll.a); // `ll.a < lr.a` is assumed implicitly
        }
        bool operator<(const Line &r) const
        {
            if (b == T_MIN)
            {
                if (r.rp.first == T_MIN) return true;
                else return a * r.rp.second < r.rp.first;
            }
            else if (r.b == T_MIN)
            {
                if (rp.first == T_MIN) return false;
                else return !(r.a * rp.second < rp.first);
            }
            else return a < r.a;
        }
    };
    struct Lines : multiset<Line>
    {
        bool flg_min; // true iff for minimization
        inline bool isNeedless(iterator itr)
        {
            if (size() == 1) return false;
            auto nxt = next(itr);
            if (itr == begin()) return itr->a == nxt->a and itr->b <= nxt->b;
            else
            {
                auto prv = prev(itr);
                if (nxt == end()) return itr->a == prv->a and itr->b <= prv->b;
                // Prevent overflow
                else return mpint(prv->b - itr->b) * (nxt->a - itr->a) >= mpint(itr->b - nxt->b) * (itr->a - prv->a);
            }
        }
        void add_line(T_CHT a, T_CHT b)
        {
            if (flg_min) a = -a, b = -b;
            auto itr = insert({a, b});
            if (isNeedless(itr)) erase(itr);
            else
            {
                while (next(itr) != end() and isNeedless(next(itr)))
                {
                    erase(next(itr));
                }
                while (itr != begin() and isNeedless(prev(itr)))
                {
                    erase(prev(itr));
                }
                if (next(itr) != end())
                {
                    itr->rp = Line::cross(*itr, *next(itr));
                }
                if (itr != begin())
                {
                    prev(itr)->rp = Line::cross(*prev(itr), *itr);
                }
            }
        }
        Lines(bool is_minimizer): flg_min(is_minimizer) {}
        pair<T_CHT, T_CHT> get(T_CHT x)
        {
            auto itr = lower_bound({x, T_MIN});
            T_CHT retval = T_MIN, reta = T_MIN;
            if (itr != end())
            {
                retval = itr->a * x + itr->b;
                reta = itr->a;
            }
            if (itr != begin())
            {
                T_CHT tmp = prev(itr)->a * x + prev(itr)->b;
                if (tmp >= retval)
                {
                    retval = tmp;
                    reta = max(reta, prev(itr)->a);
                }
            }
            return make_pair(flg_min ? -retval : retval, flg_min ? -reta : reta);
        }
    };
    Lines lines;
    ConvexHullTrick(bool is_minimizer) : lines(is_minimizer) {}
    void add_line(T_CHT a, T_CHT b) { lines.add_line(a, b); } // Add y = ax + b
    pair<T_CHT, T_CHT> get(T_CHT x) { return lines.get(x); }
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(-2 * c * a, c * a * a + b); } // Add y = c(x - a)^2 + b
    T_CHT parabola_lower_bound(T_CHT c, T_CHT x) { return lines.get(x).first + c * x * x; }
};
const T_CHT ConvexHullTrick::T_MIN;
