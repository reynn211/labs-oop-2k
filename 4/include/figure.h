#pragma once
#include "point.h"
#include <memory>
#include <vector>
#include <typeinfo>
#include <string>

template<Scalar T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices_;

public:
    Figure() = default;
    
    Figure(const Figure& other) {
        vertices_.reserve(other.vertices_.size());
        for (const auto& vertex : other.vertices_) {
            vertices_.push_back(std::make_unique<Point<T>>(vertex->x(), vertex->y()));
        }
    }
    
    virtual ~Figure() = default;
    
    virtual Point<T> getCenter() const = 0;
    virtual double getArea() const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    virtual std::string getName() const = 0;
    
    Figure& operator=(const Figure& other) {
        if (this != &other) {
            vertices_.clear();
            vertices_.reserve(other.vertices_.size());
            for (const auto& vertex : other.vertices_) {
                vertices_.push_back(std::make_unique<Point<T>>(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Figure& operator=(Figure&& other) noexcept {
        if (this != &other) {
            vertices_ = std::move(other.vertices_);
        }
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        for (const auto& point : fig.vertices_) {
            os << *point << " ";
        }
        return os;
    }
    
    virtual operator double() const {
        return getArea();
    }
}; 