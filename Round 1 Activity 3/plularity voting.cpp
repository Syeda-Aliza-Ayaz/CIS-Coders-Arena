#include <iostream>
#include <cctype>
#include <map>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
string title(string name){
	if(name.empty())
		return name;
	name[0] = toupper(name[0]);
	for(int i = 1; i < name.size(); i++){
		name[i] = tolower(name[i]);
	}
	return name;
}
int main(int argc, char** argv) {
	int numOfCandidates, numOfVoters;
	cout << "Enter the number of candidates (less than 10): ";
	cin >> numOfCandidates;
	if(numOfCandidates > 9){
		cout << "The number of candidates must be less than 10" << endl;
		while(numOfCandidates > 9){
			cout << "Enter the number of candidates (less than 10): ";
			cin >> numOfCandidates;
		}
	}
	string nameCandidate;
	map<string, int> system;
	for(int i = 0; i < numOfCandidates; i++){
		cout << "Enter name of candidate " << i + 1 << ": ";
		cin >> nameCandidate;
		system[nameCandidate] = 0;
	}
	cout << "Enter the number of voters: ";
	cin >> numOfVoters;
	
	string name;
	for(int i = 0; i < numOfVoters; i++){
		cout << "Voter " << i + 1 << ", Enter the name of candidate you want to vote for: ";
		cin >> name;
		name = title(name);
		if (system.count(name)) {
		    system[name]++;
		}
	}
	cout << "Votes received for each candidate: " << endl;
	for(auto it = system.begin(); it != system.end(); it++){
		cout << it->first << ": " << it->second << " votes" << endl;
	}
	cout << "Winner(s): " << endl;
	int max_value = INT_MIN;
    string key_of_max = "";
    for (auto& pair : system) {
        if (pair.second > max_value) {
            max_value = pair.second;
            key_of_max = pair.first;
        }
    }
    
    for (auto& pair : system) {
        if (pair.second == max_value) {
            cout << pair.first << endl;
        }
    }
    
	return 0;
}