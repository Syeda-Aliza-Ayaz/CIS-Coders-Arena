#include <iostream>
#include <cctype>
#include <map>
#include <iomanip>

using namespace std;

string title(string item){
	if (item.empty())
    	return item;

	item[0] = toupper(item[0]);
	for(int i = 1; i < item.size(); i++){
		item[i] = tolower(item[i]);
	}
	return item;
}

int main(int argc, char** argv) {
	map<string, double> menu; //item, prices
	map<string, int> order; //user ka saamaan
	cout << fixed << setprecision(2);

	menu = {
	    {"Bread", 2.50},
	    {"Milk", 1.75},
	    {"Eggs", 3.00},
	    {"Rice", 5.25},
	    {"Sugar", 4.00},
	    {"Salt", 0.99},
	    {"Tea", 2.20},
	    {"Coffee", 4.50},
	    {"Chicken", 8.75},
	    {"Beef", 10.00},
	    {"Apples", 3.20},
	    {"Bananas", 1.80},
	    {"Oranges", 2.60},
	    {"Potatoes", 1.50},
	    {"Tomatoes", 2.00},
	    {"Onions", 1.20},
	    {"Oil", 6.50},
	    {"Butter", 3.75},
	    {"Cheese", 4.20},
	    {"Yogurt", 2.00}
	};
	cout << "WELCOME TO IMTIAZ BILLING COUNTER!\nItems available in our shopping store are listed below:\n";
	for(auto& it : menu){
		cout << it.first << ": $" << it.second << endl;
	}
	cout << "==============================================================\n";
	cout << "Enter the items bought by user (Type Ctrl+Z to finish input):\n";
	string item;
	double total = 0;
	cout << "Item: ";
	while(cin >> item){
		item = title(item);
		if(menu.count(item)){
			order[item]++;
			total += menu[item];
		}
		cout << "Item: ";
	}
	cin.clear();
	cout << "----------------- Final Bill -----------------\n";
	for(auto& item : order){
		cout << item.first << " x" << item.second << " @ $" << menu[item.first] << " = " << (menu[item.first] * item.second) << endl;
	}
	cout << "-----------------------------------------------\n";
	cout << "Total Due: $" << total << endl << endl;
	cout << "Enter the amount paid by user: ";
	double payment;
	cin >> payment;
	double change = payment - total;
	cout << "Change: $" << change << endl << endl;
	
	cout << "----------------- Receipt -----------------\n";
	cout << "Paid: $" << payment << endl;
	cout << "Total: $" << total << endl;
	cout << "Change: $" << change << endl;
	cout << "-------------------------------------------\n\n";
	cout << "Thank you for shopping at Imtiaz Supermarket!" << endl;
	return 0;
}