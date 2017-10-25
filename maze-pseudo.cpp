//------------------------------------------------------------------------
// Pseudo-code for the maze solver problem. You have permission to use any
// of the code below, or to totally ignore it. -sb
//------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include "conio.h"
#include <unistd.h>

using namespace std;

//Initialize functions
void loadMatrix(char masterMatrix[10][10]);
void getStart(int& startRow, int& startCol);
bool canEscape(int row, int col, char masterMatrix[10][10]);

//Declaring Global Variables
const char visited = '@';
const char path = '+';
string fileName;

void loadMatrix(char masterMatrix[10][10]){
	cout << "Please enter the name of maze file=> " << endl;
	cin >> fileName;
	ifstream file(fileName);
	if (!file){
	cout << "Could not Open File" << endl;
	return;
	}
	system("clear");
	int x, y;
	for (int x = 0; x < 10; x++){
			for (int y = 0; y < 10; y++){
				file >> masterMatrix[x][y];
			}
	}
}

void getStart(int& startRow, int& startCol){
	cout << "Please Enter Starting Row=> " << endl;
	cin >> startRow;
	cout << "Please Enter Starting Column=> " << endl;
	cin >> startCol;
}

bool canEscape(int row, int col, char masterMatrix[10][10]){
	if (row < 0 || row > 9 || col < 0 || col > 9){
		return false;
	}
	if (masterMatrix[row][col] == '#'){
		cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::RED) << "#\n";
		return false;
	}
//	else if (masterMatrix[row][col] == path){
//		cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::RED) << "x\n";
//		return false;
//	}
	else if (masterMatrix[row][col] == visited){
		return false;
	}
	else if (masterMatrix[row][col] == 'E'){
		cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::GREEN) << "x\n";
		return true;
	}
	else{
		cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::BLUE) << "x\n";
		masterMatrix[row][col] = visited;
		sleep(1);
		if (canEscape(row, col + 1, masterMatrix)){
			cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::GREEN) << "x\n";
			return true;
		}
		if (canEscape(row + 1, col, masterMatrix)){
			cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::GREEN) << "x\n";
			return true;
		}
		if (canEscape(row, col - 1, masterMatrix)){
			cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::GREEN) << "x\n";
			return true;
		}
		if (canEscape(row - 1, col, masterMatrix)){
			cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::GREEN) << "x\n";
			return true;
		}
	//	masterMatrix[row][col] = path;
	//	cout << conio::gotoRowCol(row + 2, col + 1) << conio::fgColor(conio::RED) << "x";
		return false;

	}
}

int main(){
     int startRow, startCol;

     char masterMatrix[10][10];
     char matrix[10][10];
     
	 // Call a function that prompts for the file name (e.g., "maze1.txt"),
     // reads the file and loads the maze characters into masterMatrix.
     loadMatrix(masterMatrix);
	 
	 //Draws maze
	 cout << "0123456789" << endl;
     for (int x = 0; x < 10; x++){
			for (int y = 0; y < 10; y++){
				cout << masterMatrix[x][y];
				matrix[x][y]=masterMatrix[x][y];
			}
			cout << x;
			cout << endl;
	 }
	// Call a function that prompts user for the starting row and column.
     // Reading the row and column from cin also causes a "priming read"
     // so that we can use "cin" as a boolean test for input data happiness. :-)
     getStart(startRow, startCol);

     // While the input stream is happy because the last read worked, keep looping.
	 while(cin){
		if( canEscape(startRow, startCol, masterMatrix) ) {
	    	cout << conio::gotoRowCol(30,1) <<conio::fgColor(conio::RESET) << "Path Found" << endl;
			sleep(2);
			system("clear");	
		}
		else {
	    	cout << conio::gotoRowCol(30,1) <<conio::fgColor(conio::RESET) <<"No Path Found" << endl;
			sleep(2);
			system("clear");
		}

		 for (int x = 0; x < 10; x++){
			for (int y = 0; y < 10; y++){
				masterMatrix[x][y]=matrix[x][y];
			}
		}
		//Reprint Maze
		cout << "0123456789" << endl;
     		for (int x = 0; x < 10; x++){
				for (int y = 0; y < 10; y++){
					cout << masterMatrix[x][y];
					matrix[x][y]=masterMatrix[x][y];
				}	
			cout << x;
			cout << endl;
	 		}
		//Re ask for start
		getStart(startRow, startCol);

     }
	 return 0;
}
