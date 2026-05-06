#pragma once

template <class T> struct UpperTriangular3d {
    static T explicit_init_required() = delete;
    T a00 = this->explicit_init_required(), a01 = this->explicit_init_required(),
      a02 = this->explicit_init_required();
    T a11 = this->explicit_init_required(), a12 = this->explicit_init_required();
    T a22 = this->explicit_init_required();

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
