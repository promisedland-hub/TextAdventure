#include <iostream>
#include <string>

using namespace std;


class Enemy {
public:
    string name;
    int hitpoints;


    Enemy(string name, int gesundheit) : name(name), hitpoints(gesundheit) {}

    void anzeigen() {
        cout << "Gegner: " << name << ", Gesundheit: " << hitpoints << endl;
    }

    void angreifen() {
        // Implementiere die Logik für den Angriff des Gegners
    }
};