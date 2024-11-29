#pragma once
#include <string>
#include <fstream>

class BattleObserver {
public:
    virtual ~BattleObserver() = default;
    virtual void onBattleEvent(const std::string& message) = 0;
};

class ConsoleObserver : public BattleObserver {
public:
    void onBattleEvent(const std::string& message) override;
};

class FileObserver : public BattleObserver {
private:
    std::ofstream file;
public:
    FileObserver();
    ~FileObserver();
    void onBattleEvent(const std::string& message) override;
}; 