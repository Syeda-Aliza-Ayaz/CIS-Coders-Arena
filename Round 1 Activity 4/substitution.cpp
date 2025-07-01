#include<iostream>
#include<map>
#include<set>
#include<string>
#include<cctype>
#include<stdexcept>
using namespace std;

//argc = argument count in command line // argv = vector holding the argument text
int main(int argc, char* argv[]){
    try{
        // command line arguments validation
        if(argc != 2){
            throw invalid_argument("The usage should be \"./substitution_cipher KEY\"");
        }
        
        // key validation
        string text = argv[1];
        if(text.size() == 26){
            set<char> seen;
            for(char ch : text){
                char lower_ch = tolower(ch);
                if(!isalpha(lower_ch)){
                    throw invalid_argument("The key must only contain English alphabets.");
                }
                else if(seen.count(lower_ch)){
                    throw invalid_argument("The key must be unique i.e. no repeated characters allowed.");
                }
                seen.insert(lower_ch);
            }
        }
        else{
            throw invalid_argument("Key size must be 26 characters.");
        }

        // cipher mapping
        map<char, char> cipher_map;
        for(int i = 0; i < 26; i++){
            cipher_map['A' + i] = toupper(text[i]);
            cipher_map['a' + i] = tolower(text[i]);
        }

        //conversion
        string input, output;
        cout << "Enter the word to encrypt: ";
        // cin.ignore();
        getline(cin, input);
        for(char ch : input){
            if(isalpha(ch)){
                output.push_back(cipher_map[ch]);
            }
            else{
                output.push_back(ch);
            }
        }
        cout << "Encrypted Text: " << output << endl;
    }
    catch(const exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}