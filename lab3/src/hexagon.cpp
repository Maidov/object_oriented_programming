#include "hexagon.h"

Hexagon::Hexagon() : Figure(6)
{
    tag = "HEXAGON";
}

Hexagon::Hexagon(point cen, point dot) : Figure(cen, 6)
{
    tag = "HEXAGON";
    constructFig(dot, 6);
    check();
};

Hexagon::Hexagon(const std::initializer_list<point> &dots) : Figure(dots, 6)
{
    tag = "HEXAGON";
    check();
};

void Hexagon::check() const
{
    if ((!(Figure::trueFigCheck(this->size())) || (this->calcArea() == 0)))  throw std::underflow_error("This is not HEXAGON");
}

Hexagon& Hexagon::operator=(Hexagon& other)
{
    if (this != &other) {
        Figure::operator=(other);
    }
    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other)
{
    if (this != &other) {
        Figure::operator=(std::move(other));
    }
    return *this;
}