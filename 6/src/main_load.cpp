#include "gamemanager.h"
#include <iostream>
#include <string>
#include <limits>

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    GameManager game;
    std::string filename;
    double battleRange;
    
    try {
        std::cout << "Введите имя файла для загрузки NPC: ";
        std::getline(std::cin, filename);
        
        game.loadFromFile(filename);
        
        std::cout << "\nЗагруженные NPC:\n";
        game.printNPCs();
        
        std::cout << "\nВведите радиус боя (0-500): ";
        while (!(std::cin >> battleRange) || battleRange < 0 || battleRange > 500) {
            std::cout << "Неверный радиус. Введите число от 0 до 500: ";
            clearInputStream();
        }
        
        std::cout << "\nНачинаем бой с радиусом " << battleRange << ":\n";
        game.startBattle(battleRange);
        
        std::cout << "\nОставшиеся NPC:\n";
        game.printNPCs();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 