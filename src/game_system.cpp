#include "game_system.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

Quest::Quest()
    : title("First Victory"), description("Defeat one enemy."), target(1),
      progress(0), completed(false) {}

Quest::Quest(const std::string& title, const std::string& description, int target)
    : title(title), description(description), target(target),
      progress(0), completed(false) {
    if (target <= 0) throw std::invalid_argument("Quest target must be positive.");
}

void Quest::addProgress(int amount) {
    if (amount < 0) throw std::invalid_argument("Quest progress cannot be negative.");
    progress += amount;
    if (progress >= target) {
        progress = target;
        completed = true;
    }
}
bool Quest::isCompleted() const { return completed; }
std::string Quest::getTitle() const { return title; }
void Quest::display() const {
    std::cout << "\nQuest: " << title << "\nDescription: " << description
              << "\nProgress: " << progress << '/' << target
              << "\nStatus: " << (completed ? "Completed" : "In progress") << '\n';
}

Achievement::Achievement() : title("First Blood"), description("Win a battle."), unlocked(false) {}
Achievement::Achievement(const std::string& title, const std::string& description)
    : title(title), description(description), unlocked(false) {}
void Achievement::unlock() { unlocked = true; }
void Achievement::display() const {
    std::cout << title << " - " << description << " ["
              << (unlocked ? "UNLOCKED" : "LOCKED") << "]\n";
}

GameLogger::GameLogger(const std::string& filename) : filename(filename) {}

void GameLogger::log(const std::string& message) const {
    std::ofstream out(filename, std::ios::app);
    if (!out) throw std::runtime_error("Could not open battle log.");
    out << message << '\n';
}

void GameLogger::showLog() const {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "No battle log found.\n";
        return;
    }
    std::string line;
    std::cout << "\n========== BATTLE LOG ==========\n";
    while (std::getline(in, line)) std::cout << line << '\n';
    std::cout << "================================\n";
}

// Demonstrates file input/output modes and file pointers (seekp).
void GameLogger::updateFirstLine(const std::string& message) const {
    std::fstream file(filename, std::ios::in | std::ios::out);
    if (!file) {
        log(message);
        return;
    }
    file.seekp(0, std::ios::beg);
    file << message;
}

SaveManager::SaveManager(const std::string& filename) : filename(filename) {}

void SaveManager::save(const Character& character, const Inventory& inventory) const {
    std::ofstream out(filename, std::ios::out | std::ios::trunc);
    if (!out) throw std::runtime_error("Could not open save file.");
    out << std::quoted(character.getName()) << '\n'
        << character.getHealth() << '\n'
        << inventory.getGold() << '\n'
        << inventory.getPotionCount() << '\n'
        << std::quoted(inventory.getWeapon().getName()) << '\n'
        << inventory.getWeapon().getDamage() << '\n';
    std::cout << "Game saved successfully.\n";
}

bool SaveManager::load(Character& character, Inventory& inventory) const {
    std::ifstream in(filename, std::ios::in);
    if (!in) return false;

    std::string savedName, weaponName;
    int savedHealth, savedGold, potionCount, weaponDamage;

    if (!(in >> std::quoted(savedName) >> savedHealth >> savedGold
             >> potionCount >> std::quoted(weaponName) >> weaponDamage))
        throw std::runtime_error("Save file is corrupted.");

    character.setName(savedName);
    character.setHealth(savedHealth);
    inventory.addGold(savedGold);
    inventory.getWeapon() = Weapon(weaponName, weaponDamage);

    for (int i = 0; i < potionCount; ++i)
        inventory.addPotion(Potion("Saved Potion", 20));

    std::cout << "Game loaded successfully.\n";
    return true;
}

void Shop::display() const {
    std::cout << "\n========== SHOP ==========\n"
              << "1. Small Potion (20 HP) - 10 gold\n"
              << "2. Large Potion (40 HP) - 20 gold\n"
              << "3. Iron Sword (+15 damage) - 30 gold\n"
              << "==========================\n";
}

void Shop::buyPotion(Inventory& inventory) const {
    std::cout << "1. Small Potion (10 gold)\n2. Large Potion (20 gold)\n";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid shop input.");
    }

    int price = (choice == 1) ? 10 : (choice == 2 ? 20 : 0);
    if (price == 0) throw std::invalid_argument("Invalid potion selection.");
    if (inventory.getPotionCount() >= 5)
        throw std::runtime_error("Potion storage is full.");

    if (!inventory.spendGold(price)) {
        std::cout << "Not enough gold.\n";
        return;
    }

    Potion potion = (choice == 1) ? Potion("Small Potion", 20)
                                  : Potion("Large Potion", 40);
    if (!inventory.addPotion(potion)) {
        inventory.addGold(price);
        throw std::runtime_error("Could not add potion.");
    }
    std::cout << "Potion purchased!\n";
}

void Shop::buyWeapon(Inventory& inventory) const {
    const int price = 30;
    if (!inventory.spendGold(price)) {
        std::cout << "Not enough gold for an Iron Sword.\n";
        return;
    }
    inventory.getWeapon() = Weapon("Iron Sword", 15);
    std::cout << "Iron Sword equipped!\n";
}
