#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
const int width = 60;
const int height = 20;
 
void newBoard(bool** board) {
	//Alokacja pamięci na tablicę.
	board = new bool*[height];
	for (int i = 0; i < height; i++) {
		board[i] = new bool[width];
		for (int j = 0; j < width; j++) {
			board[i][j] = false;
		}
	}
}
 
void deleteBoard(bool**board) {
	if (board == NULL) return;
	for (int i = 0; i < height; i++) {
		delete[] board[i];
	}
	delete[] board;
}
 
bool checkPercent(bool**board, int userPercent) {
	int howMany = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j]) howMany++;
		}
	}
	float percent;
	percent = (float)howMany / (width*height);
	return percent * 100 <= userPercent ? true : false;
}
 
void reset(bool**board) {
	deleteBoard(board);
	newBoard(board);
	int userPercent, x, y;
	scanf("%d", &userPercent);
	if (userPercent > 100) userPercent = 99;
	if (userPercent < 0) userPercent = 1;
 
	while (checkPercent(board, userPercent)) {
		x = rand() % width;
		y = rand() % height;
		board[y][x] = true;
	}
 
}
 
bool checkIfInBorder(int width, int height, int x, int y) {
	if (x < 0 || y < 0 || x >= width || y >= height)return false;
	return true;
}
 
void checkConditions(bool**board) {
	int howManyAround = 0;
	bool** tempBoard;
	//Preparing temporary board
	tempBoard = new bool*[height];
	for (int i = 0; i < height; i++) {
		tempBoard[i] = new bool[width];
		for (int j = 0; j < width; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}
	//Checking conditions
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					if (checkIfInBorder(width, height, j + l - 1, i + k - 1)) {
						if (k == 1 && l == 1) continue;
						if (board[i + k - 1][j + l - 1]) howManyAround++;
					}
				}
			}
			if (howManyAround == 3) tempBoard[i][j] = true;
			else if (howManyAround < 2 || howManyAround > 3) tempBoard[i][j] = false;
			howManyAround = 0;
		}
	}
	//Copying temporary board to our board and deleting temp
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j] = tempBoard[i][j];
		}
	}
 
	for (int i = 0; i < height; i++) {
		delete[] tempBoard[i];
	}
	delete[] tempBoard;
}
 
void nextStep(bool**board) {
	system("cls");
	checkConditions(board);
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (i == 0 || i == height + 1) printf("-");
			else if (j == 0 || j == width + 1) printf("|");
			else {
				if (board[i - 1][j - 1]) printf("x");
				else printf(" ");
			}
		}
		printf("\n");
	}
 
 
}
 
int main() {
	//Zmienne
	bool quit = false;
	bool** board;
	char sign;
	//Alokacja pamięci na tablicę.
	board = new bool*[height];
	for (int i = 0; i < height; i++) {
		board[i] = new bool[width];
		for (int j = 0; j < width; j++) {
			board[i][j] = false;
		}
	}
	srand(time(NULL));
	reset(board);
	//Pętla głowna aplikacji.
	do {
		sign = getchar();
 
		if (sign == 'q' || sign == 'Q') quit = true;
		else if (sign == 'r' || sign == 'R') reset(board);
		else nextStep(board);
 
 
	} while (!quit);
 
	return 0;
}