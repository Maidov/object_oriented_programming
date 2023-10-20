#pragma once

#include <iostream>

class point
{
public:
    double x = 0;
    double y = 0;
    
    friend std::ostream& operator<<(std::ostream& out, const point& _this);

    bool operator==(const point& other) const;
    bool operator!=(const point& other) const;
};
