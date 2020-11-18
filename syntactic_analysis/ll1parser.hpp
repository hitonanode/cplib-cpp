#pragma once
#include <cmath>
#include <string>

// CUT begin
// 構文木を作らず簡単な整数加減乗算をやるLL(1)構文解析
// https://gist.github.com/draftcode/1357281 などが参考になる
template <typename T> struct Parser {
    using State = std::string::const_iterator;

    Parser() {}

    T expr(State &begin) {
        T ret = term(begin);
        while (true) {
            if (*begin == '+') {
                begin++;
                ret += term(begin);
            } else if (*begin == '-') {
                begin++;
                ret -= term(begin);
            } else
                break;
        }
        return ret;
    }

    T term(State &begin) {
        T ret = factor(begin);
        while (true) {
            if (*begin == '*') {
                begin++;
                ret *= factor(begin);
            } else
                break;
        }
        return ret;
    }

    T value(State &begin) {
        T ret = 0;
        while (isdigit(*begin)) {
            ret *= 10;
            ret += *begin - '0';
            begin++;
        }
        return ret;
    }

    T factor(State &begin) {
        if (*begin == '(') {
            begin++;
            T ret = expr(begin);
            begin++;
            return ret;
        } else
            return value(begin);
    }
};
/* example usage
Parser<long long> parser();
std::string::const_iterator iter = S.begin();
std::cout << parser.expr(iter) << '\n';
*/
