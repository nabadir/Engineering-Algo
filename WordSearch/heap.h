#pragma once
#include <iostream>
#include <strstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>


template<typename T>
class heap
{

public:
	//Return parent of heap
	int parent(int i)
	{
		return (i / 2);
	}
	//Return left side of heap
	int LEFT(int i)
	{
		return (2 * i + 1);
	}
	//Return right side of heap
	int RIGHT(int i)
	{
		return (2 * i + 2);
	}
	//Return value of heap at a certain point in the vector
	std::string getItem(int n, std::vector<T> input)
	{
		return input[n];
	}
	//Initializes the heap by copying the dictionary vector to a new vector<T> heapVec
	std::vector<T> initializeMaxHeap(std::vector<std::string>& input)
	{
		std::vector<T> heapVec = input;
		return heapVec;
	}
	void maxHeapify(std::vector<T>& input,int size, int i)
	{
		int largest = i;
		int l = LEFT(i);
		int r = RIGHT(i);
		int heapsize = size;
		//Sets largest to l if conditions are met
		if (l <= heapsize && input[l] > input[i])
		{
			largest = l;
		}
		//Sets largest to r if conditions are met
		if (r <= heapsize && input[r] > input[largest])
		{
			largest = r;
		}
		//recursive so as to heapify the entire vector
		if (largest != i)
		{
			swap(input[i], input[largest]);
			maxHeapify(input, heapsize, largest);
		}

	}
	void buildMaxHeap(std::vector<std::string>& input)
	{
		std::vector<T> heapVec = initializeMaxHeap(input);
		int hsize = heapVec.size();
		int heapIDX = (hsize / 2) - 1;
		//Creates a max heap through recursion
		for (int i = heapIDX; i >= 0; i--)
		{
			maxHeapify(input,hsize,i);
		}
	}
	void heapSort(std::vector<T>& input, int size)
	{
		int heapsize = size;
		buildMaxHeap(input);
		// One by one extract an element from heap
		for (int i = heapsize - 1; i > 0; i--) {
			// Move current root to end
			swap(input[0], input[i]);

			// call max heapify on the reduced heap
			maxHeapify(input, i, 0);
		}
	}
};