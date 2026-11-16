#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include "character.h"
#include "game_items.h"
#include <string>

class Quest {
private:
    std::string title;
    std::string description;
    int target;
    int progress;
    bool completed;

public:
    Quest();
    Quest(const std::string& title, const std::string& description, int target);
    void addProgress(int amount = 1);
    bool isCompleted() const;
    std::string getTitle() const;
    void display() const;
};

class Achievement {
private:
    std::string title;
    std::string description;
    bool unlocked;

public:
    Achievement();
    Achievement(const std::string& title, const std::string& description);
    void unlock();
    void display() const;
};

class GameLogger {
private:
    std::string filename;

public:
    explicit GameLogger(const std::string& filename = "data/battle_log.txt");
    void log(const std::string& message) const;
    void showLog() const;
    void updateFirstLine(const std::string& message) const;
};

class SaveManager {
private:
    std::string filename;

public:
    explicit SaveManager(const std::string& filename = "data/save.txt");
    void save(const Character& character, const Inventory& inventory) const;
    bool load(Character& character, Inventory& inventory) const;
};

class Shop {
public:
    void display() const;
    void buyPotion(Inventory& inventory) const;
    void buyWeapon(Inventory& inventory) const;
};

#endif
