#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <memory>

template <Number X>
class Rhombus : public Figure<X> {
using Figure<X>::vertices;
using Figure<X>::_size;
using Figure<X>::findCenter;
public:
    Rhombus();
    Rhombus(point<X> p1, point<X> p2, point<X> p3, point<X> p4);

    bool isThisFigure() override;
    std::string draw() const override;
    operator double() ;
};

#include "rhombus.hpp"