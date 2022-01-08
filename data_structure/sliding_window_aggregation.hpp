#pragma once
#include <stack>
#include <utility>
using namespace std;

// CUT begin
// Sliding-Window Aggregation based queue
// - `std::queue`-like data structure with monoid operation
// - Each operation is amortized O(1)
// - Verification:
// <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>
// - Reference:
// <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>
template <typename T_VAL, typename T_PROD, T_PROD (*val2prod)(T_VAL), T_PROD (*merge)(T_PROD, T_PROD)>
struct SlidingWindowAggregation {
    std::stack<std::pair<T_VAL, T_PROD>> front_stack, back_stack;
    T_PROD ID_;

    SlidingWindowAggregation(T_PROD id_prod) : ID_(id_prod) {}
    bool empty() const { return front_stack.empty() and back_stack.empty(); }
    int size() const { return front_stack.size() + back_stack.size(); }
    T_PROD fold_all() const {
        if (empty())
            return ID_;
        else if (front_stack.empty())
            return back_stack.top().second;
        else if (back_stack.empty())
            return front_stack.top().second;
        else
            return merge(front_stack.top().second, back_stack.top().second);
    }
    void push(const T_VAL &x) {
        if (back_stack.empty())
            back_stack.emplace(x, val2prod(x));
        else
            back_stack.emplace(x, merge(back_stack.top().second, val2prod(x)));
    }
    T_VAL pop() {
        if (front_stack.empty()) {
            front_stack.emplace(back_stack.top().first, val2prod(back_stack.top().first));
            back_stack.pop();
            while (!back_stack.empty()) {
                T_VAL t = back_stack.top().first;
                front_stack.emplace(t, merge(val2prod(t), front_stack.top().second));
                back_stack.pop();
            }
        }
        T_VAL t = front_stack.top().first;
        front_stack.pop();
        return t;
    }
};

template <typename T> T swag_op_id(T x) { return x; };
template <typename T> T swag_op_linear_merge(T l, T r) {
    return make_pair(l.first * r.first, l.second * r.first + r.second);
};

// Linear function composition
// `f(x) = first * x + second`, operate most recently added function first
template <typename T>
struct LinearFunctionQueue
    : public SlidingWindowAggregation<pair<T, T>, pair<T, T>, swag_op_id, swag_op_linear_merge> {
    LinearFunctionQueue()
        : SlidingWindowAggregation<pair<T, T>, pair<T, T>, swag_op_id,
                                   swag_op_linear_merge>::SlidingWindowAggregation(pair<T, T>(1, 0)) {
    }
};
