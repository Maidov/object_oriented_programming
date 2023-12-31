#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class Hexagon: virtual public Figure{
public:
    Hexagon();
    Hexagon(point x, point y);
    Hexagon(const std::initializer_list<point> &dots);
    Hexagon& operator=(Hexagon& other);
    Hexagon& operator=(Hexagon&& other);
    
protected:
    void check() const override;
};

