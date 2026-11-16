#include "character.h"
#include <algorithm>

int Character::characterCount = 0;

Character::Character()
    : name("Unknown"), health(100), attackPower(10), abilities{10, 10, 10} {
    ++characterCount;
}

Character::Character(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower),
      abilities{attackPower, health / 2, 5} {
    ++characterCount;
}

Character::Character(const Character& other)
    : name(other.name), health(other.health), attackPower(other.attackPower),
      abilities{other.abilities[0], other.abilities[1], other.abilities[2]} {
    ++characterCount;
}

Character::~Character() {
    --characterCount;
    std::cout << name << " character destroyed.\n";
}

int& Character::healthReference() {
    return health;
}

void Character::setName(const std::string& name) {
    this->name = name;
}

void Character::setHealth(int health) {
    if (health < 0 || health > 100)
        throw std::out_of_range("Health must be between 0 and 100.");
    this->health = health;
}

void Character::heal(int amount) {
    if (amount < 0) throw std::invalid_argument("Healing cannot be negative.");
    health = std::min(100, health + amount);
}

void Character::heal(int amount, const std::string& reason) {
    heal(amount);
    std::cout << reason << '\n';
}

void Character::takeDamage(int damage) {
    if (damage < 0) throw std::invalid_argument("Damage cannot be negative.");
    health = std::max(0, health - damage);
    std::cout << name << " received " << damage << " damage.\n";
}

bool Character::isAlive() const {
    return health > 0;
}

bool Character::operator>(const Character& other) const {
    return (health + attackPower) > (other.health + other.attackPower);
}

Character::operator int() const {
    return health + attackPower;
}

int Character::getCharacterCount() {
    return characterCount;
}

void displayCharacterStats(const Character& character) {
    std::cout << "\n===== CHARACTER STATISTICS =====\n"
              << "Name: " << character.name << '\n'
              << "Class: " << character.getClassName() << '\n'
              << "Health: " << character.health << '\n'
              << "Attack power: " << character.attackPower << '\n'
              << "Abilities: ";
    for (int ability : character.abilities) std::cout << ability << ' ';
    std::cout << "\n================================\n";
}

Warrior::Warrior(const std::string& name) : Character(name, 100, 25) {}
Warrior::Warrior(const Warrior& other) : Character(other) {}
void Warrior::attack() {
    std::cout << name << " performs a powerful sword attack!\n";
}
std::string Warrior::getClassName() const { return "Warrior"; }

Mage::Mage(const std::string& name) : Character(name, 80, 35) {}
Mage::Mage(const Mage& other) : Character(other) {}
void Mage::attack() {
    std::cout << name << " casts a powerful fireball!\n";
}
std::string Mage::getClassName() const { return "Mage"; }

Archer::Archer(const std::string& name) : Character(name, 90, 30) {}
Archer::Archer(const Archer& other) : Character(other) {}
void Archer::attack() {
    std::cout << name << " shoots a sharp arrow!\n";
}
std::string Archer::getClassName() const { return "Archer"; }
