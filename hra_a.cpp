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