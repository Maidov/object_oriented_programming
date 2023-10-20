#include "point.h"
#include <iomanip>

bool point::operator==(const point& other) const
{
    if ((this->x == other.x) && (this->y == other.y)) return true;
    return false;
}

bool point::operator!=(const point& other) const
{
    if (*this == other) return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const point& _this) //out overload
{
    out << std::left << std::setw(12) <<_this.x << " | "  << std::setw(12) << _this.y << std::endl;
    return out;
}