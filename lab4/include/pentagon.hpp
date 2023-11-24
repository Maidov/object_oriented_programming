#include "pentagon.h"
template <Number X>
Pentagon<X>::Pentagon() : Figure<X>(5) {}

template <Number X>
bool Pentagon<X>::isThisFigure() {
    return Figure<X>::trueFigCheck();
}

template <Number X>
Pentagon<X>::operator double() {
    point<X> center = findCenter();
    return _size * pow(Distance(center, vertices[0]), 2) * sin((2*M_PI)/_size) * 0.5;
}

template <Number X>
Pentagon<X>::Pentagon(point<X> p0, point<X> p1, point<X> p2, point<X> p3, point<X> p4) : Figure<X>(5){
    vertices[0] = p0;
    vertices[1] = p1;
    vertices[2] = p2;
    vertices[3] = p3;
    vertices[4] = p4;
    
    if (!isThisFigure()) {
            _size = 0;
        throw std::invalid_argument("This is not Pentagon");
    }
}

template <Number X>
std::string Pentagon<X>::draw() const {
    return "This is a Pentagon.";
}