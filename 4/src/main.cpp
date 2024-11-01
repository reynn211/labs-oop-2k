#include <iostream>
#include "array.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить трапецию\n";
        std::cout << "2. Добавить ромб\n";
        std::cout << "3. Добавить пятиугольник\n";
        std::cout << "4. Вывести все фигуры\n";
        std::cout << "5. Удалить фигуру по индексу\n";
        std::cout << "6. Показать общую площадь\n";
        std::cout << "0. Выход\n";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                auto trapezoid = std::make_shared<Trapezoid<double>>();
                std::cout << "Введите координаты 4 вершин (x y):\n";
                std::cin >> *trapezoid;
                figures.push_back(trapezoid);
                break;
            }
            case 2: {
                auto rhombus = std::make_shared<Rhombus<double>>();
                std::cout << "Введите координаты 4 вершин (x y):\n";
                std::cin >> *rhombus;
                figures.push_back(rhombus);
                break;
            }
            case 3: {
                auto pentagon = std::make_shared<Pentagon<double>>();
                std::cout << "Введите координаты 5 вершин (x y):\n";
                std::cin >> *pentagon;
                figures.push_back(pentagon);
                break;
            }
            case 4: {
                for (size_t i = 0; i < figures.size(); ++i) {
                    std::cout << "\nФигура " << i + 1 << " (" << figures[i]->getName() << "):\n";
                    std::cout << *figures[i];
                    auto center = figures[i]->getCenter();
                    std::cout << "\nЦентр: " << center;
                    std::cout << "\nПлощадь: " << static_cast<double>(*figures[i]) << "\n";
                }
                break;
            }
            case 5: {
                size_t index;
                std::cout << "Введите индекс фигуры для удаления: ";
                std::cin >> index;
                try {
                    figures.remove(index);
                    std::cout << "Фигура удалена\n";
                } catch (const std::out_of_range& e) {
                    std::cout << "Неверный индекс\n";
                }
                break;
            }
            case 6: {
                double totalArea = 0;
                for (size_t i = 0; i < figures.size(); ++i) {
                    totalArea += static_cast<double>(*figures[i]);
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