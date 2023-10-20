#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class FigureCollection {
public:
    FigureCollection();
    virtual ~FigureCollection();
    friend std::ostream& operator<<(std::ostream &stream, const FigureCollection&  collection); // NEED
    void displayGCenters();
    void displayAreas();
    double getAllArea();
    void pushBack(Figure* figure);
    Figure* get(int index);

private:
    Figure** figures;
    int capacity;
    int size;
};