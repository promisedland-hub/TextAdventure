#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Enemy {
public:
    string name;
    int hitpoints;
    string enemyClass;
    string weapon;
    string weaponType;

    Enemy(string name, int hitpoints) : name(name), hitpoints(hitpoints) {

        if (enemyClass == "Goblin")
        {
            hitpoints = 20;
            weapon = "Kurzschwert";
            weaponType = "Nahkampf";
        } else if (enemyClass == "Ogre")
        {
            hitpoints = 50;
            weapon = "Bogen";
            weaponType = "Fernkampf";

        } else if (enemyClass == "Skeleton Archer")
        {
            hitpoints = 10;
                weapon = "Bogen";
                weaponType = "Fernkampf";

        }
    }

    void showStats() {
        cout << "Gegner: " << name << ", Gesundheit: " << hitpoints << endl;
    }

    void attack() {
        // Implementiere die Logik für den Angriff des Gegners
    }
};
class Player{
    public: 
        string name;
        int hitpoints;
        string playerClass;
        string weapon;
        string weaponType;
        
        Player(string name, string playerClass) : name(name), playerClass(playerClass) {

            if (playerClass == "Jäger"){
                hitpoints = 100;
                weapon = "Bogen";
                weaponType = "Fernkampf";
            } else if (playerClass == "Krieger"){
                hitpoints = 150;
                weapon = "Schwert";
                weaponType = "Nahkampf";
            } else if (playerClass == "Schurke"){
                hitpoints = 80;
                weapon = "Dolche";
                weaponType = "Nahkampf";
            }
        }


        void showStats(){
            cout << "Spieler: " << name << ", Gesundheit: " << hitpoints << endl;
        }
        void attack() {
        // Implementiere die Logik für den Angriff des Spielers
    }
};

class Room{
    public:
        bool hostile;
        

};
// Funktion, um den Spielzustand zu aktualisieren und auf Eingaben zu reagieren
void updateGameState(string input) {
      // Aufteilen der Eingabe in Wörter
    stringstream ss(input);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }

    // Überprüfen der Schlüsselwörter
    if (words.size() > 0) {
        // Das erste Wort entspricht dem Befehl des Spielers
        string command = words[0];

        // Befehl überprüfen und entsprechende Aktion ausführen
        if (command == "gehe") {
            // TODO: Füge Code hinzu, um den Spieler in einen anderen Raum zu bewegen
        } else if (command == "untersuche") {
            // TODO: Füge Code hinzu, um ein Objekt zu untersuchen
        } else if (command == "benutze") {
            // TODO: Füge Code hinzu, um ein Objekt zu benutzen
        } else {
            // Unbekannter Befehl
            cout << "Unbekannter Befehl: " << command << endl;
            cout << "Folgende Befehle sind zulässig: " << "gehe, untersuche, benutze, angreifen" << endl;
        }
    }
}


// Funktion, um den aktuellen Spielzustand auszugeben
void renderGameState(string action) {
    // TODO: Code zum Rendern hinzufügen
    if (action == "start"){
        //TODO : Ausgabe für start
        
    } else if (action == "gehe"){
        //TODO : Ausgabe für gehe

    } else if (action == "untersuche"){
        //TODO : Ausgabe für untersuche
    } else if (action == "benutze"){
        //TODO : Ausgabe für benutze
    } else if (action == "kaempfe"){
        //TODO : Ausgabe für kaempfe
    }

}
void renderGameStart(string action){
    if (action == "start"){
        //TODO Neues Spiel starten
    } else if (action == "laden"){
        //TODO Ladefunktion hinzufügen
    }
}

int main() {
    string input;

    // Spielbegrüßung
    cout << "Willkommen zum Textadventure!" << endl;


    // Hauptschleife des Spiels
    while (true) {
        // Spielzustand anzeigen
        cout << "Möchtest du ein neues Spiel starten oder einen Spielstand laden?" << endl;
        cin >> input;
        renderGameStart(input);

        // Eingabe des Spielers abfragen
        cout << "Was möchtest du tun? ";
        getline(cin, input);

        // Spielzustand aktualisieren
        updateGameState(input);

        // Überprüfen auf Spielende
        // TODO: Bedingungen hinzu, um das Spiel zu beenden (z.B. wenn der Spieler gewinnt oder verliert)

        // Leerzeile für bessere Lesbarkeit
        cout << endl;
    }

    return 0;
}
