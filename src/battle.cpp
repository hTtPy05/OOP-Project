#include "battle.h"
#include <iostream>
#include <limits>

Enemy::Enemy() : name("Training Dummy"), health(1), attackPower(0), rewardGold(0) {}

Enemy::Enemy(const std::string& name, int health, int attackPower, int rewardGold)
    : name(name), health(health), attackPower(attackPower), rewardGold(rewardGold) {}

void Enemy::attack(Character& player) const {
    std::cout << name << " attacks!\n";
    player.takeDamage(attackPower);
}

void Enemy::takeDamage(int damage) {
    if (damage < 0) throw std::invalid_argument("Damage cannot be negative.");
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << " received " << damage << " damage.\n";
}

bool Enemy::isAlive() const { return health > 0; }
std::string Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
int Enemy::getRewardGold() const { return rewardGold; }

// Array of Enemy objects is maintained inside Battle.
Battle::Battle()
    : enemyRoster{
        Enemy("Goblin", 70, 10, 15),
        Enemy("Orc", 100, 15, 25),
        Enemy("Dragon", 150, 20, 50)
    } {}

void Battle::start(Character& player, Inventory& inventory,
                   Quest& quest, Achievement& achievement,
                   GameLogger& logger) {
    std::cout << "\n========== BATTLE ARENA ==========\n";

    for (Enemy& enemy : enemyRoster) {
        if (!player.isAlive()) break;

        std::cout << "\n" << player.getName() << " VS " << enemy.getName() << '\n';
        logger.log("Battle started: " + player.getName() + " vs " + enemy.getName());

        while (player.isAlive() && enemy.isAlive()) {
            std::cout << "\n--------------------------------\n"
                      << player.getName() << " Health: " << player.getHealth() << '\n'
                      << enemy.getName() << " Health: " << enemy.getHealth() << '\n'
                      << "1. Attack\n2. Use potion\n3. Show inventory\n"
                      << "Enter choice: ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input!\n";
                continue;
            }

            if (choice == 1) {
                player.attack();
                int damage = player.getAttackPower() + inventory.getWeapon().getDamage();
                enemy.takeDamage(damage);
                logger.log(player.getName() + " dealt " + std::to_string(damage)
                           + " damage to " + enemy.getName());
            } else if (choice == 2) {
                inventory.usePotion(player);
            } else if (choice == 3) {
                inventory.showInventory();
                continue;
            } else {
                std::cout << "Invalid choice!\n";
                continue;
            }

            if (enemy.isAlive() && player.isAlive()) enemy.attack(player);
        }

        if (player.isAlive() && !enemy.isAlive()) {
            std::cout << "You defeated " << enemy.getName() << "!\n";
            inventory.addGold(enemy.getRewardGold());
            quest.addProgress();
            logger.log(enemy.getName() + " defeated. Reward gold: "
                       + std::to_string(enemy.getRewardGold()));
        }
    }

    if (player.isAlive()) {
        std::cout << "\nYou survived the arena!\n";
        achievement.unlock();
        logger.log(player.getName() + " completed the arena.");
    } else {
        std::cout << "\nGame over. Your character was defeated.\n";
        logger.log(player.getName() + " was defeated.");
    }

    quest.display();
    achievement.display();
}
