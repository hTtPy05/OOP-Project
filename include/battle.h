#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "game_items.h"
#include "game_system.h"

class Enemy {
private:
    std::string name;
    int health;
    int attackPower;
    int rewardGold;

public:
    Enemy();
    Enemy(const std::string& name, int health, int attackPower, int rewardGold = 10);
    void attack(Character& player) const;
    void takeDamage(int damage);
    bool isAlive() const;
    std::string getName() const;
    int getHealth() const;
    int getRewardGold() const;
};

class Battle {
private:
    Enemy enemyRoster[3];

public:
    Battle();
    void start(Character& player, Inventory& inventory,
               Quest& quest, Achievement& achievement,
               GameLogger& logger);
};

#endif
