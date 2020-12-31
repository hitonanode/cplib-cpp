#pragma once
#include <vector>

// CUT begin
// Simple forward_list for MLE-sensitive situations
// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>
template <typename T> struct light_forward_list {
    static std::vector<unsigned> ptr;
    static std::vector<T> val;
    unsigned head;
    light_forward_list() : head(0) {}
    void push_front(T x) {
        ptr.push_back(head), val.push_back(x);
        head = ptr.size() - 1;
    }
    struct iterator {
        unsigned p;
        iterator operator++() { return {p = ptr[p]}; }
        T &operator*() { return val[p]; }
        bool operator!=(const iterator &rhs) { return p != rhs.p; }
    };
    iterator begin() { return {head}; }
    iterator end() { return {0}; }
};
template <typename T> std::vector<unsigned> light_forward_list<T>::ptr = {0};
template <typename T> std::vector<T> light_forward_list<T>::val = {0};
