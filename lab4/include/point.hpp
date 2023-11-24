#include <point.h>

template <Number N>
std::istream& operator>>(std::istream& in, point<N>& point) {
    in >> point.x >> point.y;
    return in;
}

template <Number N>
std::ostream& operator<<(std::ostream& out, const point<N>& point) {
    out << '(' << point.x << ',' << point.y << ")  \n";
    return out;
}

template <Number N>
bool dbEqual(N a, N b)
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}

template <Number N>
bool point<N>::operator==(point<N>& other) {
    return (x - other.x < 0.00001 && x - other.x > -0.00001)  && (y - other.y < 0.00001 && y - other.y > -0.00001) ;
}

template <Number N>
bool point<N>::operator<(point<N>& other) {
    if (x < other.x) {
        return true;
    } else if (x == other.x) {
        return y < other.y;
    }
    return false;
}

template <Number N>
long double Distance(point<N>&a, point<N>&b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

template <Number N>
bool comparePoints(point<N>& p1, point<N>& p2) {
    if (p1.x - p2.x < 0.00001 && p1.x - p2.x > -0.00001) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}

template <Number N>
bool comparePointsY(point<N>& p1, point<N>& p2) {
    return p1.y > p2.y;
}

template <Number N>
bool compareClockwise(point<N>& center,point<N>& a, point<N>& b) {
    long double angleA = atan2(a.y - center.y, a.x - center.x);
    long double angleB = atan2(b.y - center.y, b.x - center.x);
    return angleA < angleB;
}