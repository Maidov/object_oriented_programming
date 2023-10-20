#include "pentagon.h"

void Pentagon::check() const{
    if (!(Figure::trueFigCheck(this->size()))) throw std::underflow_error("Dumb ass. This is not PENTAGON");
}

Pentagon::Pentagon() : Figure(5){
    tag = "PENTAGON";
}

Pentagon::Pentagon(point x, point y) : Figure(x, 5){
    tag = "PENTAGON";
    constructFig(y, 5);
    check();
}

Pentagon::Pentagon(const std::initializer_list<point> &dots) : Figure(dots, 5){
    tag = "PENTAGON";
    check();
};