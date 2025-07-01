#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
int compute_score1(string word1, vector<int> points){
	int score1 = 0;
	// calculate score of word 1
	for(int i = 0; i < word1.length(); i++){
		if(isalpha(word1[i]))
			score1 += points[toupper(word1[i]) - 'A'];
	}
	return score1;
}

int compute_score2(string word2, vector<int> points){
	int score2 = 0;
	//calculate score of word 2
	for(int i = 0; i < word2.length(); i++){
		if(isalpha(word2[i]))
			score2 += points[toupper(word2[i]) - 'A'];
	}
	return score2;
}

void compute_round_result(int score1, int score2, string player1Name, string player2Name){
	if(score1 < score2){
		cout << player2Name << " wins this round!" << endl;
		cout << "Scores: " << player1Name << " = " << score1 << ", " << player2Name << " = " << score2 << endl;
	}
	else if(score1 > score2){
		cout << player1Name << " wins this round!" << endl;
		cout << "Scores: " << player1Name << " = " << score1 << ", " << player2Name << " = " << score2 << endl;
	}
	else{
		cout << "Tie!" << endl;
		cout << "Scores: " << player1Name << " = " << score1 << ", " << player2Name << " = " << score2 << endl;
	}
	return;
}


int main(int argc, char** argv) {
	// Points assigned to each letter
						//A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q,  R, S, T, U, V, W, X, Y,  Z
	vector<int> points = {1, 3, 4, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	string word1, word2, player1Name, player2Name;
	cout << "=========== SCRABBLE TOURNAMENT ===========" << endl;
	cout << "Player 1 name (default: Player1): ";
	getline(cin, player1Name);
	cout << "Player 2 name (default: Player2): ";
	getline(cin, player2Name);
	if(player1Name.empty()){
	    player1Name = "Player1";
	}
	if(player2Name.empty()){
	    player2Name = "Player2";
	}
	
	cout << "Enter the number of rounds in this contest: ";
	int rounds;
	cin >> rounds;
	cout << "==========================================" << endl << endl;
	
	int score1 = 0, score2 = 0;
	int totalScore1 = 0, totalScore2 = 0, highestScore1 = 0, highestScore2 = 0, longestWord1 = 0, longestWord2 = 0;
	
	for (int i = 1; i <= rounds; i++) {
		cout << endl;
		cout << "--------- Round " << i << " ---------" << endl;
		cout << player1Name << ": ";
		cin >> word1;
		cout << player2Name << ": ";
		cin >> word2;
		
		//round result
		score1 = compute_score1(word1, points);
		score2 = compute_score2(word2, points);
		compute_round_result(score1, score2, player1Name, player2Name);
		
		//totalScore
		totalScore1 += score1;
		totalScore2 += score2;
		
		//highestScore evaluation
		if(highestScore1 < score1){
			highestScore1 = score1;
		}		
		
		if(highestScore2 < score2){
			highestScore2 = score2;
		}
		
		//longestWord
		if(longestWord1 < word1.length()){
			longestWord1 = word1.length();
		}
		
		if(longestWord2 < word2.length()){
			longestWord2 = word2.length();
		}
	}
	cout << "==========================================" << endl << endl;
	cout << "=================== FINAL TOURNAMENT RESULTS ===================" << endl;
	cout << player1Name << ": Total = " << totalScore1 << ", Highest Score = " << highestScore1 << ", Longest Word Length = " << longestWord1 << endl;
	cout << player2Name << ": Total = " << totalScore2 << ", Highest Score = " << highestScore2 << ", Longest Word Length = " << longestWord2 << endl;
	
	//final evaluation
	if(totalScore1 > totalScore2){
		cout << player1Name << " wins the tournament!" << endl;
	}
	else if(totalScore1 < totalScore2){
		cout << player2Name << " wins the tournament!" << endl;
	}
	else{
		if(highestScore1 > highestScore2){
			cout << player1Name << " wins the tournament!" << endl;
		}
		else if(highestScore1 < highestScore2){
			cout << player2Name << " wins the tournament!" << endl;
		}
		else{
			if(longestWord1 > longestWord2){
				cout << player1Name << " wins the tournament!" << endl;
			}
			else if(longestWord1 < longestWord2){
				cout << player2Name << " wins the tournament!" << endl;
			}
			else{
				cout << "The tournament ends in a TIE!" << endl;
			}
			
		}
	}
	
	return 0;
}