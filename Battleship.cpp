#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#define BRIGHT 1
#define RED 31
#define BG_BLACK 40
using namespace std;

const int numSubs = 2;
const int numDest = 2;
const int numB  = 1;
const int numH = 1;
const int sizeS = 1;
const int sizeD = 2;
const int sizeB = 3;
const int sizeH = 5;
bool isOver = false;
int p1Hits = 0; //hits on p1's board
int p2Hits = 0; //hits on p2's board
string p1[10][10];
string p2[10][10];
string p1guess[10][10];
string p2guess[10][10];

void printBoard(string arr[10][10], int player){
	
	cout << "                                   Player " << player << endl << " ";
	for(int i = 0; i < 10; i ++){
		cout << "                             ";
		for(int j = 0; j < 10; j ++){
			
			cout << arr[i][j] + " ";
			if(j == 9){cout << endl;}
		}
	}
}

void initBoard(string arr[10][10]){
	for(int col = 1; col < 10; col ++){
		arr[0][col] = std::to_string(col);
		arr[col][0] = std::to_string(col);
	}
	for(int i = 1; i < 10; i ++){
		for(int j = 1; j < 10; j ++){
			arr[i][j] = "*";
		}
	}
}

void initGuessBoard(string arr[10][10]){
	for(int i = 1; i < 10; i ++){
		for(int j = 1; j < 10; j ++){
			arr[i][j] = "*";
		}
	}
}

void selectShipLocation(string board[10][10], int player){
	cout << endl << "You have two subs ( S ), two destroyers ( D D ), one battleship ( B B B )" << endl << "and one S.H.I.E.L.D. helicarrier ( H H H H H )" << endl;
	cout << "To place a ship, first select a coordinate pair, and then select an orientation" << endl;
	cout << "For example, let's place a destroyer ( D D ) on the square (2,3)" << endl << "and then orient it to the right" << endl;
	cout << "When prompted, I would enter the number 2, and then I would enter the number 3" << endl; 
	cout << "After that, I would enter D, since I want to orient the destroyer to the right" << endl;
	cout << "This last part uses the A-W-S-D key format. A = left, W = up, S = down, and D = right" << endl;
	for(int s = 0; s < numSubs; s ++){
		cout << endl << "Submarine #" << s + 1 << endl;
		cout << "Enter row: ";
		int xCoor; cin >> xCoor;
		cout << "Enter column: ";
		int yCoor; cin >> yCoor;
		//cout << "Enter orientation: ";
		//string orien; cin << orien;
		board[xCoor][yCoor] = "S";
		system("clear");
		printBoard(board, player);
	}
	for(int d = 0; d < numDest; d ++){
		cout << endl << "Destroyer #" << d + 1 << endl;
		cout << "Enter row: ";
		int xCoor; cin >> xCoor;
		cout << "Enter column: ";
		int yCoor; cin >> yCoor;
		board[xCoor][yCoor] = "D";
		cout << "Enter orientation: ";
		string orien; cin >> orien;
		if(orien == "A"){yCoor = yCoor - 1;}
		else if(orien == "W"){xCoor = xCoor - 1;}
		else if(orien == "S"){xCoor ++;}
		else if(orien == "D"){yCoor ++;}	
		board[xCoor][yCoor] = "D";
		system("clear");
		printBoard(board, player);
	}
	for(int b = 0; b < numB; b ++){
		cout << endl << "Battleship" << endl;
		cout << "Enter row: ";
		int xCoor; cin >> xCoor;
		cout << "Enter column: ";
		int yCoor; cin >> yCoor;
		board[xCoor][yCoor] = "B";
		cout << "Enter orientation: ";
		string orien; cin >> orien;
		for(int i = 0; i < 2; i ++){
			if(orien == "A"){yCoor = yCoor - 1;}
			else if(orien == "W"){xCoor = xCoor - 1;}
			else if(orien == "S"){xCoor ++;}
			else if(orien == "D"){yCoor ++;}
			board[xCoor][yCoor] = "B";
		}
		system("clear");
		printBoard(board, player);
	}
	for(int h = 0; h < numH; h ++){
		cout << endl << "S.H.I.E.L.D. Helicarrier" << endl;
		cout << "Enter row: ";
		int xCoor; cin >> xCoor;
		cout << "Enter column: ";
		int yCoor; cin >> yCoor;
		board[xCoor][yCoor] = "H";
		cout << "Enter orientation: ";
		string orien; cin >> orien;
		for(int i = 0; i < 4; i ++){
			if(orien == "A"){yCoor = yCoor - 1;}
			else if(orien == "W"){xCoor = xCoor - 1;}
			else if(orien == "S"){xCoor ++;}
			else if(orien == "D"){yCoor ++;}
			board[xCoor][yCoor] = "H";
		}
		system("clear");
		printBoard(board, player);
	}
}

bool isover(){
	if(p1Hits == 14 || p2Hits == 14){return true;}
	return false;
}

void makeTurn(int num){
	system("clear");
	if(num == 1){printBoard(p1guess, num);}
	else{printBoard(p2guess, num);}
	cout << "Player " << num << ", make a guess!" << endl;
	cout << "Row:" << endl; int row; cin >> row;
	cout << "Column:" << endl; int col; cin >> col;
	if(num == 1){
		if(p2[row][col] != "*"){
			cout << "You got a hit!" << endl;
			p2Hits ++;
			p1guess[row][col] = "X";
			p2[row][col] = "*";
			usleep(1000000);
		}else{
			cout << "You missed!" << endl;
			p1guess[row][col] = "O";
			usleep(1000000);
		}
	}else{
		if(p1[row][col] != "*"){
			cout << "You got a hit!" << endl;
			p1Hits ++;
			p2guess[row][col] = "X";
			p1[row][col] = "*";
			usleep(1000000);
		}else {
			cout << "You missed!" << endl;
			p2guess[row][col] = "O";
			usleep(1000000);
		}
		
	}
}

void game(string p1[10][10], string p2[10][10]){
	while(isOver == false){
		makeTurn(1);
		if(isover()){
			isOver = true;
			cout << "Congratulations, Player 1! You won!" << endl;
		}
		makeTurn(2);
		if(isover()){
			isOver = true;
			cout << "Congratulations, Player 2! You won!" << endl;
		}
	}
}

int main(){
	printf("%c[%d;%d;%dm", 0x1B, BRIGHT,RED,BG_BLACK); //print something in red
	printf("%c[%dm", 0x1B, 0);  //reset color
	initGuessBoard(p1guess);
	initBoard(p1);
	printBoard(p1, 1);
	selectShipLocation(p1, 1);
	usleep(1000000);
	initGuessBoard(p2guess);
	initBoard(p2);
	printBoard(p2, 2);
	selectShipLocation(p2, 2);
	usleep(1000000);
	game(p1, p2);
}
