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
string directions = "links rechts vor zurueck weiter ";
string classList = "Jaeger Krieger Schurke";
string statsCommands = "stats werte ueberpruefen";

enum Direction
{
    Oben,
    Unten,
    Links,
    Rechts
};
// Gegnerklasse
class Enemy
{
public:
    int type;
    string name;
    int hitpoints;
    int strenght;

    Enemy(int i) : type(i)
    {

        if (type == 1)
        {
            name = "Goblin";
            hitpoints = 20;
            strenght = 10;
        }
        else if (type == 2)
        {
            name = "Ogre";
            hitpoints = 50;
            strenght = 20;
        }
        else if (type == 3)
        {
            name = "Skeleton Archer";
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

        if (playerClass == "Jaeger")
        {
            hitpoints = 100;
            weapon = "Bogen";
            weaponType = "Fernkampf";
            strenght = 10;
            cout << name << " der erfahrene " << playerClass << " viel Spaß beim Spielen." << endl;
        }
        else if (playerClass == "Krieger")
        {
            hitpoints = 150;
            weapon = "Schwert";
            weaponType = "Nahkampf";
            strenght = 15;
            cout << name << " der starke " << playerClass << " viel Spaß beim Spielen." << endl;
        }
        else if (playerClass == "Schurke")
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
            cout << "Bitte wähle eine der Folgenden Klassen: " << classList << endl;
            string input;
            getline(cin, input);
            setClass(input);
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
    vector<pair<Direction, int>> connectedRooms;
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
    void addConnection(Direction direction, int connectedRoom)
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
        cout << "Es gibt bereits einen Spielstand. Soll dieser Überschrieben werden?" << endl;

        getline(cin, input);
        if (input == "Ja")
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
        cout << startCommands << " " << loadCommands << endl;
    }
    else
    {
        cout << "gehe, untersuche, benutze, angreifen" << endl;
    }
}
// Ausgabe falls unbekannte Richtung eingegeben wurde
void unknownDirection(string direction)
{
    cout << "Unbekannte Richtung. "
         << "Folgende Richtungen sind zulässig: " << directions << endl;
}
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
        transform(word.begin(), word.end(), word.begin(), static_cast<int (*)(int)>(tolower));
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
            saveGameState("spielstand.txt");
                }
        else if (statsCommands.find(command) != string::npos)
            {
            player.showStats();
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
        if (startCommands.find(command) != string::npos)
            {
                createMap();
                cout << "Wie lautet dein Name?" << endl;
                getline(cin, input);
                player.setName(input);

            cout << "Welche Klasse möchtest du sein? " << classList << endl;
                getline(cin, input);
                player.setClass(input);
            }
        else if (loadCommands.find(command) != string::npos)
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
// Erstellen der Karte
void createMap()
{
    Room start("start", false);
    start.addConnection(Oben, 1);
    map.push_back(start);

    Room room1("room1", true);
    room1.addConnection(Unten, 0);
    room1.addConnection(Links, 2);
    room1.addConnection(Rechts, 5);
    map.push_back(room1);

    Room room2("room2", false);
    room2.addConnection(Rechts, 1);
    room2.addConnection(Oben, 3);
    map.push_back(room2);

    Room room3("room3", true);
    room3.addConnection(Links, 4);
    room3.addConnection(Unten, 2);
    map.push_back(room3);

    Room room4("room4", false);
    room4.addConnection(Links, 3);
    map.push_back(room4);

    Room room5("room5", false);
    room5.addConnection(Links, 1);
    room5.addConnection(Oben, 6);
    map.push_back(room5);

    Room room6("room6", true);
    room6.addConnection(Unten, 5);
    room6.addConnection(Oben, 6);
    map.push_back(room6);

    Room room7("room7", true);
    room7.addConnection(Unten, 6);
    room7.addConnection(Links, 8);
    map.push_back(room7);

    Room room8("room8", false);
    room8.addConnection(Rechts, 7);
    room8.addConnection(Oben, 9);
    map.push_back(room8);

    Room boss("boss", true);
    boss.addConnection(Unten, 8);
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
                file << enemy.type << endl;
                file << enemy.name << endl;
                file << enemy.hitpoints << endl;
                file << enemy.strenght << endl;
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
                    room.addConnection(static_cast<Direction>(direction), connectedRoom);
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
                    getline(file,line);
                    enemyDamage = stoi(line);
                    Enemy enemy(enemyType);
                    enemy.name = enemyName;
                    enemy.hitpoints = enemyHitpoints;
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