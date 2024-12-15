#pragma once
#include <string>
#include <fstream>
#include <mutex>

class BattleObserver {
public:
    virtual ~BattleObserver() = default;
    virtual void onBattleEvent(const std::string& message) = 0;
};

class ConsoleObserver : public BattleObserver {
private:
    std::mutex cout_mutex;
public:
    void onBattleEvent(const std::string& message) override;
};

class FileObserver : public BattleObserver {
private:
    std::ofstream file;
    std::mutex file_mutex;
public:
    FileObserver();
    ~FileObserver();
    void onBattleEvent(const std::string& message) override;
}; 