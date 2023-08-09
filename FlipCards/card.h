#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "Node.h"


class card {

public:

	int cardvalue;
	int cardsuit;

	card(); //defulat constructor

	card(int suit, int value);//Constructor with values

	//Sets suit value
	void setSuit(int suit);

	//Returns suit value
	int getSuit();

	//Sets card value
	void  setValue(int value);

	//Returns card value
	int getValue();

	//Overloaded operator for << to return card value and card suit
	//friend ostream& operator << (ostream& os, const card& dt);

private:

};

#endif