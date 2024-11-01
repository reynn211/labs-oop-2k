#pragma once
#include "figure.h"
#include <cmath>

template<Scalar T>
class Rhombus : public Figure<T> {
public:
    Rhombus() {
        for (size_t i = 0; i < 4; ++i) {
            this->vertices_.push_back(std::make_unique<Point<T>>(0, 0));
        }
    }

    Rhombus(const Rhombus& other) : Figure<T>(other) {}
    
    Rhombus& operator=(const Rhombus& other) {
        Figure<T>::operator=(other);
        return *this;
    }
    
    Rhombus& operator=(Rhombus&& other) noexcept {
        Figure<T>::operator=(std::move(other));
        return *this;
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        auto new_rhombus = std::make_unique<Rhombus<T>>();
        for (size_t i = 0; i < this->vertices_.size(); ++i) {
            new_rhombus->vertices_[i] = std::make_unique<Point<T>>(
                this->vertices_[i]->x(),
                this->vertices_[i]->y()
            );
        }
        return new_rhombus;
    }
    
    Point<T> getCenter() const override {
        T x_sum = 0;
        T y_sum = 0;
        for (const auto& vertex : this->vertices_) {
            x_sum += vertex->x();
            y_sum += vertex->y();
        }
        return Point<T>(x_sum / 4, y_sum / 4);
    }
    
    double getArea() const override {
        T d1 = std::sqrt(std::pow(this->vertices_[2]->x() - this->vertices_[0]->x(), 2) + 
                        std::pow(this->vertices_[2]->y() - this->vertices_[0]->y(), 2));
        T d2 = std::sqrt(std::pow(this->vertices_[3]->x() - this->vertices_[1]->x(), 2) + 
                        std::pow(this->vertices_[3]->y() - this->vertices_[1]->y(), 2));
        return (d1 * d2) / 2.0;
    }
    
    friend std::istream& operator>>(std::istream& is, Rhombus<T>& rhombus) {
        for (size_t i = 0; i < 4; ++i) {
            T x, y;
            is >> x >> y;
            rhombus.vertices_[i] = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }
    
    std::string getName() const override {
        return "Ромб";
    }
}; 