#include "figure.h"
#include "point.h"
#include <cmath>
#include <iomanip>
Figure::Figure(): arr(nullptr), _size(0) {}

Figure::Figure(int n)
{
    _size = n;
    arr = new point[n];
}

Figure::Figure(point &center, int n)
{
    this->_size = n;
    arr = new point[n];
}


Figure::Figure(const std::initializer_list<point> &dots, int n)
{
    this->_size = n;
    if(dots.size() != n) throw std::underflow_error("You fucked up with quantity of numbers");
    arr = new point[n];
    size_t i = 0;

    for (auto &c : dots) { 
        arr[i++] = c;
    }
}

const point* Figure::getDots() const
{
    return arr;
}


Figure::~Figure() noexcept 
{
    delete[] arr;
    arr = nullptr;
}



point Figure::getGCenter() const
{
    point center{0, 0};

    for (size_t i = 0; i < _size; i++)
    {
        center.x += arr[i].x;
        center.y += arr[i].y;
    }
    center.x /= _size;
    center.x /= _size;
    return center;
}

const int Figure::size() const
{
    return _size;
}

const std::string Figure::getTag() const
{
    return this->tag;
}

void Figure::constructFig(point &dot, int n)
{
    point center = getGCenter();
    double angle = degrE2Rad(360/n);
    double alfa = atan((center.y - dot.y)/(center.x - dot.x));
    double r = distance(center, dot);

    for (size_t i = 0; i < n; i++)
    {
        arr[i].x = center.x + (r * cos(alfa + (angle * i)));
        arr[i].y = center.y + (r * sin(alfa + (angle * i)));
    }
}

bool Figure::trueFigCheck(int n) const
{
    point center = getGCenter();
    double setDis = distance(arr[0], arr[n - 1]);
    double setR = distance(center, arr[_size-1]);
    for (size_t i = 0; i < (_size - 1); i++)
    {
        double dis = distance(arr[i], arr[i+1]);
        double r = distance(center ,arr[i]);
        if (!(dbEqual(r, setR))) return false;
        if (!(dbEqual(dis, setDis))) return false;
    }
    return true;
}

double Figure::distance(point a, point b) const
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

double Figure::degrE2Rad(double a) const
{
    return a * (M_PI / 180);
}

bool Figure::dbEqual(double a, double b) const
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}

double Figure::calcArea() const
{
    return (_size * pow(distance(arr[0], arr[1]), 2)) / (4 * (tan(M_PI / _size)));
}

Figure::operator double()
{
    return static_cast<double>(calcArea());
}

bool Figure::operator==(const Figure& other) const
{
    if ((_size != other._size) || (this->tag != other.tag)) return false;
    if (!(equals(other))) return false;
    return true;
}

Figure& Figure::operator=(const Figure& other)
{
    if (this->tag != other.getTag()) throw std::underflow_error("Trying to copy different figures");
    if (*this == other) {
        return *this;
    }    
    _size  = other._size;
    delete[] arr;
    arr = new point[_size];

    for(size_t i{0}; i < _size; ++i) arr[i] = other.arr[i];
    return *this;
}


Figure& Figure::operator=(Figure&& other) noexcept
{
    if (this->tag != other.getTag());
    if (this != &other) {
        delete[] arr; // Освобождаем собственные ресурсы
        arr = other.arr; // Перемещаем ресурсы из other
        other.arr = nullptr;
    }
    return *this;
}


bool Figure::equals(const Figure& other) const
{
    double d1 = distance(this->arr[0], this->arr[1]);
    double d2 = distance(other.arr[0], other.arr[1]);
    if (!(dbEqual(d1, d2))) return false;
    return true;
}

void Figure::check() const {}

std::ostream& operator<<(std::ostream& out, const Figure& _this) //out overload
{
    std::cout << std::left << std::setw(13) << "X" << "| " << std::setw(13) << "Y" << std::endl; 
    for (size_t i = 0; i < _this._size; ++i) {
        out << _this.arr[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, Figure& _this)
{
    double value;
    _this.arr = new point[_this._size];
    for (size_t i = 0; i < _this._size; i++)
    {
        in >> value;
        _this.arr[i].x = value;
        in >> value;
        _this.arr[i].y = value;
    }

    _this.check();
    return in;
}