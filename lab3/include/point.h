#pragma once

#include <iostream>

class point
{
public:
    double x = 0;
    double y = 0;
    friend std::ostream& operator<<(std::ostream& out, const point& _this);

    void operator=(const point& other);
    bool operator==(const point& other) const;
    bool operator!=(const point& other) const;
private:
    bool dbEqual(double a, double b) const;
};
