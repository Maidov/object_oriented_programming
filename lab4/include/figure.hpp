//переделать на пушбеки
template <Number N>       
Figure<N>::Figure() : vertices(DynamicArray<point<N>>()), _size(0) {};

template <Number N> 
Figure<N>::Figure(int n) : vertices(DynamicArray<point<N>>(n)), _size(n) {};

template <Number N>    
point<N> Figure<N>::findCenter() {
    point<N> center = {0, 0};
    for (int i = 0; i < _size; ++i) {
        center.x += vertices[i].x;
        center.y += vertices[i].y;
    }
    center.x /= _size;
    center.y /= _size;
    return center;
}

template <Number N>    
bool Figure<N>::isThisFigure() {
    return true;
}

template <Number N>    
std::string Figure<N>::draw() const {
    return "This is a generic figure.";
}

template <Number N>     
Figure<N>::operator double() {
    return (vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y))/2;
}

template <Number N>      
std::istream& operator>>(std::istream& in, Figure<N>& figure) {
    for (int i = 0; i < figure._size; ++i) {
        in >> figure.vertices[i];
    }
    if (figure.isThisFigure()) {
        return in;
    }
    throw std::invalid_argument("Ты что то перепутал");
}

template<Number N>
bool Figure<N>::trueFigCheck(){
    int n = _size;
    point<N> center = findCenter();
    double setDis = Distance(vertices[0], vertices[n - 1]);
    double setR = Distance(center, vertices[_size-1]);
    
    if (setDis == 0) return false;
    for (size_t i = 0; i < (_size - 1); i++)
    {
        double dis = Distance(vertices[i], vertices[i+1]);
        double r = Distance(center ,vertices[i]);
        if (!(dbEqual(r, setR))) return false;
        if (!(dbEqual(dis, setDis))) return false;
    }
    return true;
}

template <Number N>    
std::ostream& operator<<(std::ostream& out, Figure<N>& figure) {
    for (int i = 0; i < figure._size; ++i) {
        point<N> p = figure.vertices[i];
        out << p;
    }
    return out;
}

template <Number N>      
bool Figure<N>::operator==(Figure& other) {
    if (_size != other._size) {
        return false;
    }
    long double distances1[_size];
    long double distances2[_size];
    for (int i = 0; i < _size; ++i) {
        distances1[i] = Distance(vertices[i],vertices[(i+1)%_size]);
        distances2[i] = Distance(other.vertices[i],other.vertices[(i+1)%_size]);
    }
    std::sort(distances1, distances1 + _size);
    std::sort(distances2, distances2 + _size);
    for (int i = 0; i < _size; ++i) {
        if (!(distances1[i] == distances2[i])) {
            return false;
        }
    }
    return true;

}

template <Number N>    
Figure<N>& Figure<N>::operator=(Figure<N>& other) {
    if (_size != other._size) {
        throw std::underflow_error("Разные фигуры");
    }
    if (*this != other) {
        _size  = other._size;
            delete[] vertices;
        vertices = new point[_size];

        for(size_t i = 0; i < _size; ++i) {
            vertices[i] = other.vertices[i];
        }
    }    
    return *this;
}

template <Number N>     
Figure<N>& Figure<N>::operator=(Figure<N>&& other) noexcept
{
    if (this->_size != other._size); {
        throw std::underflow_error("Разные фигуры");
    }
    if (this != &other) {
        delete[] vertices;
        vertices = other.vertices;
        other.vertices = nullptr;
    }
    return *this;
}

template <Number N>     
Figure<N>::~Figure() noexcept  {
    _size = 0;
} 



// #include "figure.h"
// #include <cmath>
// #include <iomanip>

// template<Axis M>
// Figure<M>::Figure(): arr(DynamicArray<point<M>>()), _size(0) {
//     std::cout << "FIG_D";
// }

// template<Axis M>
// Figure<M>::Figure(int n)
// {
//     _size = n;
//     arr = DynamicArray<point<M>>(n);
// }

// template<Axis M>
// Figure<M>::Figure(point<M> &center, int n)
// {
//     std::cout << "FIGcen";
//     _center = center;
//     _size = n;
//     arr(DynamicArray<point<M>>(n));
// }

// template<Axis M>
// Figure<M>::Figure(const std::initializer_list<point<M>> &dots, int n)
// {
//     this->_size = n;
//     if(dots.size() != n) throw std::underflow_error("You fucked up with quantity of numbers");
//     arr(DynamicArray<point<M>>(n));
//     size_t i = 0;
//     for (auto &c : dots) { 
//         arr[i++] = c;
//         _center.x += arr[i - 1].x;
//         _center.y += arr[i - 1].y;
//     }

//     _center.x /= n;
//     _center.y /= n;
// }

// template<Axis M>
// const point<M>* Figure<M>::getDots() const
// {
//     return arr;
// }

