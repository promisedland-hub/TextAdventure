#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Enemy {
public:
    string name;
    int hitpoints;


    Enemy(string name, int gesundheit) : name(name), hitpoints(gesundheit) {}

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
        int gesundheit;
        string klasse;
        string waffe;
        string waffentyp;
        
        Player(string Name, string Klasse) : name(Name), klasse(Klasse) {

            if (klasse == "Jäger"){
                gesundheit = 100;
                waffe = "Bogen";
                waffentyp = "Fernkampf";
            } else if (klasse == "Krieger"){
                gesundheit = 150;
                waffe = "Schwert";
                waffentyp = "Nahkampf";
            } else if (klasse == "Schurke"){
                gesundheit = 80;
                waffe = "Dolche";
                waffentyp = "Nahkampf";
            }
        }


        void showStats(){
            cout << "Spieler: " << name << ", Gesundheit: " << gesundheit << endl;
        }
        void attack() {
        // Implementiere die Logik für den Angriff des Spielers
    }
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
