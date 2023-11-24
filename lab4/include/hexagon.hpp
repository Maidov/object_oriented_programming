#include "hexagon.h"
template <Number X>
    Hexagon<X>::Hexagon() : Figure<X>(6) {}

template <Number X>
bool Hexagon<X>::isThisFigure() {
    return Figure<X>::trueFigCheck();
}

template <Number X>
Hexagon<X>::operator double() {
    point<X> center = findCenter();
    return _size * pow(Distance(center, vertices[0]), 2) * sin((2*M_PI)/_size) * 0.5;
}

template <Number X>
Hexagon<X>::Hexagon(point<X> p0, point<X> p1, point<X> p2, point<X> p3, point<X> p4, point<X> p5) : Figure<X>(6){
    vertices[0] = p0;
    vertices[1] = p1;
    vertices[2] = p2;
    vertices[3] = p3;
    vertices[4] = p4;
    vertices[5] = p5;
    
    if (!isThisFigure()) {
            _size = 0;
        throw std::invalid_argument("This is not HEXAGON");
    }
}

template <Number X>
std::string Hexagon<X>::draw() const {
    return "This is a HEXAGON.";
}