#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ================= PLAYER =================
struct Player {
    string className;
    int maxHP, hp;
    int maxMana, mana;
    int gold;
    int level;
    int xp;
    int attack;
};

// ================= MONSTER =================
struct Monster {
    string name;
    int hp;
    int attack;
    int xp;
    bool hasGold;
};

// ================= FUNKCE =================

void printStats(Player &p) {
    cout << "\n--- HRAC ---\n";
    cout << "Class: " << p.className << endl;
    cout << "HP: " << p.hp << "/" << p.maxHP << endl;
    cout << "Mana: " << p.mana << "/" << p.maxMana << endl;
    cout << "Gold: " << p.gold << endl;
    cout << "Level: " << p.level << " (XP: " << p.xp << ")\n";
}
// LEVEL UP
void checkLevel(Player &p) {
    int neededXP = p.level * 10;
    if (p.xp >= neededXP) {
        p.level++;
        p.maxHP++;
        p.attack++;
        p.maxMana++;
        cout << "\nLEVEL UP!\n";
        cout << "HP +1, Attack +1, Mana +1\n";
    }
}

// COMBAT
bool fight(Player &p, vector<Monster> enemies, bool boss = false) {
    cout << "\n--- SOUBOJ ---\n";

    while (p.hp > 0 && !enemies.empty()) {

        // HRAC TAH
        cout << "\nTvuj tah:\n1) Utok\n2) Schopnost\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            enemies[0].hp -= p.attack;
            cout << "Utok za " << p.attack << endl;
        }
        else if (choice == 2 && p.mana > 0) {
            cout << "Pouzil jsi schopnost!\n";
            enemies[0].hp -= (p.attack + 1);
            p.mana--;
        }

        if (enemies[0].hp <= 0) {
            cout << enemies[0].name << " zabit!\n";
            p.xp += enemies[0].xp;

            if (enemies[0].hasGold && rand()%2==0) {
                int g = rand()%5 + 2;
                p.gold += g;
                cout << "Ziskal jsi " << g << " gold!\n";
            }

            enemies.erase(enemies.begin());
            checkLevel(p);
            continue;
        }

        // NEPRATEL TAH
        for (auto &e : enemies) {
            if (e.hp > 0) {
                cout << e.name << " utoci za " << e.attack << endl;
                p.hp -= e.attack;
            }
        }

        if (p.hp <= 0) {
            cout << "PROHRAL JSI!\n";
            return false;
        }
    }

    return true;
}

// VESNICE
void village(Player &p) {
    cout << "\n--- VESNICE ---\n";
    cout << "1) Heal (3 gold)\n";
    cout << "2) Max HP +1 (5 gold)\n";
    cout << "3) Mana +1 (5 gold)\n";
    cout << "4) Attack +1 (6 gold)\n";

    int choice;
    cin >> choice;

    if (choice == 1 && p.gold >= 3) {
        p.hp = p.maxHP;
        p.gold -= 3;
    }
    else if (choice == 2 && p.gold >= 5) {
        p.maxHP++;
        p.gold -= 5;
    }
    else if (choice == 3 && p.gold >= 5) {
        p.maxMana++;
        p.gold -= 5;
    }
    else if (choice == 4 && p.gold >= 6) {
        p.attack++;
        p.gold -= 6;
    }
    else {
        cout << "Nedostatek zlata!\n";
    }
    }

// CLASS CHOICE
Player chooseClass() {
    while (true) {
        cout << "\nVyber classu:\n1) Paladin\n2) Lovec\n3) Mag\n4) Warlock\n";
        int c;
        cin >> c;

        Player p;

        if (c == 1) {
            p = {"Paladin", 6,6,5,5,5,1,0,3};
        } else if (c == 2) {
            p = {"Lovec",5,5,4,4,5,1,0,4};
        } else if (c == 3) {
            p = {"Mag",4,4,7,7,5,1,0,2};
        } else if (c == 4) {
            p = {"Warlock",5,5,6,6,5,1,0,3};
        }

        printStats(p);
        cout << "Potvrdit? (1=ano, 0=ne)\n";
        int confirm;
        cin >> confirm;

        if (confirm == 1) return p;
    }
}

// ================= MAIN =================
int main() {
    srand(time(0));

    Player player = chooseClass();

    // MONSTRA
    Monster m1 = {"Goblin", 3, 1, 3, true};
    Monster m2 = {"Troll", 5, 2, 5, true};