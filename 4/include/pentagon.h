#pragma once
#include "figure.h"
#include <cmath>

template<Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() : Figure<T>(5) {}
    
    std::unique_ptr<Figure<T>> clone() const override {
        auto new_pentagon = std::make_unique<Pentagon<T>>();
        for (size_t i = 0; i < this->vertices_.size(); ++i) {
            new_pentagon->vertices_[i] = std::make_unique<Point<T>>(
                this->vertices_[i]->x(),
                this->vertices_[i]->y()
            );
        }
        return new_pentagon;
    }
    
    Point<T> getCenter() const override {
        T x_sum = 0;
        T y_sum = 0;
        for (const auto& vertex : this->vertices_) {
            x_sum += vertex->x();
            y_sum += vertex->y();
        }
        return Point<T>(x_sum / 5, y_sum / 5);
    }
    
    double getArea() const override {
        double area = 0;
        for (size_t i = 0; i < 5; ++i) {
            size_t j = (i + 1) % 5;
            area += this->vertices_[i]->x() * this->vertices_[j]->y();
            area -= this->vertices_[j]->x() * this->vertices_[i]->y();
        }
        return std::abs(area) / 2.0;
    }
    
    friend std::istream& operator>>(std::istream& is, Pentagon<T>& pentagon) {
        for (size_t i = 0; i < 5; ++i) {
            T x, y;
            is >> x >> y;
            pentagon.vertices_[i] = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }
    
    std::string getName() const override {
        return "Пятиугольник";
    }
}; 