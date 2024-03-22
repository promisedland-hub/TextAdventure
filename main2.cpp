#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <random>

#include "enemy.hpp"
// #include "direction.hpp"
enum DIRECTION : char
{
    Oben,
    Unten,
    Links,
    Rechts
};

using namespace std;

vector<string> startCommands = {"start", "neu"};
vector<string> loadCommands = {"laden", "lade"};
vector<string> saveCommands = {"speichern", "speicher"};
vector<string> walkCommands = {"gehe"};
vector<string> useCommands = {"benutze"};
vector<string> searchCommands = {"untersuche", "suche"};
vector<string> directions = {"links", "rechts", "vor", "zurueck", "weiter "};
vector<string> classList = {"jaeger", "krieger", "schurke"};
vector<string> statsCommands = {"stats", "werte", "ueberpruefen"};

// Gegnerklasse

// Spielerklasse
class Player
{
public:
    string name;
    int hitpoints;
    string playerClass;
    string weapon;
    string weaponType;
    int strenght;

    Player(string name, string playerClass) : name(name), playerClass(playerClass)
    {
    }

    void showStats()
    {
        // Abrufen der Stats
        cout << "Spieler: " << name << ", Gesundheit: " << hitpoints << ", Klasse" << playerClass << endl;
    }

    void attack(Player *Player, Enemy *Enemy)
    {
        // Angriffslogik für Spieler
    }

    void save(ofstream &outputFile)
    {
        outputFile << "Player" << endl;
        outputFile << name << endl;
        outputFile << playerClass << endl;
        outputFile << weapon << endl;
        outputFile << weaponType << endl;
        outputFile << hitpoints << endl;
        outputFile << strenght << endl;
    }

    void load(ifstream &inputFile)
    {
        // string type;
        // inputFile >> type;
        inputFile >> name;
        inputFile >> playerClass;
        inputFile >> weapon;
        inputFile >> weaponType;
        inputFile >> hitpoints;
        inputFile >> strenght;
    }
    void setName(string choosenName)
    {
        name = choosenName;
    }

    void setClass(string choosenClass)
    {
        playerClass = choosenClass;

        if (playerClass == classList[0])
        {
            hitpoints = 100;
            weapon = "Bogen";
            weaponType = "Fernkampf";
            strenght = 10;
            cout << name << " der erfahrene " << playerClass << " viel Spaß beim Spielen." << endl;
        }
        else if (playerClass == classList[2])
        {
            hitpoints = 150;
            weapon = "Schwert";
            weaponType = "Nahkampf";
            strenght = 15;
            cout << name << " der starke " << playerClass << " viel Spaß beim Spielen." << endl;
        }
        else if (playerClass == classList[3])
        {
            hitpoints = 80;
            weapon = "Dolche";
            weaponType = "Nahkampf";
            strenght = 20;
            cout << name << " der listige " << playerClass << " viel Spaß beim Spielen." << endl;
        }
        else
        {
            cout << "Unbekannte Klasse " << playerClass << endl;
            cout << "Bitte wähle eine der Folgenden Klassen: ";
            for (const auto &classList : classList)
            {
                cout << classList << " ";
            }
            string input;
            getline(cin, input);
            stringstream ss;
            string word;
            vector<string> words;
            while (ss >> word)
            {
                transform(word.begin(), word.end(), word.begin(), static_cast<int (*)(int)>(tolower));
                words.push_back(word);
            }
            if (words.size() > 0)
            {
                setClass(words[0]);
            }
        }
    }
};
// Raumklasse
class Room
{
public:
    string name;
    bool hostile;
    int enemycount;
    vector<pair<DIRECTION, int>> connectedRooms;
    vector<Enemy> enemies;

    Room(string name, bool hostile) : name(name), hostile(hostile)
    {

        if (hostile == true)
        {
            random_device rd;
            mt19937 generator(rd());
            int min = 1;
            int max = 3;
            int enemyCount2;
            int enemyType;
            uniform_int_distribution<int> distribution(min, max);

            enemycount = distribution(generator);
            enemyCount2 = enemycount;
            while (enemyCount2 > 0)
            {
                enemyType = distribution(generator);
                Enemy enemy(enemyType);
                enemies.push_back(enemy);
                enemyCount2--;
            }
        }
    }
    void addConnection(DIRECTION direction, int connectedRoom)
    {
        connectedRooms.emplace_back(direction, connectedRoom);
    }
};

