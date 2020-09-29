#pragma once

// CUT begin
// Example: 1 -> 2, 4 -> 8, 12(1100) -> 17(10001)
template <typename Int>
Int next_combination(Int comb)
{
    Int x = comb & -comb, y = comb + x;
    return ((comb & ~y) / x >> 1) | y;
}
