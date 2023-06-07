#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define fileName "teams.txt"

struct Player{
    string  name,
            team;
    int goals,
        yellowCards,
        redCards;
};

vector<Player> players;

void getPlayers(){
    players.clear();
    ifstream inputFile(fileName);
    if(!inputFile){
        cout << "Error : Unable to read the file!" << endl;
        return;
    }
    while( !inputFile.eof() ){
        Player player;
        inputFile >> player.name >> player.team >> player.goals >> player.yellowCards >> player.redCards ;
        if(player.name!="" && player.team!="")
            players.push_back(player);
    }
    inputFile.close();
}

void insertPlayer(){
    ofstream outputFile(fileName, ios::app);
    Player player;
    cout << "Enter Player's Name : ";
    cin >> player.name;
    cout << "Enter Player's Team : ";
    cin >> player.team;
    cout << "Enter Player's Goals Scored : ";
    cin >> player.goals;
    cout << "Enter Player's Yellow Cards : ";
    cin >> player.yellowCards;
    cout << "Enter Player's Red Cards : ";
    cin >> player.redCards;
    outputFile << "\n" << player.name << " " << player.team << " " << player.goals << " " << player.yellowCards << " " << player.redCards;
    players.push_back(player);
    getPlayers();
    outputFile.close();
}



void displayDetails(Player player){
    cout << player.name << " (" << player.team 
         << ") -- Goals : " << player.goals 
         << ", Yellow Cards : " << player.yellowCards 
         << " & Red Cards : " << player.redCards << endl;
}


void searchPlayer(){
    int count=0, status = 0;
    string name;
    cout << "Enter player's name : ";
    cin >> name;

    for( Player player : players){
        count++;
        if(player.name==name){
            displayDetails(player);
            status++;
        }
        else if (count==players.size() && status==0) {
            cout << "Player not found.\n";
        }
    }
}

void displayTeamDetails(){
    cout << "Team Detils are :-\n";
    vector<string> teams;
    for (auto player : players) {
        auto it = find(teams.begin(), teams.end(), player.team);
        if (it == teams.end()) {
            teams.push_back(player.team);
        }
    }
    for (auto team : teams) {
        int goals = 0;
        int yellow_cards = 0;
        int red_cards = 0;
        for (auto player : players) {
            if (player.team == team) {
                goals += player.goals;
                yellow_cards += player.yellowCards;
                red_cards += player.redCards;
            }
        }
        cout << team << " - Goals: " << goals << ", Yellow Cards: " << yellow_cards << ", Red Cards: " << red_cards << endl;
    }
    cout << endl;
}

// Function to display the menu and handle user input
void displayMenu() {
    int choice;
    do {
        // Display menu options
        cout << "Main Menu:-\n1. Display all players\n2. Search for a player\n";
        cout << "3. Insert a new player record\n4. Display team statistics\n5. Exit\n";

        // Get user input
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user input
        switch (choice) {

            // Display all players
            case 1: 
                cout << "Details of all players :-" << endl;
                for(auto player : players){
                    displayDetails(player);
                }
                cout << endl;
                break;

            // Search for a player
            case 2:
                searchPlayer();
                break;

            // Insert a new player record
            case 3:
                insertPlayer();
                break;

            // Display team statistics
            case 4:
                displayTeamDetails();
                break;

            // Exit the program
            case 5:
                cout << "Exiting program...\n";
                break;

            // Invalid input
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } 
    while (choice != 5);
}

int main(){    
    getPlayers();
    displayMenu();
    return 0;
}
