#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class FigureCollection {
public:
    FigureCollection();
    virtual ~FigureCollection();

    void displayGCenters();
    void displayAreas();
    double getAllArea();

    void remove(int index);
    void pushBack(Figure* figure);
    Figure* get(int index);

    friend std::ostream& operator<<(std::ostream &stream, const FigureCollection&  collection);

private:
    Figure** figures;
    int capacity;
    int size;
};