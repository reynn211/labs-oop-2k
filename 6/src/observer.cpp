#include "observer.h"
#include <iostream>

void ConsoleObserver::onBattleEvent(const std::string& message) {
    std::cout << "Событие боя: " << message << std::endl;
}

FileObserver::FileObserver() {
    file.open("log.txt", std::ios::app);
}

FileObserver::~FileObserver() {
    if (file.is_open()) {
        file.close();
    }
}

void FileObserver::onBattleEvent(const std::string& message) {
    if (file.is_open()) {
        file << "Событие боя: " << message << std::endl;
    }
} 