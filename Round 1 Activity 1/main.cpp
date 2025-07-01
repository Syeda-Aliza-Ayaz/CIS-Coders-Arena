#include <iostream>
#include <cctype>
#include <string>
using namespace std;
int main(int argc, char** argv) {
	int n;
	cout << "Enter the height of pyramid (a number between 1 and 8 inclusive): ";
	cin >> n;
	bool isN = false;
	while(!isN){
		if(n > 0 && n < 8){
			isN = true;
			break;
		}
		cout << "Please enter a valid number: ";
		cin >> n;
	}
	//printing pyramid
        for(int i = 0; i < n; i++){ //controls complete pattern printing
            for(int s = 0; s < n - i - 1; s++){ // controls printing of dots of left-pyramid
                cout << ".";
            }
            for(int j = 0; j < i + 1; j++){ //controls prinitng of # of left-pyramid
                cout << "#";
                if(i == 0){ //controls prinintg of bridge
                    cout << " ";
                    for(int i = 0; i < n; i++){
                        cout << "=";
                    }
                    cout << " ";
                }
            }
            
            if(i > 0){ //controls printing of middle dots
            	cout << " ";
	            for(int m = 0; m < n; m++){
	                cout << ".";
	            }
            	cout << " ";
			}
			
            for(int j = 0; j < i + 1; j++){ //controls printing of # of right pyramid
                cout << "#";
            }
            for(int s = 0; s < n - i - 1; s++){ //controls printing of dots of right pyramid
                cout << ".";
            }
            cout << endl;
        }
	return 0;
}