#include "rhombus.h"

template <Number X>
Rhombus<X>::Rhombus() : Figure<X>(4) {};

template <Number X>
bool Rhombus<X>::isThisFigure() {
    double area = Distance(this->vertices[1], this->vertices[3]) * Distance(this->vertices[0], this->vertices[2]) * 0.5;
    if ((area == 0)) return false;
    int n = _size;
    double setDis = Distance(vertices[0], vertices[n - 1]);
    for (size_t i = 0; i < (n - 1); i++)
    {
        double dis = Distance(vertices[i], vertices[i+1]);
        if (!(dbEqual(dis, setDis))) return false;
    }
    return true;
}

template <Number X>
Rhombus<X>:: Rhombus(point<X> p1, point<X> p2, point<X> p3, point<X> p4) : Figure<X>(4) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    if (!isThisFigure()) {
        _size = 0;
        throw std::invalid_argument("This is not RHOMBUS");
    }
}

template <Number X>
std::string Rhombus<X>::draw() const  {
    return "This is RHOMBUS";
}

template <Number X>
Rhombus<X>::operator double() {
    return Distance(this->vertices[1], this->vertices[3]) * Distance(this->vertices[0], this->vertices[2]) * 0.5;
}