#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class Pentagon: virtual public Figure{
public:
    Pentagon();
    Pentagon(point& cen, point& dot);
    Pentagon(const std::initializer_list<point> &dots);
    Pentagon& operator=(Pentagon& other);
    Pentagon& operator=(Pentagon&& other);
    
protected:
    void check() const override;
};

