#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "Node.h"
#include "Card.h"

class deck {

public:
	node<card>* temp = nullptr;
	node<card>* result;
	node<card>* top = nullptr;

	std::vector<card> cardlist;


	deck(int i);

	void shuffle();
	void deal();
	void replace(card& val);
	card flip(card& val);
	



};
#endif