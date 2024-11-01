#pragma once
#include <concepts>
#include <iostream>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
private:
    T x_;
    T y_;

public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}
    
    T x() const { return x_; }
    T y() const { return y_; }

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << "(" << point.x_ << ", " << point.y_ << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point<T>& point) {
        is >> point.x_ >> point.y_;
        return is;
    }
}; 