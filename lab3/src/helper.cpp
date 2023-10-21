#include <cmath>
#include "point.h"

bool dbEqual(double a, double b)
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}

double distance(point a, point b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}