#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <algorithm>
#include <memory>

template <Number X>
class Pentagon : public Figure<X> {
using Figure<X>::vertices;
using Figure<X>::_size;
using Figure<X>::findCenter;
public:
    Pentagon();
    Pentagon(point<X> p0, point<X> p1, point<X> p2, point<X> p3, point<X> p4);

    bool isThisFigure() override;
    std::string draw() const override;
    operator double() ;
};

#include "pentagon.hpp"