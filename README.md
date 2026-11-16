# Mini RPG Battle Game — C++ OOP Project

An expanded console RPG game designed to demonstrate the practical C++ concepts in the six-unit OOP syllabus.

## Requirements

- C++17 compiler (GCC or Clang)
- `make` is optional

## Compile and run on macOS/Linux

From the `MiniRPG` directory:

```bash
make
./mini_rpg
```

Or compile manually:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/character.cpp src/game_items.cpp src/game_system.cpp src/battle.cpp -o mini_rpg
./mini_rpg
```

## Windows (MinGW)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/character.cpp src/game_items.cpp src/game_system.cpp src/battle.cpp -o mini_rpg.exe
mini_rpg.exe
```

## Classes

Original gameplay classes retained:
- `Character` (abstract base)
- `Warrior`, `Mage`, `Archer`
- `Enemy`
- `Inventory`
- `Battle`

New classes:
- `Weapon`
- `Potion`
- `Quest`
- `Achievement`
- `Shop`
- `GameLogger`
- `SaveManager`

## Features

- Choose Warrior, Mage or Archer.
- Fight three enemies in sequence.
- Use potions and weapon damage.
- Earn gold from defeated enemies.
- Buy potions and weapons from the shop.
- Track a quest and unlock an achievement.
- Save and load player progress.
- Record and display battle logs.
- Update the first line of the battle log using file positioning.

## Syllabus mapping

| Unit | Topic | Implementation |
|---|---|---|
| 1 | OOP paradigm, classes, objects, abstraction, encapsulation, inheritance, polymorphism | Overall design; abstract `Character`; derived player classes |
| 2 | Tokens, keywords, identifiers, constants, data types, variables, operators, precedence, control structures | Throughout the program; menu and battle loops |
| 2 | Type compatibility and implicit conversion | Ordinary arithmetic and stream expressions; integer conversion where applicable |
| 2 | Operator overloading | `Character::operator>` and `Weapon::operator==`; stream insertion for `Weapon` |
| 3 | Main function and function prototypes | `main()` and declarations in headers |
| 3 | Call by reference | `Enemy::attack(Character&)`, `Inventory::usePotion(Character&)` |
| 3 | Return by reference | `Character::healthReference()` |
| 3 | Inline functions | Inline getters in `character.h` |
| 3 | Function overloading | `Character::heal()` overloads |
| 3 | Friend functions | `displayCharacterStats()` |
| 3 | Virtual functions | `Character::attack()` and derived overrides |
| 3 | Arrays within a class | `Character::abilities[3]` |
| 3 | Static member functions | `Character::getCharacterCount()` |
| 3 | Arrays of objects | `Battle::enemyRoster[3]` |
| 4 | Constructors and parameterized constructors | Model constructors |
| 4 | Inheritance constructors | Derived constructors invoke `Character(...)` |
| 4 | Copy constructors | `Character`, `Warrior`, `Mage`, `Archer`, `Inventory` |
| 4 | Dynamic constructors | `Inventory` allocates a dynamic Potion array and Weapon |
| 4 | Destructors | Virtual `Character` destructor and `Inventory` destructor |
| 4 | Operator overloading and rules | `operator>`, `operator==`, `operator<<` |
| 4 | Type conversion | `Character::operator int()` |
| 5 | Pointers to objects | `unique_ptr<Character>` and dynamic allocations in `Inventory` |
| 5 | Pointer to derived classes | `unique_ptr<Character>` owns derived player objects |
| 5 | `this` pointer | `Character::setName()` and `setHealth()` |
| 5 | Virtual functions and runtime polymorphism | `player.attack()` |
| 5 | File stream classes | `ifstream`, `ofstream`, `fstream` |
| 5 | Opening and closing files | File streams in `GameLogger` and `SaveManager` |
| 5 | File modes | `ios::app`, `ios::in`, `ios::out`, `ios::trunc` |
| 5 | File pointers | `seekp()` in `GameLogger::updateFirstLine()` |
| 5 | Input/output and updating files | Save/load, battle logging and log update |
| 5 | Exception handling | `try`, `catch`, `throw` and validation |
| 6 | Real-life problem modelling and abstraction | Characters, weapons, potions, quests, shop and battle model a game world |

## Data files

The program writes to the `data` directory:
- `save.txt` — saved player and inventory details
- `battle_log.txt` — battle history

The program expects to be launched from the project root so relative data paths resolve correctly.

## Notes and limitations

- Save/load currently restores the character name, health, gold, potion count and weapon. The selected character class, quest progress and achievement state are not persisted.
- The `quest_data.txt` file is reserved for a future extension; quest progress is currently kept in memory.
- This is an educational console project, not a production game engine.
- `std::unique_ptr` is used for safe ownership of the selected derived character. Raw `new`/`delete` is demonstrated internally by `Inventory` to illustrate dynamic allocation and destructor-based cleanup.
