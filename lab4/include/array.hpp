
#include "array.h"
template <typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(2) {
    data = std::make_unique<T[]>(capacity);
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t initialSize) : size(initialSize), capacity(2*initialSize) {
    data = std::make_unique<T[]>(capacity);
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    size = 0;
    capacity = 0;
}

template <typename T>
T* DynamicArray<T>::begin() {
        return data.get();
    }
template <typename T>
T* DynamicArray<T>::end() {
        return data.get() + size;
    }

template <typename T>
T& DynamicArray<T>::operator[](size_t index) const{
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&other) noexcept {
    size = other.size;
    capacity = other.capacity;
    data = std::move(other.data);
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &other) {
    size = other.size;
    capacity = other.capacity;
    data = std::make_unique<T[]>(capacity);
    for (int i = 0; i < other.size(); i++) {
        data[i] = other[i];
    }
}

template <typename T>
void DynamicArray<T>::pushBack(T& element) {
    if (size >= capacity) {
        capacity *= 2;
        std::unique_ptr<T[]> newArray = std::make_unique<T[]>(capacity);
        for (int i = 0; i < size; i++) {
            newArray[i] = data[i];
        }
        data = std::move(newArray);
    }
    data[size++] = element;
}

template <typename T>
void DynamicArray<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
        return;
    }

    data[index] = T();  // Заменяет элемент на значение по умолчанию для типа T
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const DynamicArray<T>& arr) {
    for (size_t i = 0; i < arr.getSize(); ++i) {
        out << *arr[i] << "\n";
    }
    return out;
}


template <typename T>
double findSumAreas(DynamicArray<T> &arr)
{
    double result = 0;
    for (size_t i = 0; i < arr.getSize(); i++) {
        result += double(*arr[i]);
    }
    return result;
}
//enable_if
template <typename T>
void findAllCenters(DynamicArray<T> &arr) {
    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << (*arr[i]).findCenter() << '\n';
    }
}
template <typename T>
void findAllAreas(DynamicArray<T> &arr) {
    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << double(*arr[i]) << '\n';
    }
}