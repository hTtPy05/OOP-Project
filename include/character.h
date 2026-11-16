#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

class Character {
protected:
    std::string name;
    int health;
    int attackPower;
    int abilities[3];

    static int characterCount;

public:
    Character();
    Character(const std::string& name, int health, int attackPower);
    Character(const Character& other);
    virtual ~Character();

    inline std::string getName() const { return name; }
    inline int getHealth() const { return health; }
    inline int getAttackPower() const { return attackPower; }

    int& healthReference();
    void setName(const std::string& name);
    void setHealth(int health);

    virtual void attack() = 0;
    virtual std::string getClassName() const = 0;

    void heal(int amount);
    void heal(int amount, const std::string& reason);
    void takeDamage(int damage);
    bool isAlive() const;

    bool operator>(const Character& other) const;
    operator int() const;

    static int getCharacterCount();

    friend void displayCharacterStats(const Character& character);
};

class Warrior : public Character {
public:
    explicit Warrior(const std::string& name = "Warrior");
    Warrior(const Warrior& other);
    void attack() override;
    std::string getClassName() const override;
};

class Mage : public Character {
public:
    explicit Mage(const std::string& name = "Mage");
    Mage(const Mage& other);
    void attack() override;
    std::string getClassName() const override;
};

class Archer : public Character {
public:
    explicit Archer(const std::string& name = "Archer");
    Archer(const Archer& other);
    void attack() override;
    std::string getClassName() const override;
};

#endif
