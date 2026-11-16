#include "battle.h"
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

int readChoice(const string& prompt) {
    cout << prompt;
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Please enter a valid number.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    try {
        string playerName;
        cout << "====================================\n"
             << "          MINI RPG BATTLE GAME\n"
             << "====================================\n"
             << "Enter your character name: ";
        getline(cin, playerName);

        cout << "\nChoose your character:\n"
             << "1. Warrior\n2. Mage\n3. Archer\n";

        int choice = readChoice("Enter choice: ");
        unique_ptr<Character> player;

        if (choice == 1) player = make_unique<Warrior>(playerName);
        else if (choice == 2) player = make_unique<Mage>(playerName);
        else if (choice == 3) player = make_unique<Archer>(playerName);
        else throw invalid_argument("Invalid character selection.");

        Inventory inventory(5);
        inventory.addPotion(Potion("Small Potion", 20));
        inventory.addPotion(Potion("Small Potion", 20));
        Quest quest("Arena Champion", "Defeat all three enemies.", 3);
        Achievement achievement("Arena Champion", "Win the complete arena.");
        GameLogger logger;
        SaveManager saveManager;
        Shop shop;

        bool running = true;
        while (running) {
            cout << "\n========== MAIN MENU ==========\n"
                 << "1. Start arena battle\n"
                 << "2. Show character statistics\n"
                 << "3. Show inventory\n"
                 << "4. Visit shop\n"
                 << "5. Show quest\n"
                 << "6. Show achievement\n"
                 << "7. Save game\n"
                 << "8. Load game\n"
                 << "9. Show battle log\n"
                 << "10. Update first line of battle log\n"
                 << "11. Compare with a test warrior\n"
                 << "12. Show total character objects\n"
                 << "0. Exit\n"
                 << "===============================\n";

            try {
                choice = readChoice("Enter choice: ");

                switch (choice) {
                case 1: {
                    Battle battle;
                    battle.start(*player, inventory, quest, achievement, logger);
                    break;
                }
                case 2:
                    displayCharacterStats(*player);
                    break;
                case 3:
                    inventory.showInventory();
                    break;
                case 4: {
                    shop.display();
                    int item = readChoice("1. Buy potion\n2. Buy weapon\nChoose: ");
                    if (item == 1) shop.buyPotion(inventory);
                    else if (item == 2) shop.buyWeapon(inventory);
                    else cout << "Invalid shop choice.\n";
                    break;
                }
                case 5:
                    quest.display();
                    break;
                case 6:
                    achievement.display();
                    break;
                case 7:
                    saveManager.save(*player, inventory);
                    break;
                case 8:
                    if (!saveManager.load(*player, inventory))
                        cout << "No saved game found.\n";
                    break;
                case 9:
                    logger.showLog();
                    break;
                case 10: {
                    string message;
                    cout << "Enter replacement text for first log line: ";
                    getline(cin, message);
                    logger.updateFirstLine(message);
                    cout << "Log file updated.\n";
                    break;
                }
                case 11: {
                    Warrior testWarrior("Test Warrior");
                    cout << "\nCombat comparison: ";
                    if (*player > testWarrior)
                        cout << player->getName() << " has a higher combat score.\n";
                    else
                        cout << "Test Warrior has an equal or higher combat score.\n";

                    int playerScore = static_cast<int>(*player);
                    cout << "Player combat score using type conversion: "
                         << playerScore << '\n';
                    break;
                }
                case 12:
                    cout << "Character objects currently alive: "
                         << Character::getCharacterCount() << '\n';
                    break;
                case 0:
                    running = false;
                    cout << "Thanks for playing!\n";
                    break;
                default:
                    cout << "Invalid menu choice.\n";
                }
            } catch (const exception& error) {
                cout << "Operation failed: " << error.what() << '\n';
            }
        }
    } catch (const exception& error) {
        cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
