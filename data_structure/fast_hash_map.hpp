#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <random>
#include <type_traits>

// Fixed-capacity hash map for integer keys.
// N must be a power of two. At most N distinct keys can be stored.
template <typename K, typename V, std::size_t N> struct HashMap {
    static_assert(std::has_single_bit(N));
    static_assert(std::is_integral_v<K>);
    static_assert(sizeof(K) <= sizeof(std::uint64_t));

private:
    std::array<K, N> keys;
    std::array<V, N> values;
    std::array<std::uint32_t, N> versions{};

    std::uint32_t version = 1;
    std::size_t count = 0;
    std::uint64_t multiplier;

    static std::uint64_t make_multiplier() noexcept {
        // Use a nondeterministic seed
        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
        return mt() | 1;
    }

    std::size_t hash(K key) const noexcept {
        if constexpr (N == 1) {
            return 0;
        } else {
            constexpr int shift = 64 - std::countr_zero(N);
            return (static_cast<std::uint64_t>(key) * multiplier) >> shift;
        }
    }

public:
    HashMap() : multiplier(make_multiplier()) {}

    void set(K key, V value) noexcept {
        std::size_t pos = hash(key);
        for (std::size_t step = 0; step < N; ++step) {
            if (versions[pos] != version) {
                keys[pos] = key;
                values[pos] = value;
                versions[pos] = version;
                assert(count < N);
                ++count;
                return;
            }
            if (keys[pos] == key) {
                values[pos] = value;
                return;
            }
            pos = (pos + 1) & (N - 1);
        }
        assert(false && "HashMap capacity exceeded");
    }

    V get(K key) const noexcept {
        std::size_t pos = hash(key);
        for (std::size_t step = 0; step < N; ++step) {
            if (versions[pos] != version) return V{};
            if (keys[pos] == key) return values[pos];
            pos = (pos + 1) & (N - 1);
        }
        return V{};
    }

    std::size_t size() const noexcept { return count; }
    bool empty() const noexcept { return count == 0; }

    void clear() noexcept {
        ++version;
        count = 0;
    }
    void reset() noexcept { clear(); }
};
