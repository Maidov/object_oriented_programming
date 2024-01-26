#include <point.h>


std::istream& operator>>(std::istream& in, point& point) {
    in >> point.x >> point.y;
    return in;
}


std::ostream& operator<<(std::ostream& out, const point& point) {
    out << '(' << point.x << ',' << point.y << ")  \n";
    return out;
}


bool dbEqual(int a, int b)
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}


bool point::operator==(point& other) {
    return (x - other.x < 0.00001 && x - other.x > -0.00001)  && (y - other.y < 0.00001 && y - other.y > -0.00001) ;
}


long double distance(point a, point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

