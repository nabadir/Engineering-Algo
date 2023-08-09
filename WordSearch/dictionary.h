#pragma once
#include <iostream>
#include <strstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "heap.h"

class dictionary
{
public:
	std::vector<std::string> list;
	int wordcount = 0;
	int top;
	int bottom = 0;

	dictionary(int i) {

	}

	void readFile(int& top) {
		std::ifstream fin;
		std::string fileName = "Dictionary.txt";
		fin.open(fileName.c_str());

		while (!fin.eof()) {
			list.resize(wordcount + 1);
			fin >> list[wordcount];
			//cout << list[wordcount] << endl;;
			wordcount++;
		}

		std::cout << list.size() << std::endl;
		top = list.size() - 1;
	}




	//Sorts dictionary in alphabetical order
	void selectionSort(std::vector<std::string>& arr) {
		int size = arr.size();
		for (int i = 0; i < size; i++) {
			//Set new minimum value if current value is less than current minimum
			int min{ i };
			for (int x = i; x < size; x++) {
				if (arr[x] < arr[min]) {
					min = x;
				}
			}
			//Swap first ith value with minimum value
			std::string temp{ arr[i] };
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}

	void quickSort(std::vector<std::string>& arr, int low, int high)
	{
		int i = low, j = high;
		std::string mid = arr[(high + low) / 2];
		while (i <= j)
		{
			while (arr[i] < mid)
				i++;
			while (arr[j] > mid)
				j--;
			if (i <= j)
			{
				swap(arr[i], arr[j]);
				i++; j--;
			}
		};


		if (low < j)
			quickSort(arr, low, j);
		if (i < high)
			quickSort(arr, i, high);
	}

	void heapSort(std::vector<std::string>& arr)
	{
		heap<std::string> d;
		int heapsize = arr.size();
		d.heapSort(arr,heapsize);

	}
	void printVector(std::vector<std::string>& arr) {
		for (int i = 0; i < arr.size(); i++)
		{
			std::cout << arr[i] << std::endl;

		}
	}

	//Overloaded operator declaration
	friend std::ostream& operator << (std::ostream& os, const dictionary& dt);

};