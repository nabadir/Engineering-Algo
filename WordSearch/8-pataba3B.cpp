// wordsearchB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Nicholas Abadir and Parth Patel

#include <iostream>
#include <strstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "dictionary.h"
#include "heap.h"
#include "d_except.h"
#include "matrix.h"

using namespace std;

//Overloaded operator for dictionary class

ostream& operator << (ostream& os, const dictionary& dt) {
	int limit = dt.wordcount;
	for (int i = 0; i < limit; i++) {
		os << dt.list[i] << endl;
	}
	return os;
}

class grid
{
public:
	int length;
	int width;


	//Constructor
	grid(int len, int wid) {
		length = len;
		width = wid;
	}

	//Reads file to create grad matrix
	void readGrid(matrix<string>& st) {
		ifstream fin;
		string fileName;
		//Prompt user to enter name of file
		cout << "Enter name of file: " << endl;
		cin >> fileName;
		//Open file to read contents
		fin.open(fileName);
		string templen;
		string tempwid;

		while (!fin.eof()) {
			//Length and width are set based on values provided by file
			fin >> templen;
			stringstream templength(templen);
			templength >> length;
			fin >> tempwid;
			stringstream tempwidth(tempwid);
			tempwidth >> width;
			//Resize matrix based on previously set values
			st.resize(length, width);
			cout << "here" << endl;
			//Matrix values are set based on read file
			for (int i = 0; i < length; i++) {
				for (int j = 0; j < width; j++) {
					fin >> st[i][j];
				}
			}
		}
	}

};

void Search(grid g, matrix<string> mx, vector<string>& candidate, int n, dictionary &dict) {
	
	dict.readFile(dict.top);
	
	
	
	//dict.printVector(dict.list);

	int counter = 0;
	if (n == 1)
	{
		cout << "you have selected selection sort" << endl;
		dict.selectionSort(dict.list);
	}
	if (n == 2)
	{
		cout << "you have selected quick sort" << endl;
		dict.quickSort(dict.list, dict.bottom, dict.top);
	}
	if (n == 3)
	{
		cout << "you have selected heap sort" << endl;
		dict.heapSort(dict.list);

	}

	ifstream fin;
	string fileName;
	//Prompts user to enter name of grid file
	cout << "Enter name of file: " << endl;
	cin >> fileName;

	fin.open(fileName);
	string templen;
	string tempwid;

	while (!fin.eof()) {
		//Length and width of grid are set based on values provided by file
		fin >> templen;
		stringstream templength(templen);
		templength >> g.length;
		fin >> tempwid;
		stringstream tempwidth(tempwid);
		tempwidth >> g.width;

		mx.resize(g.length, g.width);
		//Matrix values are set based on read file
		for (int i = 0; i < g.length; i++) {
			for (int j = 0; j < g.width; j++) {
				fin >> mx[i][j];
				cout << mx[i][j] << " ";
			}
			cout << endl;
		}
	}


	//Stores all combinations for moving right in matrix
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[i][(j + 1) % g.width] + mx[i][(j + 2) % g.width] + mx[i][(j + 3) % g.width] + mx[i][(j + 4) % g.width];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[i][(j + x) % g.width];
				counter++;
			}
		}
	}
	//Stores all combinations for moving downwards 
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[(i + 1) % g.width][j] + mx[(i + 2) % g.width][j] + mx[(i + 3) % g.width][j] + mx[(i + 4) % g.width][j];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[(i + x) % g.width][j];
				counter++;
			}
		}
	}
	//Stores all combinations moving left
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[i][abs((j - 1)) % g.width] + mx[i][abs((j - 2)) % g.width] + mx[i][abs((j - 3)) % g.width] + mx[i][abs((j - 4)) % g.width];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[i][abs((j - x)) % g.width];
				counter++;
			}
		}
	}
	//Stores all combinations moving upwards
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[abs((i - 1)) % g.width][j] + mx[abs((i - 2)) % g.width][j] + mx[abs((i - 3)) % g.width][j] + mx[abs((i - 4)) % g.width][j];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[abs((i - x)) % g.width][j];
				counter++;
			}
		}
	}
	//Stores all combinations moving diagonal (down+right)
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[(i + 1) % g.width][(j + 1) % g.width] + mx[(i + 2) % g.width][(j + 2) % g.width] + mx[(i + 3) % g.width][(j + 3) % g.width] + mx[(i + 4) % g.width][(j + 4) % g.width];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[i][(j + x) % g.width];
				counter++;
			}
		}
	}
	//Stores all combinations moving diagonal (up+right)
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[abs((i - 1)) % g.width][(j + 1) % g.width] + mx[abs((i - 2)) % g.width][(j + 2) % g.width] + mx[abs((i - 3)) % g.width][(j + 3) % g.width] + mx[abs((i - 4)) % g.width][(j + 4) % g.width];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[i][abs((j - x)) % g.width];
				counter++;
			}
		}
	}
	//Stores all combinations moving diagonal (down+left)
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[(i + 1) % g.width][abs((j - 1)) % g.width] + mx[(i + 2) % g.width][abs((j - 2)) % g.width] + mx[(i + 3) % g.width][abs((j - 3)) % g.width] + mx[(i + 4) % g.width][abs((j - 4)) % g.width];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[abs((i - x)) % g.width][j];
				counter++;
			}
		}
	}
	//Stores all combinations moving diagonal (up+left)
	for (int i = 0; i < g.length; i++) {
		for (int j = 0; j < g.length; j++) {
			candidate.resize(counter + 1);
			candidate[counter] = mx[i][j] + mx[abs((i - 1)) % g.width][abs((j - 1)) % g.width] + mx[abs((i - 2)) % g.width][abs((j - 2)) % g.width] + mx[abs((i - 3)) % g.width][abs((j - 3)) % g.width] + mx[abs((i - 4)) % g.width][abs((j - 4)) % g.width];
			counter++;
			for (int x = 5; x < g.width; x++) {
				candidate.resize(counter + 1);
				candidate[counter] = candidate[counter - 1] + mx[abs((i - x)) % g.width][abs((j - x)) % g.width];
				counter++;
			}
		}
	}
}


