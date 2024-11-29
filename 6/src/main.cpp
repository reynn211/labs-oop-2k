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
    double battleRange;
    
    try {
        game.addNPC("Knight", "Arthur", 100, 100);
        game.addNPC("Druid", "Merlin", 150, 150);
        game.addNPC("Elf", "Legolas", 120, 120);
        game.addNPC("Knight", "Lancelot", 200, 200);
        game.addNPC("Druid", "Gandalf", 250, 250);
        
        std::cout << "Изначальные NPC:\n";
        game.printNPCs();
        
        game.saveToFile("game_state.txt");
        
        std::cout << "\nВведите радиус битвы (0-500): ";
        while (!(std::cin >> battleRange) || battleRange < 0 || battleRange > 500) {
            std::cout << "Неверный радиус. Введите число от 0 до 500: ";
            clearInputStream();
        }
        
        std::cout << "\nНачинаем битву с радиусом " << battleRange << ":\n";
        game.startBattle(battleRange);
        
        std::cout << "\nОставшиеся NPC:\n";
        game.printNPCs();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 