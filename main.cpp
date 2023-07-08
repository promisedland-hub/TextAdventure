#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <random>

using namespace std;

string startCommands = "start neu";
string loadCommands = "laden lade";
string saveCommands = "speichern speicher";
string walkCommands = "gehe";
string useCommands = "benutze";
string searchCommands = "untersuche suche";
string directions = "weiter vor vorwärts zurück rückwärts";
// Gegnerklasse
class Enemy
{
public:
    string name;
    int hitpoints;
    int strenght;

    Enemy(string name, int hitpoints) : name(name), hitpoints(hitpoints)
    {

        if (name == "Goblin")
        {
            hitpoints = 20;
            strenght = 10;
        }
        else if (name == "Ogre")
        {
            hitpoints = 50;
            strenght = 20;
        }
        else if (name == "Skeleton Archer")
        {
            hitpoints = 10;
            strenght = 5;
        }
    }

    void showStats()
    {
        cout << "Gegner: " << name << ", Gesundheit: " << hitpoints << endl;
    }

    void attack()
    {
        // Implementiere die Logik für den Angriff des Gegners
    }
    void save(ofstream &outputFile)
    {
        outputFile << "Enemy" << endl;
        outputFile << name << endl;
        outputFile << hitpoints << endl;
        outputFile << strenght << endl;
    }
    void load(ifstream &inputFile)
    {
        string type;
        inputFile >> type;
        inputFile >> name;
        inputFile >> hitpoints;
        inputFile >> strenght;
    }
};
// Spielerklasse
class Player
{
public:
    string name;
    int hitpoints;
    string playerClass;
    string weapon;
    string weaponType;
    int damage;

    Player(string name, string playerClass) : name(name), playerClass(playerClass)
    {

        if (playerClass == "Jäger")
        {
            hitpoints = 100;
            weapon = "Bogen";
            weaponType = "Fernkampf";
            damage = 10;
        }
        else if (playerClass == "Krieger")
        {
            hitpoints = 150;
            weapon = "Schwert";
            weaponType = "Nahkampf";
            damage = 15;
        }
        else if (playerClass == "Schurke")
        {
            hitpoints = 80;
            weapon = "Dolche";
            weaponType = "Nahkampf";
            damage = 20;
        }
    }

    void showStats()
    {
        // Abrufen der Stats
        cout << "Spieler: " << name << ", Gesundheit: " << hitpoints << endl;
    }
    void attack(Player *Player, Enemy *Enemy)
    {
        // Angriffslogik für Spieler
    }
};
// Raumklasse
class Room
{
public:
    string name;
    bool hostile;
    int enemycount;

    Room(string name, bool hostile, int enemycount, bool containsObjekt) : name(name), hostile(hostile)
    {

        if (hostile == true)
        {
            random_device rd;
            mt19937 generator(rd());
            int min = 0;
            int max = 3;
            uniform_int_distribution<int> distribution(min, max);

            enemycount = distribution(generator);
        }
    }
};

// Funktion, um den Spielzustand zu aktualisieren und auf Eingaben zu reagieren
void updateGameState(string input)
{
    stringstream ss(input);
    string word;
    vector<string> words;
    // Liste an wörtern für vorwärts
    string forward = "weiter vor vorwärts";
    // Liste an wörtern für rückwärts
    string backwards = "zurück rückwärts";

    // Aufteilen der Eingabe in Wörter
    while (ss >> word)
    {
        transform(words.begin(), words.end(), word.begin(), ::tolower);
        words.push_back(word);
    }

    // Überprüfen der Schlüsselwörter
    if (words.size() > 0)
    {
        // Das erste Wort entspricht dem Befehl des Spielers
        string command = words[0];

        // Befehl überprüfen und entsprechende Aktion ausführen
        if (walkCommands.find(command) != string::npos)
        {
            if (words.size() > 1)
            {
                // Das zweite wort ist die anweisung daruaf wohin es gehen soll
                string direction = words[1];

                if (forward.find(direction) != string::npos)
                {
                    // Spieler geht weiter
                }
                else if (backwards.find(direction) != string::npos)
                {
                    // Spieler geht zurück
                }
                else
                {
                    // Spieler hat falsche richtung angegeben
                    cout << "Unbekannte Richtung: " << direction << endl;
                    getline(cin, input);
                    updateGameState(input);
                }
            }
            else
            {
                // Spieler hat keine richtung angegeben
                cout << "Keine Richtung angegeben." << endl;
            }
        }
        else if (searchCommands.find(command) != string::npos)
        {
            // TODO: Füge Code hinzu, um ein Objekt zu untersuchen
        }
        else if (useCommands.find(command) != string::npos)
        {
            // TODO: Füge Code hinzu, um ein Objekt zu benutzen
        }
        else if (saveCommands.find(command) != string::npos)
        {
        }
        else
        {
            // Unbekannter Befehl
            unknownCommand(command, false);
        }
    }
}

// Funktion, um den aktuellen Spielzustand auszugeben
void renderGameState(string action)
{
    // TODO: Code zum Rendern hinzufügen
    if (action == "start")
    {
        // TODO : Ausgabe für start
    }
    else if (action == "gehe")
    {
        // TODO : Ausgabe für gehe
    }
    else if (action == "untersuche")
    {
        // TODO : Ausgabe für untersuche
    }
    else if (action == "benutze")
    {
        // TODO : Ausgabe für benutze
    }
    else if (action == "kaempfe")
    {
        // TODO : Ausgabe für kaempfe
    }
}
void renderGameStart(string action)
{
    stringstream ss(action);
    string word;
    vector<string> words;
    string input;
    // Aufteilen der Eingabe in Wörter
    while (ss >> word)
    {
        transform(words.begin(), words.end(), word.begin(), ::tolower);
        words.push_back(word);
    }

    if (words.size() > 0)
    {
        // Das erste Wort entspricht dem Befehl des Spielers
        string command = words[0];

        // Befehl überprüfen und entsprechende Aktion ausführen
        if (startCommands.find(command) != string::npos)
        {
            cout << "Wie lautet dein Name?" << endl;
        }
        else if (loadCommands.find(command) != string::npos)
        {
        }
        else
        {
            unknownCommand(command, true);
            getline(cin, input);
            renderGameStart(input);
        }
    }
}

void unknownCommand(string command, bool startCommand)
{
    cout << "Unbekannter Befehl: " << command << endl;
    cout << "Folgende Befehle sind zulässig: ";

    if (startCommand == true)
    {
        cout << startCommands << " " << loadCommands << endl;
    }
    else
    {
        cout << "gehe, untersuche, benutze, angreifen" << endl;
    }
}
void unknownDirection(string direction)
{
    cout << "Unbekannte Richtung. "
            "Folgende Richtungen sind zulässig: "
         << directions << endl;
}
int main()
{
    string input;

    // Spielbegrüßung
    cout << "Willkommen zum Textadventure!" << endl;

    cout << "Möchtest du ein neues Spiel starten oder einen Spielstand laden?" << endl;
    getline(cin, input);
    renderGameStart(input);

    // Hauptschleife des Spiels
    while (true)
    {
        // Spielzustand anzeigen
        cout << "Du befindest dich in";
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