//Implement binary search to find candidate words in dictionary
string findMatches(vector<string> arr, int l, int r, string x)
{

	string str;
	
	if (r >= l) {

		int mid = l + (r - l) / 2;
		
		//If the middle value is a match, return value
		if (arr[mid] == x) 
			return arr[mid] + " ";
		
		//If the value is towards the right side, use recursion with mid - 1
		if (arr[mid] > x)
			return findMatches(arr, l, mid - 1, x);

		//If the value is towards the left side, use recursion with mid + 1
		if (arr[mid] < x)
		return findMatches(arr, mid + 1, r, x);
	}
	//When value is not present in dictionary, return empty string
	return str;
}



int main()
{
	//Initialize empty matrix and candidate word list
	matrix<string> mac(1, 1, "0");
	vector<string> candidate;
	
	//Initialiize and sort dictionary
	dictionary dict(0);
	//dict.readFile(dict.top);
	//dict.selectionSort(dict.list);
	//dict.quickSort(dict.list, dict.bottom, dict.top);
	//dict.heapSort(dict.list);
	//dict.printVector(dict.list);
	//Initialize gridand search for list of candidate words
	grid grd(0, 0);
	cout << " Please select a sorting method :" << endl;
	cout << " 1. Selection Sort " << " 2. Quick Sort " << " 3. Heap Sort" << endl;
	int selection = 0;
	while (selection == 0) {
		cin >> selection;
		if (selection >= 4 || selection == 0)
		{
			cout << "please choose between options 1 and 3" << endl;
			selection = 0;
		}
	}
	Search(grd, mac, candidate, selection, dict);

	//Print all matches
	cout << dict.list.size() << endl;

	for (int n = 0; n < candidate.size() - 1; n++) {
		//cout << candidate[n] << endl;
		cout << findMatches(dict.list, 0, dict.list.size() - 1, candidate[n]);
		
	}

}

