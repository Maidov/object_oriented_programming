#include "six.h"

Six::Six(): arr(nullptr), _size(0) {}

Six::Six(const size_t &n, unsigned char t)  // Fill constructor
{
    if (t >= '6' || t < '0') throw std::underflow_error("invalid symbol");
    arr = new unsigned char[n];
    for (size_t i = 0; i < n; ++i)
        arr[n - i - 1] = t;
    _size = n;
    removeZeros();
}

Six::Six(const std::initializer_list<unsigned char> &t)  // Initializer list constructor
{
    arr = new unsigned char[t.size()];
    size_t i{t.size() - 1};
    for (auto &c : t) { 
        if (c >= '6' || c < '0') throw std::underflow_error("invalid symbol");
        arr[i--] = c;
    }
    _size = t.size();
    removeZeros();
}

Six::Six(const std::string &t)  // Copy string constructor
{
    arr = new unsigned char[t.size()];
    _size  = t.size();

    for(size_t i{0}; i < _size; ++i) {
        if (t[i] >= '6' || t[i] < '0') throw std::underflow_error("invalid symbol");
        arr[_size - i - 1] = t[i];
    }
    removeZeros();
}

Six::Six(const Six &other)  // Copy constructor
{
    _size  = other._size;
    arr = new unsigned char[_size];

    for(size_t i{0}; i < _size; ++i) arr[i] = other.arr[i];
    removeZeros();
}

Six::Six(Six &&other) noexcept  // Move constructor
{
    _size = other._size;
    arr = other.arr;

    other._size = 0;
    other.arr = nullptr;
    removeZeros();
}

int Six::size() {
    return _size;
}

void Six::convertToString(std::string& s) {
    for (size_t i = 0; i < _size; ++i) {
        s = static_cast<char>(arr[i]) + s;
    }
}

void Six::addZeros(int n) {
    unsigned char * array = new unsigned char[n + this->_size];
    for (size_t i = 0; i < this->_size; ++i) {
        array[i] = this->arr[i];
    }
    for (size_t i = 0; i < n; ++i) {
        array[i + this->_size] = '0';
    }
    this->_size = n + this->_size;
    this->arr = array;
}

void Six::removeZeros() {
    int t = -1;
    for (size_t i = 0; i < _size; ++i) {
        if (arr[_size - i - 1] != '0') {
            t = i;
            break;
        }
    }
    if (t == -1) {
        this->~Six();
        this->_size = 1;
        this->arr = new unsigned char[1]{'0'};
    } else {
        unsigned char * array = new unsigned char[this->_size - t];
        for (size_t i = 0; i < this->_size - t; ++i) {
            array[i] = arr[i];
        }
        _size -= t;
        arr = array;
    }
}

Six& Six::operator=(const Six& other)
{
    if (*this == other) {
        return *this;
    }
    
    _size  = other._size;
    arr = new unsigned char[_size];

    for(size_t i{0}; i < _size; ++i) arr[i] = other.arr[i];
    removeZeros();

    return *this;
}


bool Six::operator==(const Six& other) const
{
    if (_size!=other._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (this->arr[i] != other.arr[i]) {
            return false;
        }
    }
    return true;
}



bool Six::operator>(const Six& other) const
{
    if (_size > other._size) {
        return true;
    } else if (_size == other._size) {
        for (size_t i = 0; i < _size; ++i) {
            if (arr[_size - i - 1] > other.arr[_size - i - 1]) return true;
        }
    }
    return false;
}

bool Six::operator<(const Six& other) const
{
    return !((*this == other) || (*this > other));
}

Six Six::operator+(const Six& other)
{

    int s1 = this->_size;
    int s2 = other._size;
    int new_size = 0;
    if (this->_size > other._size) new_size = s1 + 1;
    else new_size = other._size + 1;
    Six res(1, '0');
    res.addZeros(new_size - 1);
    bool shift = false;
    int finDigit;
    for (size_t i = 0; i < new_size - 1; ++i) {
        if (shift) {
            if (this->_size <= i) {
                finDigit = other.arr[i] - '0' + 1;
            } else if (other._size <= i) {
                finDigit = this->arr[i] - '0' + 1;
            } else {
                finDigit = (this->arr[i] - '0') + (other.arr[i] - '0') + 1;
            }
            if (finDigit < 6) shift = false;
            res.arr[i] = (finDigit % 6) + '0';
        } else {
            if (this->_size <= i) {
                finDigit = other.arr[i] - '0';
            } else if (other._size <= i) {
                finDigit = this->arr[i] - '0';
            } else {
                finDigit = (this->arr[i] - '0') + (other.arr[i] - '0');
            }
            if (finDigit >= 6) shift = true;
            res.arr[i] = (finDigit % 6) + '0';
        }
    }
    if (shift) {
        res.arr[new_size - 1] = '1';
    }
    res.removeZeros();

    return res;
}


Six Six::operator-(const Six& other) const
{

    if(*this < other) throw std::underflow_error("unsigned six number can't be negative");
    Six res(*this);
    for (size_t i = 0; i < res._size; ++i) {
        if (i >= other._size) {
            break;
        }
        if (res.arr[i] >= other.arr[i]) {
            res.arr[i] = (res.arr[i] - other.arr[i]) + '0';
        } else {
            size_t j = i + 1;
            while (res.arr[j] == '0') {
                res.arr[j] += 5;
                ++j;
            }
            res.arr[j] = res.arr[j] - 1;
            res.arr[i] += 6;
            res.arr[i] = (res.arr[i] - other.arr[i]) + '0';
        }
    }
    res.removeZeros();
    return res;
}

Six Six::operator+=(const Six& other) {
        Six tmp  = *(this) + other;
        *(this) = tmp;

        return *(this);
    }

Six Six::operator-=(const Six& other) {
        Six tmp  = *(this) - other;
        *(this) = tmp;

        return *(this);
    }

std::ostream& operator<<(std::ostream& out, const Six& _this) //out overload
{
    for (size_t i = 0; i < _this._size; ++i) {
        out << _this.arr[_this._size - i - 1];
    }
    return out;
}  

std::istream& operator >> (std::istream& in, Six& _this) //in overload
{
    std::string input;
    in >> input;
    _this.arr = new unsigned char[input.size()];
    _this._size = input.size();
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] >= '6' || input[i] < '0') throw std::underflow_error("invalid symbol");
        _this.arr[input.size() - i - 1] = input[i];
    }
    _this.removeZeros();
    return in;
}


Six::~Six() noexcept  // Destructor
{
    if (_size > 0)
    {
        _size = 0;
        delete[] arr;
        arr = nullptr;
    }
}