Player player("", "");
vector<Room> map;

bool isFileEmpty(const string &filename);
void saveGameState(const string &filename);
void loadGameState(const string &filename);
void renderGameStart(string action);
void renderGameState(string action);
void unknownCommand(string command, bool startCommand);
void unknownDirection(string direction);
void updateGameState(string input);
void saveMapToFile(const string &filename);
void loadMapFromFile(const string &filename);
void createMap();

// Prüfen ob Datei bereits Daten enthält
bool isFileEmpty(const string &filename)
{
    ifstream file(filename);

    return file.peek() != EOF;
}
// Speichern des Spieles
void saveGameState(const string &filename)
// Speichern des Spieles
{
    ofstream outputFile(filename);

    if (!isFileEmpty(filename))
    {
        string input;
        string accept = "ja speichern";
        cout << "Es gibt bereits einen Spielstand. Soll dieser Überschrieben werden?" << endl;

        getline(cin, input);
        stringstream ss(input);
        string word;
        vector<string> words;
        string acceptCommands = "ja start starten";
        string denieCommands = "nein abbrechen zurück";

        while (ss >> word)
        {
            transform(word.begin(), word.end(), word.begin(), static_cast<int (*)(int)>(tolower));
            words.push_back(word);
        }

        if (words.size() > 0)
        {
            string command = words[0];

            if (acceptCommands.find(command) != string::npos)
            {
                if (outputFile.is_open())
                {
                    player.save(outputFile);
                    saveMapToFile("map.txt");

                    outputFile.close();
                    cout << "Spielstand erflogreich gespeichert." << endl;
                }
                else
                {
                    cout << "Fehler beim Öffnen der Datei zum Speichern des Spieles";
                }
            }
            else if (denieCommands.find(command) != string::npos)
            {
                cout << "Speichern abgebrochen. " << endl;
            }
            else
            {
                cout << "Unbekannter Befehl. Folgenden Befehle sind zulässig: " << acceptCommands << endl;
                cout << denieCommands << endl;
                cout << "Speichern abgeborchen." << endl;
            }
        }
    }
    else
    {
        if (outputFile.is_open())
        {
            player.save(outputFile);
            saveMapToFile("map.txt");

            outputFile.close();
            cout << "Spielstand erflogreich gespeichert." << endl;
        }
        else
        {
            cout << "Fehler beim Öffnen der Datei zum Speichern des Spieles";
        }
    }
}
// Laden des Spieles
void loadGameState(const string &filename)
{
    string input;
    ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        while (!inputFile.eof())
        {
            string type;
            inputFile >> type;

            if (type == "Player")
            {
                player.load(inputFile);
            }
            else if (type == "Enemy")
            {
                // enemy.load(inputFile);
            }
            else if (type == "Room")
            {
                // room.load(inputFile);
            }
        }

        inputFile.close();
        cout << "Spielstand erfolgreich geladen." << endl;
        cout << "Willkommen zurück " << player.name << endl;
    }
    else
    {
        cout << "Fehler beim Öffnen der Datei zum Laden des Spielstandes." << endl;
        cout << "Möchstest du ein neues Spiel starten?" << endl;
        getline(cin, input);

        stringstream ss(input);
        string word;
        vector<string> words;
        string acceptCommands = "ja start starten";
        string denieCommands = "nein abbrechen zurück";

        while (ss >> word)
        {
            transform(word.begin(), word.end(), word.begin(), static_cast<int (*)(int)>(tolower));
            words.push_back(word);
        }

        if (words.size() > 0)
        {
            string command = words[0];

            if (acceptCommands.find(command) != string::npos)
            {
                renderGameStart("start");
            }
            else if (denieCommands.find(command) != string::npos)
            {
                cout << "Spiel Start abgelehnt. Spiel wird geschlossen.";
                exit(0);
            }
        }
    }
}
// Ausgabe falls Unbekannter befehl eingegeben wurde
void unknownCommand(string command, bool startCommand)
{
    cout << "Unbekannter Befehl: " << command << endl;
    cout << "Folgende Befehle sind zulässig: ";

    if (startCommand == true)
    {
        for (const auto &startCommands : startCommands)
        {
            cout << startCommands << " ";
        }
        for (const auto &loadCommands : loadCommands)
        {
            cout << loadCommands << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "gehe, untersuche, benutze, angreifen" << endl;
    }
}
// Ausgabe falls unbekannte Richtung eingegeben wurde
void unknownDirection(string direction)
{
    cout << "Unbekannte Richtung. ";
    cout << "Folgende Richtungen sind zulässig: ";
    for (const auto &directions : directions)
    {
        cout << directions << " ";
    }
    cout << endl;
}
// Funktion, um den Spielzustand zu aktualisieren und auf Eingaben zu reagieren
void updateGameState(string input)
{
    stringstream ss(input);
    string word;
    vector<string> words;
    // Liste an wörtern für vorwärts
    vector<string> forward = {"weiter", "vor", "vorwärts"};
    // Liste an wörtern für rückwärts
    vector<string> backwards = {"zurück", "rückwärts"};

    // Aufteilen der Eingabe in Wörter
    while (ss >> word)
    {
        transform(word.begin(), word.end(), word.begin(), static_cast<int (*)(int)>(tolower));
        words.push_back(word);
    }

    // Überprüfen der Schlüsselwörter
    if (words.size() > 0)
    {
        // Das erste Wort entspricht dem Befehl des Spielers
        string command = words[0];

        // Befehl überprüfen und entsprechende Aktion ausführen
        for (const auto &walkCommands : walkCommands)
        {
            if (command == walkCommands)
            {
                if (words.size() > 1)
                {
                    // Das zweite wort ist die anweisung daruaf wohin es gehen soll
                    string direction = words[1];

                    for (const auto &forward : forward)
                    {
                        if (direction == forward)
                        {
                            // Spieler geht weiter
                        }
                        else
                        {
                            for (const auto &backwards : backwards)
                            {
                                if (direction == backwards)
                                {
                                    // Spieler geht weiter
                                }
                                else
                                {
                                    // Spieler hat falsche richtung angegeben
                                    cout << "Unbekannte Richtung: " << direction << endl;
                                    getline(cin, input);
                                    updateGameState(input);
                                }
                            }
                        }
                    }
                }
                else
                {
                    // Spieler hat keine richtung angegeben
                    cout << "Keine Richtung angegeben." << endl;
                }
            }
            for (const auto &searchCommands : searchCommands)
            {
                if (searchCommands == command)
                {
                    // TODO: Füge Code hinzu, um ein Objekt zu untersuchen
                }
            }
            for (const auto &useCommands : useCommands)
            {
                if (useCommands == command)
                {
                    // TODO: Füge Code hinzu, um ein Objekt zu benutzen
                }
            }
            for (const auto &saveCommands : saveCommands)
            {
                if (saveCommands == command)
                {
                    // TODO: Füge Code hinzu, um ein Objekt zu benutzen
                }
            }
            for (const auto &statsCommands : statsCommands)
            {
                if (statsCommands == command)
                {
                    // TODO: Füge Code hinzu, um ein Objekt zu benutzen
                }
                else
                {
                    // Unbekannter Befehl
                    unknownCommand(command, false);
                }
            }
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
// Initialisierung des Spielstartes oder Ladens
void renderGameStart(string action)
{
    stringstream ss(action);
    string word;
    vector<string> words;
    string input;
    // Aufteilen der Eingabe in Wörter
    while (ss >> word)
    {
        transform(word.begin(), word.end(), word.begin(), static_cast<int (*)(int)>(tolower));
        words.push_back(word);
    }

    if (words.size() > 0)
    {
        // Das erste Wort entspricht dem Befehl des Spielers
        string command = words[0];

        // Befehl überprüfen und entsprechende Aktion ausführen
        for (const auto &startCommands : startCommands)
        {
            if (startCommands == command)
            {
                createMap();
                cout << "Wie lautet dein Name?" << endl;
                getline(cin, input);
                player.setName(input);

                cout << "Welche Klasse möchtest du sein? ";
                for (const auto &classList : classList)
                {
                    cout << classList << " ";
                }
                cout << endl;
                getline(cin, input);
                player.setClass(input);
                exit;
            }
            else
            {
                for (const auto &loadCommands : loadCommands)
                {
                    if (loadCommands == command)
                    {

                        loadGameState("spielstand.txt");
                        loadMapFromFile("map.txt");
                    }
                    else
                    {
                        unknownCommand(command, true);
                        getline(cin, input);
                        renderGameStart(input);
                    }
                }
            }
        }
    }
}
// Erstellen der Karte
void createMap()
{
    Room start("start", false);
    start.addConnection(DIRECTION::Oben, 1);
    map.push_back(start);

    Room room1("room1", true);
    room1.addConnection(DIRECTION::Unten, 0);
    room1.addConnection(DIRECTION::Links, 2);
    room1.addConnection(DIRECTION::Rechts, 5);
    map.push_back(room1);

    Room room2("room2", false);
    room2.addConnection(DIRECTION::Rechts, 1);
    room2.addConnection(DIRECTION::Oben, 3);
    map.push_back(room2);

    Room room3("room3", true);
    room3.addConnection(DIRECTION::Links, 4);
    room3.addConnection(DIRECTION::Unten, 2);
    map.push_back(room3);

    Room room4("room4", false);
    room4.addConnection(DIRECTION::Links, 3);
    map.push_back(room4);

    Room room5("room5", false);
    room5.addConnection(DIRECTION::Links, 1);
    room5.addConnection(DIRECTION::Oben, 6);
    map.push_back(room5);

    Room room6("room6", true);
    room6.addConnection(DIRECTION::Unten, 5);
    room6.addConnection(DIRECTION::Oben, 6);
    map.push_back(room6);

    Room room7("room7", true);
    room7.addConnection(DIRECTION::Unten, 6);
    room7.addConnection(DIRECTION::Links, 8);
    map.push_back(room7);

    Room room8("room8", false);
    room8.addConnection(DIRECTION::Rechts, 7);
    room8.addConnection(DIRECTION::Oben, 9);
    map.push_back(room8);

    Room boss("boss", true);
    boss.addConnection(DIRECTION::Unten, 8);
    map.push_back(boss);

    cout << "Karte erstellt" << endl;
}
// Speichern der Karte
void saveMapToFile(const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const Room &room : map)
        {
            file << room.name << endl;
            file << room.hostile << endl;
            file << room.enemycount << endl;
            for (const auto &connection : room.connectedRooms)
            {
                file << connection.first << " " << connection.second << endl;
            }
            for (const auto &enemy : room.enemies)
            {
                file << enemy.getType() << endl;
                file << enemy.getName() << endl;
                file << enemy.getHitpoints() << endl;
                file << enemy.getStrength() << endl;
            }
            file << endl;
        }
        file.close();
        cout << "Karte gespeichert" << endl;
    }
    else
    {
        cout << "Fehler beim Öffnen der Datei zum Speichern der Karte." << endl;
    }
}
// Laden der Karte
void loadMapFromFile(const string &filename)
{
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        Room room("", false);

        while (getline(file, line))
        {
            if (room.name.empty())
            {
                room.name = line;
            }
            getline(file, line);
            if (room.hostile == false)
            {
                room.hostile = stoi(line);
            }
            getline(file, line);
            if (room.enemycount == 0)
            {
                room.enemycount = stoi(line);
            }
            getline(file, line);
            if (room.connectedRooms.empty())
            {
                int direction;
                int connectedRoom;

                while (line.size() > 1)
                {
                    istringstream iss(line);
                    iss >> direction >> connectedRoom;
                    room.addConnection(static_cast<DIRECTION>(direction), connectedRoom);
                    getline(file, line);
                }
            }
            if (room.enemies.empty())
            {
                while (!line.empty())
                {
                    int enemyType = stoi(line);
                    int enemyHitpoints;
                    string enemyName;
                    int enemyDamage;

                    getline(file, line);
                    enemyName = line;
                    getline(file, line);
                    enemyHitpoints = stoi(line);
                    getline(file, line);
                    enemyDamage = stoi(line);
                    Enemy enemy(enemyType);
                    enemy.setName(enemyName);
                    enemy.setHitpoints(enemyHitpoints);
                    room.enemies.push_back(enemy);
                    getline(file, line);
                }
                if (!room.name.empty())
                {
                    map.push_back(room);
                    room = Room("", false);
                    room.enemycount = 0;
                }
            }
        }
    }
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
        cout << "Du befindest dich in" << endl;
        // Eingabe des Spielers abfragen
        cout << "Was möchtest du tun? " << endl;
        getline(cin, input);

        // Spielzustand aktualisieren
        updateGameState(input);

        // Überprüfen auf Spielende
        // TODO: Bedingungen hinzu, um das Spiel zu beenden (z.B. wenn der Spieler gewinnt oder verliert)

        if (player.hitpoints == 0)
        {
            cout << "Game Over.";
            exit;
        }
    }
    return 0;
}