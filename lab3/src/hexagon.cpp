#include "hexagon.h"

void Hexagon::check() const{
    if (!(Figure::trueFigCheck(this->size()))) throw std::underflow_error("Dumb ass. This is not HEXAGON");
}

Hexagon::Hexagon() : Figure(6) {
    tag = "HEXAGON";
}

Hexagon::Hexagon(point x, point y) : Figure(x, 6){
    tag = "HEXAGON";
    constructFig(y, 6);
    check();
};

Hexagon::Hexagon(const std::initializer_list<point> &dots) : Figure(dots, 6){
    tag = "HEXAGON";
    check();
};