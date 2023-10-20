#include "rhombus.h"
#include <cmath>

void Rhombus::check() const{
    point center = this->getGCenter();
    int n = this->size();
    double setDis = distance(arr[0], arr[n - 1]);
    for (size_t i = 0; i < (n - 1); i++)
    {
        double dis = distance(arr[i], arr[i+1]);
        if (!(dbEqual(dis, setDis))) throw std::underflow_error("This is not a rhombus");;
    }
}

double Rhombus::calcArea() const{
    return distance(this->arr[1], this->arr[3]) * distance(this->arr[0], this->arr[2]) * 0.5;
}


bool Rhombus::equals(const Figure& other) const{
    double diagMain1 = distance(this->arr[0], this->arr[2]);
    double daigSub1 = distance(this->arr[1], this->arr[3]);

    double diagMain2 = distance(other.getDots()[0], other.getDots()[2]);
    double daigSub2 = distance(other.getDots()[1], other.getDots()[3]);

    if (!((dbEqual(diagMain1, diagMain2) && dbEqual(daigSub1, daigSub2)) || (dbEqual(diagMain1, daigSub2) && dbEqual(daigSub1, diagMain2))))
        return false;
    return true;
}


Rhombus::Rhombus() : Figure(4){
    tag = "RHOMBUS";
};

Rhombus::Rhombus(point x, point y, double multiply) : Figure(x, 4){
    tag = "RHOMBUS";
    constructFig(y, multiply);
    check();
}

Rhombus::Rhombus(const std::initializer_list<point> &dots) : Figure(dots, 4){
    tag = "RHOMBUS";
    check();
};

void Rhombus::constructFig(point &dot, double multiply){
    point center = this->getGCenter();
    double angle = degrE2Rad(360/4);
    double alfa = atan((dot.y - center.y)/(dot.x - center.x));
    double r = distance(center, dot);
    double multi = 1;

    if ((1 < multiply) || (multiply < 0)) throw std::underflow_error("Multiply must be (0 < multiply < 1)");

    for (size_t i = 0; i < 4; i++)
    {
        if ((i % 2) == 0) {
            multi = 1;
        } else {
            multi = multiply;
        }
        // std::cout <<  "r: " << r * multi * cos(alfa + (angle * i)) << "\n";
        arr[i].x = center.x + (r * cos(alfa + (angle * i)) * multi);   
        arr[i].y = center.y + (r * sin(alfa + (angle * i)) * multi);
    }                                   
}
