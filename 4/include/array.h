#pragma once
#include <memory>
#include <stdexcept>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        auto new_data = std::make_shared<T[]>(new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    Array() : data_(nullptr), size_(0), capacity_(0) {}
    
    size_t size() const { return size_; }
    
    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Индекс выходит за пределы массива");
        }
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Индекс выходит за пределы массива");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Индекс выходит за пределы массива");
        }
        return data_[index];
    }
}; 