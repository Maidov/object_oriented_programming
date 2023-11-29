#include <cstddef>
#include <memory>
#include <iostream>
#include "allocator.h"

// Динамический массив с параметризуемым аллокатором
template <typename T, typename Allocator = PoolAllocator<T>>
class Vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;

    Vector() : data(nullptr), size(0), capacity(0), allocator() {}

    ~Vector() {
        clear();
        v_deallocate();
    }

    void push_back(const T& value) {
        if (size == capacity) {
            // Если достигнут лимит capacity, увеличиваем его
            if (capacity == 0) {v_reserve(1);}
            else {v_reserve(capacity * 2);}
        }

        // Вызываем конструктор копирования для нового элемента
        allocator.construct(data + size, value);
        ++size;
    }

    size_type get_size() const {
        return size;
    }

    size_type get_capacity() const {
        return capacity;
    }

    void clear() {
        for (size_type i = 0; i < size; ++i) {
            // Вызываем деструктор для каждого элемента
            allocator.destroy(data + i);
        }
        size = 0;
    }

    value_type& operator[](std::size_t index){
        if ((index >= size) || (index < 0)) { throw std::out_of_range("Index out of range"); }
        return data[index];
    }

    const value_type& operator[](std::size_t index) const{
        if ((index >= size) || (index < 0)) { throw std::out_of_range("Index out of range"); }
        return data[index];
    }


    class Iterator : public std::iterator<std::forward_iterator_tag, T>{
        friend class List;
    private:
        T *item;
    public:
        
        Iterator(T* ptr) : item(ptr){}

        Iterator(Iterator &other) : item(other.item) {}

        Iterator(Iterator &&other) noexcept {
            item = std::move(other.item);
        }

        ~Iterator() = default;
        bool operator==(const Iterator& other) const{
            return item == other.item;
        }

        bool operator!=(const Iterator& other) const{
            return !(item == other.item);
        }

        value_type& operator*() const{
            return *item;
        }

        Iterator& operator++() {
            ++item;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        T* operator->() const{
            return item;
        }
        
        Iterator operator=(const Iterator& other) {
            item = other.item;
            return *this;
        }

        Iterator& operator =(Iterator &&other) noexcept{
            item = std::move(other.item);
            return *this;
        }

    };
    

    class ConstIterator : public std::iterator<std::forward_iterator_tag, T>{
        friend class List;
    private:
        T *item;
    public:
        
        ConstIterator(T* ptr) : item(ptr){}

        ConstIterator(ConstIterator &other) : item(other.item) {}

        ConstIterator(ConstIterator &&other) noexcept {
            item = std::move(other.item);
        }

        ~ConstIterator() = default;
        bool operator==(const ConstIterator& other) const{
            return item == other.item;
        }

        bool operator!=(const ConstIterator& other) const{
            return !(item == other.item);
        }

        value_type& operator*() const{
            return *item;
        }

        ConstIterator& operator++() {
            ++item;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        T* operator->() const{
            return item;
        }
        
        ConstIterator operator=(const ConstIterator& other) {
            item = other.item;
            return *this;
        }

        ConstIterator& operator =(ConstIterator &&other) noexcept{
            item = std::move(other.item);
            return *this;
        }

    };


    Iterator begin() const{
        return(Iterator(data));
    }

    Iterator end() const{
        return(Iterator(data + size));
    }

    ConstIterator cbegin() const{
        return(ConstIterator(data));
    }

    ConstIterator cend() const{
        return(ConstIterator(data + size));
    }

private:
    pointer data;          // Указатель на начало массива
    size_type size;        // Текущий размер массива
    size_type capacity;    // Емкость массива
    PoolAllocator<T> allocator;  // Аллокатор

    void v_allocate(size_type new_capacity) {
        data = allocator.allocate(new_capacity);
        capacity = new_capacity;
    }

    void v_deallocate() {
        if (data != nullptr){
            allocator.deallocate(data, capacity);
            data = nullptr;
            capacity = 0;
        }
    }

    void v_reserve(size_type new_capacity) {
        if (new_capacity > capacity) {
            
            pointer new_data = allocator.allocate(new_capacity);
            // Копируем существующие элементы в новый массив
            for (size_type i = 0; i < size; ++i) {
                
                allocator.construct(new_data + i, std::move(data[i]));
                allocator.destroy(data + i);
            }
            if (capacity != 0){allocator.deallocate(data, capacity);}
            // Освобождаем старую память и обновляем указатель на новую
            data = new_data;
            capacity = new_capacity;
        }
    }

};


// DONT PUT METHODS SEPARATELY COUZE USINGS WILL FAILED