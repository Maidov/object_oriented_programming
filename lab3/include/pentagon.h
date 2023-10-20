#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class Pentagon: virtual public Figure{
public:
    Pentagon();
    Pentagon(point x, point y);
    Pentagon(const std::initializer_list<point> &dots);
    Pentagon& operator=(Pentagon&& other);
    
protected:
    void check() const override;
};

