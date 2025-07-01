#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;
int main(int argc, char** argv) {
	bool valid = false; //controls validity of inputs
	int numStruct; // 1 to 3
	char structType; // t=triangle or s=square
	int height; // 1 to 10
	string chr; // character to build pattern
	char triangleAlignment; // l=left or r=right
	cout << "Number of Structures (between 1 and 3 inclusive): ";
	cin >> numStruct;
	while(!valid){
		if(numStruct > 0 && numStruct < 4){
			valid = true;
			break;
		}
		cout << "Please enter valid number of structures: ";
		cin >> numStruct;
	}
	valid = false;
	//structure holding variables
	vector<vector<string>> all_struct;
	vector<string> structure;
	//structure information and building loop
	vector<int> structureWidths; // stores max width (which is equal to height of each shape)
	for(int i = 0; i < numStruct; i++){
		cout << "Structure " << i + 1 << ":" << endl;
		cout << "Type (\'t\' for triangle and \'s\' for square): ";
		cin >> structType;
		while(!valid){
			structType = tolower(structType);
			if(structType == 's' || structType == 't'){
				valid = true;
				break;
			}
			cout << "Please enter valid structure type: ";
			cin >> structType;
		}
		valid = false;
		cout << "Height (between 1 to 10 inclusive): ";
		cin >> height;
		while(!valid){
			if(height >= 1 && height <= 10){
			valid = true;
			break;
		}
		cout << "Please enter valid height: ";
		cin >> height;
		}
		structureWidths.push_back(height);
		valid = false;
		cin.ignore();
		cout << "Character: ";
		getline(cin, chr);
		while(chr.length() != 1){
			cout << "Please enter a single character: ";
			getline(cin, chr);
		}
		char character = chr[0]; // store the character
		if(structType == 't'){
			cout << "Align (\'l\' for left and \'r\' for right): ";
			cin >> triangleAlignment;
			while(!valid){
				triangleAlignment = tolower(triangleAlignment);
				if(triangleAlignment == 'l' || triangleAlignment == 'r'){
					valid = true;
					break;
				}
				cout << "Please enter valid alignment: ";
				cin >> triangleAlignment;
			}
			valid = false;
		}
		//structure storage
		if(structType == 't'){
			if(triangleAlignment == 'l'){
				for(int i = 0; i < height; i++){
					string line(i + 1, character);
					structure.push_back(line);
					// cout << line;
					// cout << endl;
				}
				all_struct.push_back(structure);
				structure.clear();
			}
			else if(triangleAlignment == 'r'){
				for (int i = 0; i < height; i++) {
					string line = string(height - i - 1, ' ') + string(i + 1, character);
				    structure.push_back(line);
				}

				all_struct.push_back(structure);
				structure.clear();
			}
		}
		else if(structType == 's'){
			for(int i = 0; i < height; i++){
				string line(height, character);
				// cout << line;
				// cout << endl;
				structure.push_back(line);
			}
			all_struct.push_back(structure);
			structure.clear();
		}
	}
	//max height
	int maxHeight = all_struct[0].size();
	for(int j = 0; j < all_struct.size(); j++){
		if(maxHeight < all_struct[j].size()){
			maxHeight = all_struct[j].size();
		}
	}

	//print shapes
	for(int row = 0; row < maxHeight; row++){ //number of rows to be printed is determined b maxHeight
	    for(int i = 0; i < all_struct.size(); i++){ // accessing structure
	        const auto& structure = all_struct[i];
	        if(row < structure.size()){
	            cout << structure[row];
	            cout << string(structureWidths[i] - structure[row].size(), ' ');
	        }
			else{
	            cout << string(structureWidths[i], ' ');
	        }
	        cout << "  "; // spacing between structures
	    }
	    cout << endl;
	}

	return 0;
}
