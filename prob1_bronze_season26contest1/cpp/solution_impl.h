#ifndef USACO_PROB1_SOLUTION_IMPL_H
#define USACO_PROB1_SOLUTION_IMPL_H

#include <cstdint>

using ll = long long;

inline ll solve_case(ll a, ll b, ll c_a, ll c_b, ll f_a) {
    ll initial_a = (b / c_b) * c_a + a;
    if (initial_a >= f_a) {
        return 0;
    }

    ll need_a = f_a - 1 - initial_a;
    ll y = c_b - 1 - (b % c_b);

    if (c_a >= c_b) {
        y += need_a;
    } else {
        y += (need_a / c_a) * c_b + (need_a % c_a);
    }

    return y + 1;
}

#endif
