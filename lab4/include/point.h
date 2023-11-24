#pragma once

#include <cmath>
#include <iostream>
#include <concepts>
#include <memory>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number N>
class point {
    public:
    N x;
    N y;
    point() = default;
    point(const N& x, const N& y) : x(x), y(y) {}
    template <Number _N>
    friend std::istream& operator>>(std::istream& in, point<_N>& point);
    template <Number N_>
    friend std::ostream& operator<<(std::ostream& out, const point<N_>& point);
    bool operator==(point& other);
    bool operator<(point& other);
};
template <Number N>
long double Distance(point<N> &a, point<N> &b);
template <Number N>
bool comparePoints(point<N>& p1, point<N>& p2);
template <Number N>
bool comparePointsY(point<N>& p1, point<N>& p2);
template <Number N>
bool compareClockwise(point<N>& center, point<N>& a, point<N>& b);
template <Number N>
bool dbEqual(N a, N b);
#include "point.hpp"