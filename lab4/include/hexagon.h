#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <algorithm>
#include <memory>

template <Number X>
class Hexagon : public Figure<X> {
using Figure<X>::vertices;
using Figure<X>::_size;
using Figure<X>::findCenter;
public:
    Hexagon();
    Hexagon(point<X> p0, point<X> p1, point<X> p2, point<X> p3, point<X> p4, point<X> p5);

    bool isThisFigure() override;
    std::string draw() const override;
    operator double() ;
};

#include "hexagon.hpp"