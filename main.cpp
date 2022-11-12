#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <string>

int nScreenWidth = 80;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)
int nFieldWidth = 12;
int nFieldHeight = 18;
int counter = 0;
int pos = 0;
int main()
{
	int score = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// Create Screen Buffer
	wchar_t* screen = new wchar_t[rows * columns];
	//wchar_t tempScreen = &screen;
	for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	pos = columns/2;
	//Block is a 4x4 vector of integers
	vector <vector<int>> mField(20);
	vector <vector<int>> tField(20);
	for (int i = 0; i < 20; i++) {
		mField[i] = vector<int>(20);
		tField[i] = vector<int>(20);
		for (int j = 0; j < 20; j++) {
			mField[i][j] = 0;
			tField[i][j] = 0;
		}
	}
	vector <vector<int>> block{
		{0,0,0,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0}
	};
	vector <vector<int>> block1{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	};
	vector <vector<int>> block2{
		{0,0,0,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0}
	};
	vector <vector<int>> block3{
		{0,0,0,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0}
	};
	vector <vector<int>> block4{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	};

	int inc = 0;
	int x = 10;
	int y = 0;
	int xt = x;
	int yt = y;
	int fdX = 0;
	int fdY = 0;
	int y_coord = 0;
	int x_coord = 0;
	wchar_t tempChar = L'0';
	bool vFlag = false;
	bool sFlag = false;
	bool lFlag = false;
	bool testFlag = false;
	bool hFlag = false;
	vector <vector <int>> fCoords{
		{0,0,0,0},
		{0,0,0,0}
	};
	int randNum[2] = { 1,1 };
	srand(time(0));
	//Collision Detection Code for Y-Pos
	//Check for blocks below y-pos
	/*
	*	Calcuations:
	*	Finds the mField coordinates of each component of the block
	*	
	*/
	bool isDone = false;
	while(isDone == false) {
		/*while (testFlag == false) {
			
			if (randNum[1] != randNum[0]) {
				testFlag = true;
			}
		}*/
		//Choosing a block
		if (randNum[1] == 0) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					block[i][j] = block1[i][j];
				}
			}
		}
		else if (randNum[1] == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					block[i][j] = block2[i][j];
				}
			}
		}
		else if (randNum[1] == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					block[i][j] = block3[i][j];
				}
			}
		}
		else if (randNum[1] == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					block[i][j] = block4[i][j];
				}
			}
		}
		
		while (!sFlag) {
			if (GetAsyncKeyState(0x41)) {
				xt = 0;
			} else if (GetAsyncKeyState(0x44)) {
				xt = 1; //increment x
			}
			else {
				xt = 2;
			}

			for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
			//Code for reseting
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					if (mField[i][j] == 1) {
						mField[i][j] = 0;
					}
				}
			}
			int fX = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[i][j] == 1) {
						//x value
						fCoords[0][fX] = x + j;
						//y value
						fCoords[1][fX] = y + i;
						fX++;
					}
				}
			}
			int cX = 0; int cY = 0;
			for (int i = 0; i < 4; i++) {
				cX = fCoords[0][i];
				cY = fCoords[1][i];
				//Error Handling for cY
				if (cY + 1 > 19) {
					vFlag = true;
					break;
				}
				else if (mField[cY + 1][cX] == 2) {
					vFlag = true; //Cannot Move, need to set the block
					if (cY < 4) {
						lFlag = true;
					}
					break;
				}
			}
			if (xt == 0) {
				for (int i = 0; i < 4; i++) {
					cX = fCoords[0][i];
					cY = fCoords[1][i];
					if (cX - 1 < 5) {
						hFlag = true;
						break;
					}
					else if (mField[cY][cX - 1] == 2) {
						hFlag = true;
						break;
					}
				}
			}
			else if (xt == 1) {
				for (int i = 0; i < 4; i++) {
					cX = fCoords[0][i];
					cY = fCoords[1][i];
					if (cX + 1 > 15) {
						hFlag = true;
						break;
					}
					else if (mField[cY][cX + 1] == 2) {
						hFlag = true;
						break;
					}
				}
			}

			//Code for setting a block
				if (vFlag) {
					for (int i = 0; i < 4; i++) {
						cX = fCoords[0][i];
						cY = fCoords[1][i];
						mField[cY][cX] = 2;
					}
					sFlag = true;
				}
				//Code for moving a block
				else {
					for (int i = 0; i < 4; i++) {
						cX = fCoords[0][i];
						cY = fCoords[1][i] + 1;
						mField[cY][cX] = 1;
					}
					y++;
				}
			

			if (hFlag == false && xt == 0) {
				x--;
			}
			else if (hFlag == false && xt == 1) {
				x++;
			}
			//Code for transforming the 2D Field vector to a 1D wchar_t array
			/*
			*	Equation for determining position:
			*
			*/
			//Find a row that contains a solid line
			int count = 0;
			bool isComp = false;
			int ind = 0;
			for (int i = 19; i > -1; i--) {
				count = 0;
				for (int j = 5; j < 15; j++) {
					if (mField[i][j] == 2) {
						count++;
						if (count > 9) {
							isComp = true;
						}
					}
				}
				if (isComp == true) {
					for (int j = i;j > 0; j--) {
						for (int k = 0; k < 20; k++) {
							//Set current row equal to previous row
							mField[j][k] = mField[j - 1][k];
						}
					}
					isComp = false;
					score += 100;
				}
				
			}
			
				
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					if (mField[i][j] == 2) {
						y_coord = fdX + i;
						x_coord = fdY + j;
						pos = y_coord * columns + x_coord - 1;
						screen[pos] = L'#';
					}
					else if (mField[i][j] == 1) {
						y_coord = fdX + i;
						x_coord = fdY + j;
						pos = y_coord * columns + x_coord - 1;
						screen[pos] = L'@';
					} 
				}
			}
			/*
			*	Scoring:
			*	Check from the bottom up for complete lines
			*	Store them in a 1D array with 20 indices
			*	Shift mField 2s
			*/
			//Finds a row that is complete
			
			
			
		/*
		*	Calcuations:
		*	Checks if coordinates have a valid spaces to move
		*/
			inc++;
			WriteConsoleOutputCharacter(hConsole, screen, rows * columns, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(100ms); // Delay a bit
		}
		//Full Reset
		y = 0;
		randNum[1] = rand() % 4;
		sFlag = false;
		vFlag = false;
		hFlag = false;
		
		
		if (lFlag == true) {
			break;
		}
		
	}
	for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
	//Your Score: 
	string endMsg = "Your Score: ";
	string sScore = to_string(score);
	for (int i = 0; i < endMsg.size(); i++) {
		tempChar = (wchar_t)endMsg[i];
		screen[i] = tempChar;
	}
	for (int i = 0; i < sScore.size(); i++) {
		tempChar = (wchar_t)sScore[i];
		screen[i + 80] = tempChar;
	}

	while (1) {
		WriteConsoleOutputCharacter(hConsole, screen, rows* columns, { 0,0 }, & dwBytesWritten);
	}
	
	//Code for Debugging
	
	
	/*for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			cout << mField[i][j] << " ";
		}
		cout << endl;
	}
	cout << vFlag << endl;
	cout << "Old Y: " << y << endl;
	cout << "New Y: " << yt << endl;
	cout << "fCoord: " << fCoords[1][0] << endl;*/

	return 0;
}