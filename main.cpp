#include <iostream>
#include <string>

using namespace std;

int main() {
    // Start Message
    cout << "Willkommen zu meinem Textadventure!" << endl;
    cout << "Du befindest dich in einem mysteriösen Raum..." << endl;

    // gamestate Variables
    bool gameOver = false;

    // Main Schleife des Spiels
    while (!gameOver) {
        
        string input;
        cout << "\nWas möchtest du tun? ";
        getline(cin, input);

        // Hier kannst du die Eingabe des Spielers analysieren und den Spielverlauf steuern
        // Du kannst if-else-Statements oder eine Switch-Anweisung verwenden

        // Beispiel:
        if (input == "schau um dich") {
            cout << "Du siehst einen Schreibtisch und eine Tür." << endl;
        } else if (input == "untersuche schreibtisch") {
            cout << "Du findest einen Schlüssel." << endl;
        } else if (input == "öffne tür") {
            cout << "Die Tür ist verschlossen." << endl;
        } else if (input == "verwende schlüssel") {
            cout << "Du öffnest die Tür und entkommst dem Raum. Glückwunsch!" << endl;
            gameOver = true;
        } else {
            cout << "Das verstehe ich nicht." << endl;
        }
    }

    // End Message
    cout << "Das Spiel ist vorbei. Danke fürs Spielen!" << endl;

    return 0;
}