// template<Axis M>
// Figure<M>::~Figure() noexcept 
// {
//     this->_size = 0;
// }

// template<Axis M>
// point<M> Figure<M>::getGCenter() const{
//     return _center;
// }

// template<Axis M>
// void Figure<M>::refreshCenter()
// {
//     point center{0, 0};

//     for (size_t i = 0; i < _size; i++)
//     {
//         center.x += arr[i].x;
//         center.y += arr[i].y;
//     }
//     center.x /= _size;
//     center.y /= _size;
//     _center = center;
// }

// template<Axis M>
// const int Figure<M>::size() const
// {
//     return _size;
// }

// template<Axis M>
// const std::string Figure<M>::getTag() const
// {
//     return this->tag;
// }

// template<Axis M>
// void Figure<M>::constructFig(point<M> &dot, int n)
// {
//     double angle = degrE2Rad(360/n);
//     double alfa = atan((double(_center.y - dot.y))/(double(_center.x - dot.x)));
//     double r = distance(_center, dot);
//     std::cout << "\nR=" << r << "\n";
//     for (size_t i = 0; i < n; i++)
//     {
//         arr[i].x = _center.x + (r * cos(alfa + (angle * i)));
//         arr[i].y = _center.y + (r * sin(alfa + (angle * i)));
//     }
// }

// template<Axis M>
// bool Figure<M>::trueFigCheck(int n) const
// {
//     double setDis = distance(arr[0], arr[n - 1]);
//     double setR = distance(_center, arr[_size-1]);
//     if (setDis == 0) return false;
//     for (size_t i = 0; i < (_size - 1); i++)
//     {
//         double dis = distance(arr[i], arr[i+1]);
//         double r = distance(_center ,arr[i]);
//         if (!(dbEqual(r, setR))) return false;
//         if (!(dbEqual(dis, setDis))) return false;
//     }
//     return true;
// }

// template<Axis M>
// double Figure<M>::distance(point<M> a, point<M> b) const
// {
//     return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
// }

// template<Axis M>
// double Figure<M>::degrE2Rad(double a) const
// {
//     return a * (M_PI / 180);
// }

// template<Axis M>
// bool Figure<M>::dbEqual(M a, M b) const
// {
//     double eps = 1e-5;
//     return (fabs(a - b) < eps);
// }

// template<Axis M>
// double Figure<M>::calcArea() const
// {
//     return _size * pow(distance(_center, arr[0]), 2) * sin((2*M_PI)/_size) * 0.5;
// }

// template<Axis M>
// Figure<M>::operator double()
// {
//     return static_cast<double>(calcArea());
// }

// template<Axis M>
// bool Figure<M>::operator==(const Figure<M>& other) const
// {
//     if ((_size != other._size) || (this->tag != other.tag)) return false;
//     if (!(equals(other))) return false;
//     return true;
// }

// template<Axis M>
// Figure<M>& Figure<M>::operator=(Figure<M>& other)
// {
//     if (*this == other) {
//         return *this;
//     }    
//     _size  = other._size;
//     delete[] arr;
//     arr = new point[_size];

//     for(size_t i{0}; i < _size; ++i) arr[i] = other.arr[i];
//     refreshCenter();
//     return *this;
// }

// template<Axis M>
// Figure<M>& Figure<M>::operator=(Figure<M>&& other) noexcept
// {
//     if (this->tag != other.getTag());
//     if (!(this == &other)) {
//         delete[] arr; // Освобождаем собственные ресурсы
//         arr = other.arr; // Перемещаем ресурсы из other
//         other.arr = nullptr;
//     }
//     refreshCenter();
//     return *this;
// }

// template<Axis M>
// bool Figure<M>::equals(const Figure<M>& other) const
// {
//     double d1 = distance(this->arr[0], this->arr[1]);
//     double d2 = distance(other.arr[0], other.arr[1]);
//     if (!(dbEqual(d1, d2))) return false;
//     return true;
// }

// template<Axis M>
// void Figure<M>::check() const {}

// template<Axis M>
// std::ostream& operator<<(std::ostream& out, Figure<M>& _this) //out overload
// {
//     std::cout << std::left << std::setw(13) << "X" << "| " << std::setw(13) << "Y" << std::endl; 
//     for (size_t i = 0; i < _this._size; ++i) {
//         out << _this.arr[i];
//     }
//     return out;
// }

// template<Axis M>
// std::istream& operator>>(std::istream& in, Figure<M>& _this)
// {
//     double value;
//     _this.arr = new point[_this._size];
//     for (size_t i = 0; i < _this._size; i++)
//     {
//         in >> value;
//         _this.arr[i].x = value;
//         in >> value;
//         _this.arr[i].y = value;
//     }
//     _this.refreshCenter();
//     _this.check();
//     return in;
// }