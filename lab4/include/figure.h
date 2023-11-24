#pragma once

#include "point.h"
#include "array.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>


//остались тесты и функции для приколов

template <Number N> 
class Figure {
protected:
    DynamicArray<point<N>> vertices;
    int _size;

public:
    Figure();
    Figure(int n);
    virtual point<N> findCenter();
    virtual bool isThisFigure();
    virtual std::string draw() const;
    virtual operator double() ;
    template <Number _N> 
    friend std::istream& operator>>(std::istream& in, Figure<_N>& figure);
    template <Number N_> 
    friend std::ostream& operator<<(std::ostream& out, Figure<N_>& figure);
    bool trueFigCheck();
    bool operator==(Figure<N>& other);
    Figure<N>& operator=(Figure<N>& other);
    Figure<N>& operator=(Figure<N>&& other) noexcept;
    
    virtual ~Figure() noexcept;
};

#include "figure.hpp"



// #pragma once


// #include "point.h"
// #include "array.h"
// #include <iostream>
// #include <algorithm>
// #include <string>
// #include <memory>





// template <typename T>
// concept Axis = std::integral<T> || std::floating_point<T>;

// template <Axis M>
// class Figure
// { 
// public:
// Figure();
//     Figure(int n);
//     Figure(point<M> &center, int n);
//     Figure(const std::initializer_list<point<M>> &dots, int n);
//     virtual ~Figure() noexcept;

//     const std::string getTag() const;
//     const int size() const;

//     point<M> getGCenter() const;
//     const point<M>* getDots() const;

//     operator double();
//     Figure& operator=(Figure<M>& other);
//     Figure& operator=(Figure<M>&& other) noexcept;
//     bool operator==(const Figure<M>& other) const;
    
//     template <Axis U>
//     friend std::ostream& operator<<(std::ostream &stream, Figure<U>&  Figure);
//     template <Axis U>
//     friend std::istream& operator>>(std::istream &stream, Figure<U>& Figure);

// protected:

//     virtual void check() const;
//     virtual bool equals(const Figure<M>& other) const;
//     virtual double calcArea() const;

//     bool trueFigCheck(int n) const;
//     bool dbEqual(M a, M b) const;
//     void refreshCenter();
//     void constructFig(point<M> &dot, int n);

//     double distance(point<M> a, point<M> b) const;
//     double degrE2Rad(double a) const;

//     std::string tag = "NULL";
//     DynamicArray<point<M>> arr;
//     point<M> _center;
// private:
//     size_t _size = 2;
// };

// #include "figure.hpp"
