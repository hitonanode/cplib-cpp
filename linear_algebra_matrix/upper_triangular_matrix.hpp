#pragma once

#include <compare>

template <class T> struct UpperTriangular3d {
private:
    struct DesignatedInitializationOnly {
    private:
        constexpr DesignatedInitializationOnly() = default;
        constexpr DesignatedInitializationOnly(const DesignatedInitializationOnly &) = default;
        DesignatedInitializationOnly &operator=(const DesignatedInitializationOnly &) = default;
        friend UpperTriangular3d;

    public:
        auto operator<=>(const DesignatedInitializationOnly &) const = default;
    };

    template <class U> static constexpr U explicit_init_required() {
        static_assert(sizeof(U) == 0, "all matrix entries must be explicitly initialized");
        return U{};
    }

public:
    [[no_unique_address]] DesignatedInitializationOnly designated_initialization_only{};
    T a00 = explicit_init_required<T>(), a01 = explicit_init_required<T>(),
      a02 = explicit_init_required<T>();
    T a11 = explicit_init_required<T>(), a12 = explicit_init_required<T>();
    T a22 = explicit_init_required<T>();

    UpperTriangular3d operator*(const UpperTriangular3d &r) const {
        return UpperTriangular3d{
            .a00 = this->a00 * r.a00,
            .a01 = this->a00 * r.a01 + this->a01 * r.a11,
            .a02 = this->a00 * r.a02 + this->a01 * r.a12 + this->a02 * r.a22,
            .a11 = this->a11 * r.a11,
            .a12 = this->a11 * r.a12 + this->a12 * r.a22,
            .a22 = this->a22 * r.a22,
        };
    }

    UpperTriangular3d operator-() const {
        return UpperTriangular3d{
            .a00 = -this->a00,
            .a01 = -this->a01,
            .a02 = -this->a02,
            .a11 = -this->a11,
            .a12 = -this->a12,
            .a22 = -this->a22,
        };
    }

    UpperTriangular3d operator+(const UpperTriangular3d &r) const {
        return UpperTriangular3d{
            .a00 = this->a00 + r.a00,
            .a01 = this->a01 + r.a01,
            .a02 = this->a02 + r.a02,
            .a11 = this->a11 + r.a11,
            .a12 = this->a12 + r.a12,
            .a22 = this->a22 + r.a22,
        };
    }

    auto operator<=>(const UpperTriangular3d &) const = default;
};
