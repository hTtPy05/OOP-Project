#include "game_items.h"
#include "character.h"
#include <algorithm>
#include <stdexcept>

Weapon::Weapon() : name("Wooden Sword"), damage(5) {}
Weapon::Weapon(const std::string& name, int damage) : name(name), damage(damage) {
    if (damage < 0) throw std::invalid_argument("Weapon damage cannot be negative.");
}
std::string Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
void Weapon::upgrade(int bonus) {
    if (bonus < 0) throw std::invalid_argument("Upgrade bonus cannot be negative.");
    damage += bonus;
}
void Weapon::display() const {
    std::cout << name << " (+" << damage << " damage)\n";
}
bool Weapon::operator==(const Weapon& other) const {
    return name == other.name && damage == other.damage;
}
std::ostream& operator<<(std::ostream& out, const Weapon& weapon) {
    out << weapon.name << " (damage " << weapon.damage << ')';
    return out;
}

Potion::Potion() : name("Small Potion"), healingPower(20) {}
Potion::Potion(const std::string& name, int healingPower)
    : name(name), healingPower(healingPower) {
    if (healingPower <= 0) throw std::invalid_argument("Potion healing must be positive.");
}
std::string Potion::getName() const { return name; }
int Potion::getHealingPower() const { return healingPower; }
void Potion::display() const {
    std::cout << name << " (heals " << healingPower << " HP)\n";
}

// Dynamic constructor: allocates a dynamic array of Potion objects and a Weapon.
Inventory::Inventory(int capacity)
    : potions(nullptr), potionCount(0), capacity(capacity), gold(50),
      equippedWeapon(nullptr) {
    if (capacity <= 0) throw std::invalid_argument("Inventory capacity must be positive.");
    potions = new Potion[capacity];
    equippedWeapon = new Weapon("Training Sword", 5);
}

Inventory::Inventory(const Inventory& other)
    : potions(new Potion[other.capacity]), potionCount(other.potionCount),
      capacity(other.capacity), gold(other.gold),
      equippedWeapon(new Weapon(*other.equippedWeapon)) {
    for (int i = 0; i < potionCount; ++i) potions[i] = other.potions[i];
}

Inventory& Inventory::operator=(const Inventory& other) {
    if (this != &other) {
        Potion* newPotions = new Potion[other.capacity];
        for (int i = 0; i < other.potionCount; ++i)
            newPotions[i] = other.potions[i];

        Weapon* newWeapon = new Weapon(*other.equippedWeapon);

        delete[] potions;
        delete equippedWeapon;

        potions = newPotions;
        equippedWeapon = newWeapon;
        potionCount = other.potionCount;
        capacity = other.capacity;
        gold = other.gold;
    }
    return *this;
}

Inventory::~Inventory() {
    delete[] potions;
    delete equippedWeapon;
}

bool Inventory::addPotion(const Potion& potion) {
    if (potionCount >= capacity) return false;
    potions[potionCount++] = potion;
    return true;
}

bool Inventory::usePotion(Character& character) {
    if (potionCount == 0) {
        std::cout << "No potions available!\n";
        return false;
    }
    if (!character.isAlive()) {
        std::cout << "A defeated character cannot use a potion.\n";
        return false;
    }

    --potionCount;
    character.heal(potions[potionCount].getHealingPower(), "Potion restored your health!");
    return true;
}

void Inventory::addGold(int amount) {
    if (amount < 0) throw std::invalid_argument("Gold cannot be negative.");
    gold += amount;
}

bool Inventory::spendGold(int amount) {
    if (amount < 0) throw std::invalid_argument("Purchase amount cannot be negative.");
    if (gold < amount) return false;
    gold -= amount;
    return true;
}

int Inventory::getGold() const { return gold; }
int Inventory::getPotionCount() const { return potionCount; }
Weapon& Inventory::getWeapon() { return *equippedWeapon; }
const Weapon& Inventory::getWeapon() const { return *equippedWeapon; }

void Inventory::showInventory() const {
    std::cout << "\n========== INVENTORY ==========\n"
              << "Gold: " << gold << '\n'
              << "Potions: " << potionCount << '/' << capacity << '\n'
              << "Equipped weapon: " << *equippedWeapon << '\n'
              << "===============================\n";
}
