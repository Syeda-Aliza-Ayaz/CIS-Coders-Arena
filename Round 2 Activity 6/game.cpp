#include<iostream>
#include<vector>
#include<stdexcept>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include <fstream>
using namespace std;
// MAKE SURE TO READ INSTRUCTIONS.TXT FIRST
ofstream logFile("game_log.txt", ios::trunc);

void logEvent(const string& message) {
    logFile << message << endl;
}

string tolower(string str){
    string result = "";
    for(char ch : str){
        result += tolower(ch);
    }
    return result;
}

// Class Player
class Player{
    private:
        int coins;
        int lives;
        string lastLocation;
        vector<string> party;
        vector<string> treasure_items = {"trap", "health", "coins"};
    public:
        Player(){ //initial conditions
            coins = 10;
            lives = 3;
            lastLocation = "";
        }
        void addCoins(int amount){
            coins += amount;
            cout << "🎉" << amount << " coins added. Total Coins: " << coins << endl;
            logEvent("🎉 Added " + to_string(amount) + " coins. Total: " + to_string(coins));
        }
        void loseCoins(int amount){
            if(amount < coins){
                coins -= amount;
                cout << "😢" << amount << " coins lost. Total Coins: " << coins << endl;
                logEvent("😢 Lost " + to_string(amount) + " coins. Total: " + to_string(coins));
            }
            else{
                throw invalid_argument("Cannot have negative coins");
            }
        }
        void gainLife(){
            lives++;
            cout << "✨ You gained a life! Lives remaining: " << lives << endl;
            logEvent("✨ Gained a life. Lives remaining: " + to_string(lives));
        }
        void loseLife(){
            lives--;
            cout << "🗡️ You lost a life! Lives remaining: " << lives << endl;
            logEvent("🗡️ Lost a life. Lives remaining: " + to_string(lives));
        }
        bool checkWinCondition(){
            if(coins >= 30 && lives >= 1 && hasPartyMember("warrior") && (hasPartyMember("mage") || hasPartyMember("healer"))){
                return true;
            }
            else{
                return false;
            }
        }
        bool checkLoseCondition(){
            if(lives <= 0){
                return true;
            }
            else{
                return false;
            }
        }
        bool hasPartyMember(string name){
            for(auto& player : party){
                if(player == tolower(name)){
                    return true;
                }
            }
            return false;
        }
        void addToParty(string player){
            player = tolower(player);
            if(find(party.begin(), party.end(), player) == party.end()){
                party.push_back(player);
                cout << "🧑‍🤝‍🧑 " << player << " joined your party!" << endl;
                logEvent("🧑‍🤝‍🧑 " + player + " joined your party.");
            }
        }
        void setLocation(const string& loc){
            lastLocation = loc;
        }
        int getLives(){
            return lives;
        }
        int getCoins(){
            return coins;
        }
        string getLocation(){
            return lastLocation;
        }
        vector<string> getParty() {
            return party;
        }
        string getTreasureItem(int index){
            return treasure_items[index];
        }
        void showStatus(){
            cout << "-----------------------------------------------------------\n";
            cout << "🧍 Coins: " << coins << ", Lives: " << lives;
            if(!party.empty()){
                cout << ", Party: ";
                for(auto member : party){
                    cout << member << " ";
                }
            }
            cout << endl;
            cout << "-----------------------------------------------------------\n";
        }
};
void logSummary(Player& player, bool won);
void checkLives(Player& player){
    if (player.checkLoseCondition()) {
        cout << "☠️ Game Over! You ran out of lives." << endl;
        logEvent("☠️ Player died. Game over.");
        logSummary(player, false);
        exit(0); // Force stop
    }
}

int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        else {
            cout << "❌ Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            cin.clear(); // clear failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        }
    }
}

string getYesOrNo() {
    string input;
    while (true) {
        cout << "(yes/no): ";
        getline(cin, input);
        input = tolower(input);
        if (input == "yes" || input == "no") {
            return input;
        }
        else {
            cout << "❌ Invalid input. Please type 'yes' or 'no'.\n";
        }
    }
}

void logSummary(Player& player, bool won){
    logEvent("\n📜 GAME SUMMARY 📜");
    logEvent("------------------------");
    logEvent(won ? "🏆 YOU WON!" : "💀 YOU DIED!");
    logEvent("📍 Final Location: " + player.getLocation());
    logEvent("🪙 Coins Collected: " + to_string(player.getCoins()));
    logEvent("❤️ Lives Remaining: " + to_string(player.getLives()));
    string party = "🧑‍🤝‍🧑 Party Members: ";
    if (player.getParty().empty()) party += "None";
    else {
        for (const string& member : player.getParty()) {
            party += member + " ";
        }
    }
    logEvent(party);
    logEvent("------------------------\n");
}


