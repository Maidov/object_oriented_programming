#include "fcollection.h"


FigureCollection::FigureCollection() : size(0), capacity(3) {
    figures = new Figure*[capacity];
}

FigureCollection::~FigureCollection() {
    delete[] figures;
    figures = nullptr;
}

void FigureCollection::pushBack(Figure* figure)  {
    if (size >= capacity) {
        capacity *= 2;
        Figure** newCollection = new Figure*[capacity];
        for (int i = 0; i < size; i++) {
            newCollection[i] = this->figures[i];
        }
        delete[] figures;
        this->figures = newCollection;
    }
    this->figures[size++] = figure;
}

std::ostream& operator<<(std::ostream& out, const FigureCollection& _this) //out overload
{
    for (size_t i = 0; i < _this.size; ++i) {
        out << "\n      V " << _this.figures[i]->getTag() << " V" << "\n" << *_this.figures[i];
    }
    return out;
}

void FigureCollection::displayGCenters(){
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "\n   V " << this->figures[i]->getTag() << " CENTER V" << "\n" ;
        std::cout << figures[i]->getGCenter();
    }
}

void FigureCollection::displayAreas(){
    for (size_t i = 0; i < size; i++)
    {
        std::cout << this->figures[i]->getTag() << " AREA = " << double(*figures[i]) << std::endl;
    }
}

double FigureCollection::getAllArea(){
    double result = 0;
    for (size_t i = 0; i < size; i++)
    {
        result += double(*figures[i]);
    }
    return result;
}

Figure* FigureCollection::get(int index) {
    if (index >= 0 && index < size) {
        return figures[index];
    } else {
        throw std::underflow_error("Index out of range");
    }
}

void FigureCollection::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::underflow_error("Index out of range");
    }

    Figure** newCollection = new Figure*[capacity - 1];
    for (size_t i = 0, j = 0; i < size; ++i)
    {
        if (i != index) {
            newCollection[j++] = this->figures[i];
        } else {
            delete this->figures[i];
        }
    }
    
    delete[] this->figures;
    size--;
    capacity--;
    this->figures = newCollection;

    // figures[index] = NULL; // Освобождаем память, выделенную под фигуру по индексу
    // for (int i = index; i < size - 1; i++) {
    //     figures[i] = figures[i + 1];
    // }
    // size--;

    // if (size < capacity / 2 && size > 0) {
    //     // Если размер стал значительно меньше, чем вместимость, можно уменьшить capacity.
    //     // В данном случае, я уменьшу capacity до ближайшей меньшей степени двойки.
    //     while (capacity / 2 >= size) {
    //         capacity /= 2;
    //     }
    //     Figure** newCollection = new Figure*[capacity];
    //     for (int i = 0; i < size; i++) {
    //         newCollection[i] = figures[i];
    //     }
    //     delete[] figures;
    //     figures = newCollection;
    // }
}