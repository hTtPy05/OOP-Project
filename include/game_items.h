#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H

#include <iostream>
#include <string>

class Weapon {
private:
    std::string name;
    int damage;

public:
    Weapon();
    Weapon(const std::string& name, int damage);
    std::string getName() const;
    int getDamage() const;
    void upgrade(int bonus);
    void display() const;
    bool operator==(const Weapon& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Weapon& weapon);
};

class Potion {
private:
    std::string name;
    int healingPower;

public:
    Potion();
    Potion(const std::string& name, int healingPower);
    std::string getName() const;
    int getHealingPower() const;
    void display() const;
};

class Inventory {
private:
    Potion* potions;
    int potionCount;
    int capacity;
    int gold;
    Weapon* equippedWeapon;

public:
    explicit Inventory(int capacity = 5);
    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);
    ~Inventory();

    bool addPotion(const Potion& potion);
    bool usePotion(class Character& character);
    void addGold(int amount);
    bool spendGold(int amount);
    int getGold() const;
    int getPotionCount() const;
    Weapon& getWeapon();
    const Weapon& getWeapon() const;
    void showInventory() const;
};

#endif