void village(Player& player);
void tavern(Player& player);
void forest(Player& player);
void mountains(Player& player);
void treasureRoom(Player& player);

//Village
void village(Player& player){
    player.showStatus();
    player.setLocation("Village");
    cout << "🏘️  You are in \"VILLAGE\"\n---------------------------\nWhere would you like to go next?\n";
    logEvent("🏘️ Player entered the Village.");
    cout << "1. Travern\n2. Forest\n3. Mountains\n4. Treasure Room" << endl;
    int choice = getValidatedChoice(1, 4);
    switch(choice){
        case 1:{
            tavern(player);
            break;
        }
        case 2:{
            forest(player);
            break;
        }
        case 3:{
            mountains(player);
            break;
        }
        case 4:{
            treasureRoom(player);
            break;
        }
        default:{
            cout << "❌ Invalid choice.\n";
            village(player);
            break;
        }
    }
}

//Travern
void tavern(Player& player){
    cout << "🍺 You are in \"TAVERN\"\n---------------------------\n";
    logEvent("🍺 Player entered the Tavern.");
    player.setLocation("Tavern");
    if(!player.hasPartyMember("warrior")){
        cout << "You met a \"WARRIOR\"\n";
        logEvent("🥷🏻 Player met a warrior.");
        int outcome = rand() % 2;
        if(outcome && !player.hasPartyMember("warrior")){
            cout << "🎉 \"WARRIOR\" joins you for free!" << endl;
            player.addToParty("warrior");
            logEvent("🥷🏻 Warrior joined for free.");
        }
        else{
            cout << "💰 \"WARRIOR\" asks 10 coins. Do you agree to give? ";
            string decision = getYesOrNo();
            if(tolower(decision) == "yes"){
                try {
                    player.loseCoins(10);
                    player.addToParty("warrior");
                    logEvent("🥷🏻 Warrior joined for 10 coins.");
                } 
                catch(...) {
                    cout << "❌ Not enough coins.\n";
                    logEvent("🥷🏻 Warrior could not join as player is out of coins.");
                }
            }
            else{
                cout << "👋 \"WARRIOR\" walks away.\n";
                logEvent("🥷🏻 Warrior did not join.");
            }
        }
    }
    else{
        cout << "🧑‍🤝‍🧑 Warrior is already with you.\n";
        logEvent("🥷🏻 Warrior is already with you.");
    }
    cout << "-----------------------------------------\n";
    player.showStatus();
    cout << "Where would you like to go next?\n";
    cout << "1. Forest\n2. Mountains\n3. Treasure Room\n4. Return to Village" << endl;
    int choice = getValidatedChoice(1, 4);
    switch(choice){
        case 1:{
            forest(player);
            break;
        }
        case 2:{
            mountains(player);
            break;
        }
        case 3:{
            treasureRoom(player);
            break;
        }
        case 4:{
            village(player);
            break;
        }
        default:{
            cout << "❌ Invalid choice.\n";
            tavern(player);
            break;
        }
    }
}

// Forest
void forest(Player& player){
    cout << "🌲 You enter the \"FOREST\"\n---------------------------\n";
    logEvent("🌲 Player entered the Forest.");
    player.setLocation("Forest");
    int outcome = rand() % 2;
    switch(outcome){
        case 0:{
            cout << "🎁 You found a chest! Do you want to open it? ";
            string decision = getYesOrNo();
            if(tolower(decision) == "yes"){
                int index = rand() % 3;
                string reveal = player.getTreasureItem(index);
                logEvent("🎁 Player opened the chest.");
                if(reveal == "trap"){
                    cout << "💔 You fell into a trap!" << endl;
                    logEvent("💔 Player fell into trap.");
                    player.loseLife();
                    checkLives(player);
                }
                else if(reveal == "coins"){
                    cout << "🪙 You found 20 coins!" << endl;
                    logEvent("🪙 Player found 20 coins.");
                    player.addCoins(20);
                }
                else{
                    cout << "❤️‍🩹 You found health potion!" << endl;
                    logEvent("❤️‍🩹 Player found health potion.");
                    player.gainLife();
                }
            }
            break;
        }
        case 1:{
            if(!player.hasPartyMember("mage")){
                cout << "🧙‍♂️ You met \"MAGE\"! Get into conversation? ";
                logEvent("🧙‍♂️ Player met a mage.");
                string decision = getYesOrNo();
                if(tolower(decision) == "yes"){
                    cout << "----------------------------------------\n";
                    cout << "MAGE: Hello my child! Pay me 15 coins and I will join you.\n";
                    cout << "YOU: ";
                    string yes_no = getYesOrNo();
                    if(tolower(yes_no) == "yes"){
                        try {
                            player.loseCoins(15);
                            player.addToParty("mage");
                            cout << "👨🏻‍🤝‍🧑🏻 \"MAGE\" joined you!\n";
                        } 
                        catch(...){
                            cout << "❌ Not enough coins.\n";
                        }
                    }
                    else{
                        logEvent("🧙‍♂️ Mage left.");
                        cout << "☹️ \"MAGE\" vanishes in mist!\n";
                    }
                }
                else{
                    logEvent("🧙‍♂️ Mage left.");
                    cout << "☹️ \"MAGE\" left!\n";
                }
            }
            else{
                logEvent("🧙‍♂️ Mage is already in the party.");
                cout << "🧙‍♂️ \"MAGE\" is already with you!\n";
            }
            break;   
        }
    }
    player.showStatus();
    cout << "Where would you like to go next?\n";
    cout << "1. Mountains\n2. Treasure Room\n3. Return to Village\n4. Return to Tavern" << endl;
    int choice = getValidatedChoice(1, 4);
    switch(choice){
        case 1:{
            mountains(player);
            break;
        }
        case 2:{
            treasureRoom(player);
            break;
        }
        case 3:{
            village(player);
            break;
        }
        case 4:{
            tavern(player);
            break;
        }
        default:{
            cout << "Invalid choice.\n";
            forest(player);
            break;
        }
    }
}

