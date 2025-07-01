#include<iostream>
#include<string>
#include<cctype>
#include<ctime>
#include<cstdlib>

using namespace std;

// get level function
int getLevel(){
    int level;
    cout << "Enter level (1, 2, 3): ";
    cin >> level;
    while(level < 1 || level > 3){
       cout << "Invalid input! The levels can either be 1, 2 or 3. Try again!" << endl;
       cout << "Enter level (1, 2, 3): ";
       cin >> level; 
    }
    return level;
}

//random number generator
int generate_integer(int level){
    if(level == 1){
        return rand() % 10;
    }
    else if(level == 2){
        return rand() % 90 + 10;
    }
    else{
        return rand() % 900 + 100;
    }
}

int main(int argc, char* argv[]){
    srand(time(0));
    cout << "===============================================" << endl;
    cout << "\tLITTLE PROFESSOR'S MATHS GAME" << endl;
    cout << "===============================================" << endl;
    int level = getLevel();
    int score = 0, round = 10, i = 1, j = 0;
    while(round--){
        int num1 = generate_integer(level);
        int num2 = generate_integer(level);
        int answer = num1 + num2;
        int userAnswer;
        for(int tries = 0; tries < 3; tries++){
            cout << "Problem " << i << ": " << num1 << " + " << num2 << " = ";
            cin >> userAnswer;
            if(userAnswer != answer){
                cout << "EEE" << endl;
                if(tries == 2){
                    cout << "Answer: " << answer << endl;
                }
            }
            else{
                score++;
                break;
            }
        }
        i++;
    }

    cout << "Your final score: " << score << "/10" << endl;
    return 0;
}