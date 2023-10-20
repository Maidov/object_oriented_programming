#pragma once

#include <string>
#include <iostream>
#include "point.h"
class Figure
{ 
public:
    // initialization
    Figure();
    Figure(int n);
    Figure(point &center, int n);
    Figure(const std::initializer_list<point> &dots, int n);
    virtual ~Figure() noexcept;

    // methods
    point getGCenter() const; // NEED
    const std::string getTag() const;
    const int size() const;
    const point* getDots() const;
    operator double();  // NEED
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;
    bool operator==(const Figure& other) const;

    // I/O overload
    friend std::ostream& operator<<(std::ostream &stream, const Figure&  Figure); // NEED
    friend std::istream& operator>>(std::istream &stream, Figure& Figure);        // NEED

protected:
    virtual void check() const;
    virtual bool equals(const Figure& other) const;
    virtual double calcArea() const;
    bool trueFigCheck(int n) const;
    void constructFig(point &dot, int n);
    bool dbEqual(double a, double b) const;
    double distance(point a, point b) const;
    double degrE2Rad(double a) const;
    std::string tag = "NULL";
    point *arr;

private:
    size_t _size = 2;
};
