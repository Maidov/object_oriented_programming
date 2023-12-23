#pragma once

#include <cmath>
#include <iostream>
#include <concepts>
#include <memory>


class point {
    public:
    int x;
    int y;
    point() = default;
    point(const int& x, const int& y) : x(x), y(y) {}
    friend std::istream& operator>>(std::istream& in, point& point);
    friend std::ostream& operator<<(std::ostream& out, const point& point);
    bool operator==(point& other);
};

long double distance(point a, point b);
bool dbEqual(int a, int b);

