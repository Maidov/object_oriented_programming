#pragma once

#include <string>
#include <iostream>

class Six
{ 
public:
    Six();
    Six(const size_t & n, unsigned char t = '0');
    Six(const std::initializer_list< unsigned char> &t);
    Six(const std::string &t);
    Six(const Six& other);
    Six(Six&& other) noexcept;
    virtual ~Six() noexcept;

    int size();

    Six& operator=(const Six& other);
    bool operator==(const Six& other) const;
    bool operator>(const Six& other) const;
    bool operator<(const Six& other) const;
    Six operator+(const Six& other);
    Six operator-(const Six& other) const;
    Six operator+=(const Six& other);
    Six operator-=(const Six& other);

    // I/O overload
    friend std::ostream& operator<<(std::ostream &stream, const Six& Six);
    friend std::istream& operator>>(std::istream &stream, Six& Six);


private:
    void toString(std::string & s);
    void more0(int n);
    void less0();
    
    size_t _size;
    unsigned char *arr;
};
