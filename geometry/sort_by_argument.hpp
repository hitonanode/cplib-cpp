#pragma once

// Point on grid, sortable by its argument
struct Point {
    long long X, Y;
    Point() = default;
    Point(long long x, long long y) : X(x), Y(y) {}

    bool operator<(const Point &r) const {
        const int ll = lower_or_upper(), lr = r.lower_or_upper();
        if (ll != lr) return ll < lr;
        return X * r.Y > r.X * Y;
    }

    bool operator==(const Point &r) const {
        return lower_or_upper() == r.lower_or_upper() and X * r.Y == r.X * Y;
    }

    int lower_or_upper() const {
        if (Y) return Y > 0 ? 1 : -1;
        if (X) return X > 0 ? -1 : 1;
        return 0; // origin
    }

    void rotate_pi() { X = -X, Y = -Y; }
};
