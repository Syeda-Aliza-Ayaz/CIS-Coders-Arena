#include <iostream>
#include <vector>
#include <string>
using namespace std;
void compute_score(string word1, string word2, vector<int> points){
	int score1 = 0, score2 = 0;
	// calculate score of word 1
	for(int i = 0; i < word1.length(); i++){
		if(isalpha(word1[i]))
			score1 += points[toupper(word1[i]) - 'A'];
	}
	//calculate score of word 2
	for(int i = 0; i < word2.length(); i++){
		if(isalpha(word2[i]))
			score2 += points[toupper(word2[i]) - 'A'];
	}
	
	if(score1 < score2){
		cout << "Player 2 wins!" << endl;
	}
	else if(score1 > score2){
		cout << "Player 1 wins!" << endl;
	}
	else{
		cout << "Tie!" << endl;
	}
	return;
}
int main(int argc, char** argv) {
	// Points assigned to each letter
						//A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q,  R, S, T, U, V, W, X, Y,  Z
	vector<int> points = {1, 3, 4, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	string word1, word2;
	cout << "Player 1: ";
	cin >> word1;
	cout << "Player 2: ";
	cin >> word2;
	compute_score(word1, word2, points);
	return 0;
}