// Mountains
void mountains(Player& player){
    cout << "🏔️ You climb into \"MOUNTAINS\"\n---------------------------\n";
    logEvent("🏔️ Player climbed mountains.");
    player.setLocation("Mountains");
    int outcome = rand() % 2;
    switch(outcome){
        case 0:{
            cout << "☀️ LUCKY YOU! The weather is \"SUNNY\"." << endl;
            logEvent("☀️ It is sunny in mountains.");
            if(player.getLives() >= 2){
                int random = rand() % 2;
                if(random && !player.hasPartyMember("healer")){
                    cout << "👨🏻‍⚕️ \"HEALER\" joined you!" << endl;
                    player.addToParty("healer");
                    player.gainLife();
                }
            }
            break;
        }
        case 1:{
            cout << "⛈️ BEWARE! The weather is \"RAINY\"." << endl;
            logEvent("⛈️ It is rainy in mountains.");
            if(player.hasPartyMember("mage")){
                cout << "🪄 MAGE SAVED YOU FROM SLIPPING OFF THE MOUNTAIN!" << endl;
                logEvent("🫱🏻‍🫲🏼 Player survived in mountains.");
            }
            else{
                cout << "💀 POOR YOU! There was no one to save you from falling! You fell off!" << endl;
                logEvent("💀 Player slipped.");
                player.loseLife();
                checkLives(player);
            }
            break;
        }
    }
    player.showStatus();
    cout << "Where would you like to go next?\n";
    cout << "1.Treasure Room\n2. Return to Village\n3. Return to Tavern\n4. Return to Forest" << endl;
    int choice = getValidatedChoice(1, 4);
    switch(choice){
        case 1:{
            treasureRoom(player);
            break;
        }
        case 2:{
            village(player);
            break;
        }
        case 3:{
            tavern(player);
            break;
        }
        case 4:{
            forest(player);
            break;
        }
        default:{
            cout << "Invalid choice.\n";
            mountains(player);
            break;
        }
    }
}

//Treasure Room
void treasureRoom(Player& player){
    cout << "💰 You are in \"TREASURE ROOM\"\n---------------------------\n";
    logEvent("💰 Player entered treasure room.");
    player.setLocation("Treasure Room");
    if(player.checkWinCondition()){
        cout << "🎉 You met all win conditions!\n🏆 CONGRATULATIONS, YOU WIN!\n";
        logEvent("🏆 Player WON!");
        logSummary(player, true);
        player.showStatus();
        exit(0); // Game ends
    }
    else{
        cout << "🚫 You do not meet winning requirements!" << endl;
        logEvent("🚫 Player did not win.");
    }
    player.showStatus();
    cout << "Where would you like to go back?\n";
    cout << "1. Return to Village\n2. Return to Tavern\n3. Return to Forest\n4. Return to Mountains" << endl;
    int choice = getValidatedChoice(1, 4);
    switch(choice){
        case 1:{
            village(player);
            break;
        }
        case 2:{
            tavern(player);
            break;
        }
        case 3:{
            forest(player);
            break;
        }
        case 4:{
            mountains(player);
            break;
        }
        default:{
            cout << "Invalid choice.\n";
            treasureRoom(player);
            break;
        }
    }
}

int main(int argc, char* argv[]){
    system("chcp 65001");
    srand(time(0));
    Player player;
    cout << "🎮 Welcome to the Adventure Quest Game!\n";
    logEvent("🎮 GAME BEGINS!");
    while(!player.checkWinCondition() && !player.checkLoseCondition()){
        village(player);
    }
    // if(player.checkLoseCondition()){
    //     logEvent("☠️ Player died. Game over.");
    //     logSummary(player, false);
    // }

    logFile.close();
    return 0;
}