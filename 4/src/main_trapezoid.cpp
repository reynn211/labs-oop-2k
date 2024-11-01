#include <iostream>
#include "array.h"
#include "trapezoid.h"

int main() {
    Array<Trapezoid<double>> trapezoids;
    
    while (true) {
        std::cout << "\nМеню для работы с трапециями:\n";
        std::cout << "1. Добавить трапецию\n";
        std::cout << "2. Вывести все трапеции\n";
        std::cout << "3. Удалить трапецию по индексу\n";
        std::cout << "4. Показать общую площадь\n";
        std::cout << "0. Выход\n";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                Trapezoid<double> trapezoid;
                std::cout << "Введите координаты 4 вершин (x y):\n";
                std::cin >> trapezoid;
                trapezoids.push_back(trapezoid);
                break;
            }
            case 2: {
                for (size_t i = 0; i < trapezoids.size(); ++i) {
                    std::cout << "\nТрапеция " << i + 1 << ":\n";
                    std::cout << trapezoids[i];
                    auto center = trapezoids[i].getCenter();
                    std::cout << "\nЦентр: " << center;
                    std::cout << "\nПлощадь: " << static_cast<double>(trapezoids[i]) << "\n";
                }
                break;
            }
            case 3: {
                size_t index;
                std::cout << "Введите индекс трапеции для удаления: ";
                std::cin >> index;
                try {
                    trapezoids.remove(index);
                    std::cout << "Трапеция удалена\n";
                } catch (const std::out_of_range& e) {
                    std::cout << "Неверный индекс\n";
                }
                break;
            }
            case 4: {
                double totalArea = 0;
                for (size_t i = 0; i < trapezoids.size(); ++i) {
                    totalArea += static_cast<double>(trapezoids[i]);
                }
                std::cout << "Общая площадь: " << totalArea << "\n";
                break;
            }
            default:
                std::cout << "Неверный выбор\n";
        }
    }
    
    return 0;
} 