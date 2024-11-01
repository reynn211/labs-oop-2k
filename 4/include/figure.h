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
    Figure(size_t vertex_count = 0) {
        for (size_t i = 0; i < vertex_count; ++i) {
            vertices_.push_back(std::make_unique<Point<T>>(0, 0));
        }
    }
    
    Figure(const Figure& other) {
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