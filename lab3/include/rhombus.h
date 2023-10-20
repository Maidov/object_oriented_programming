#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class Rhombus: virtual public Figure{
public:
    Rhombus();
    Rhombus(point x, point y,  double multiply);
    Rhombus(const std::initializer_list<point> &dots);
protected:
    double calcArea() const override;
    bool equals(const Figure& other) const override;
    void constructFig(point &dot, double multiply);
    void check() const override;
};