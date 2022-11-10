#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>

int nScreenWidth = 80;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)
int nFieldWidth = 12;
int nFieldHeight = 18;
int counter = 0;
int pos = 0;
int main()
{
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
	pos = columns / 2;
	//Block is a 4x4 vector of integers
	vector <vector<int>> block(20);
	vector <vector<int>> tempBlock(20);
	for (int i = 0; i < 20; i++) {
		block[i] = vector<int>(20);
		tempBlock[i] = vector<int>(20);
		for (int j = 0; j < 20; j++) {
			block[i][j] = 0;
			tempBlock[i][j] = 0;
		}
	}
	vector <vector<int>> movingBlock{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	};
	
	int tempPos;
	int inc = 0;
	int x = 14;
	int y = 0;
	int xt = x;
	int yt = y;
	wchar_t tempChar = L'0';
	while (1) {
		for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
		//screen[pos] = L'#';
		inc = 0;
		/*if (GetAsyncKeyState(0x41)) {
			//screen[pos] = L' ';
			if(pos > 2){
				pos--;
			}
			//screen[pos] = L'#';
			//screen[0] = L'A';
		}*/
		/*if (GetAsyncKeyState(0x44)) {
			//screen[pos] = L' ';
			if (pos < rows*columns-82) {
				pos++;
			}
			//screen[pos] = L'#';
			//screen[0] = L'D';
		}*/
		//Print block to the screen
		tempPos = pos;
		/*for (int i = 0; i < 2; i++) {
			tempPos += i;
			for (int j = 0; j < 2; j++) {
				if (block[i][j] == 1 && inc > 0) {
					screen[tempPos + j] = L'#';
				}
			}
		}*/
		//screen[pos] = L'#';
		//screen[pos+1] = L'#';
		//screen[pos+80] = L'#';
		//screen[pos+81] = L'#';
		/*for (int i = 1; i < 20; i++) {
			for (int j = 1; j < 20; j++) {
				pos = i * 80 + j;
				if (pos > rows * columns) {
					pos = rows * columns - 1;
				}
				if (movingBlock[i][j] == 1) {

					tempChar = L'#';
				}
				else {
					tempChar = L' ';
				}
				screen[pos] = tempChar;
			}
			inc++;
			cout << endl;
		}*/
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (movingBlock[i][j] == 1) {
					tempBlock[y][x] = 1;
					x++;
				}
				
				if (x == 3) {
					x = 0;
				}
			}
			y++;
			
			if (y == 3) {
				y = 0;
			}
		}
		x = 14;
		y = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (tempBlock[i][j] == 1) {
					block[i][j] = 1;
				}
			}
		}
		block = tempBlock;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				pos = i*78 + j;
				if (block[i][j] == 1) {
					tempChar = L'#';
					screen[pos] = tempChar;
				}
			}
		}
		WriteConsoleOutputCharacter(hConsole, screen, rows * columns, {0,0}, &dwBytesWritten);
		this_thread::sleep_for(100ms); // Delay a bit
		//counter++;
		/*if (counter == 5) {
			counter = 0;
			pos += columns;
			screen[pos - columns] = L' ';
			if (pos > rows * columns - 10) {
				pos = columns/2;
			}
		}*/
		//this_thread::sleep_for(400ms);
		
	}
	return 0;
}