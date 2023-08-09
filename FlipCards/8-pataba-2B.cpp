#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "node.h"
#include "card.h"
#include "deck.h"

using namespace std;



	int cardvalue;
	int cardsuit;

	card::card() { //Default constructor

	}

	card::card(int suit, int value) { //Constructor with values
		setSuit(suit);
		setValue(value);
	}

	//Sets suit value
	void card::setSuit(int suit) {
		cardsuit = suit;
	}

	//Returns suit value
	int card::getSuit() {
		return cardsuit;
	}

	//Sets card value
	void  card::setValue(int value) {
		cardvalue = value;
	}

	//Returns card value
	int card::getValue() {
		return cardvalue;
	}



//Overloaded operator definition for << to return card value and card suit
ostream& operator<<(ostream& os, card& cd)
{

	os << "(" << cd.cardvalue << ", " << cd.cardsuit << ")" << endl;
	return os;
}





	deck::deck(int i) {


		int count = 0;

		//Nested for loop initializes linked list of
		//cards of all values in a deck in order
		for (int j = 1; j < 5; j++) {
			for (int i = 1; i < 14; ++i)
			{
				//New card is initilized and stored and linked list and vector
				result = new node<card>(card(j, i), temp);
				cardlist.resize(count + 1);
				cardlist[count] = result->nodeValue;
				count++;
				//Next value is set
				temp = result;
			}
		}
		//Most recently initialized card is set to top
		top = result;
		temp = nullptr;
	}

	void deck::shuffle() {

		//Temp is reset
		temp = nullptr;

		//Generate seed for random function
		srand(time(NULL));

		//Shuffle algorithm to put vector in random order
		random_shuffle(cardlist.begin(), cardlist.end());

		//Copy vector to linked list
		for (int x = 0; x < 52; x++) {
			result = new node<card>(cardlist[x], temp);
			result->next = temp;
			temp = result;

		}
		//Set top to most recent card
		top = result;
	}

	void deck::deal() {

		result = top;
		//Remove chosen card from deck and set new card to top
		if (result->next != NULL) {
			top = result->next;
			delete result;
			result = top;
		}

	}

	void deck::replace(card& val) {
		//Result is set to top and printed
		result = top;
		cout << "Your card is: " << result->nodeValue;
		val.cardvalue = top->nodeValue.cardvalue;
		val.cardsuit = top->nodeValue.cardsuit;

		//Top is set to next value and previous top is placed at bottom of deck
		top = result->next;
		temp = result;
		while (result->next != NULL) {
			result = result->next;
		}
		result->next = temp;
		temp->next = nullptr;

	}

	card deck::flip(card& val) {
		result = top;
		int cardIndex;
		int check = 0;

		//Prompt user to input value within range
		while (check == 0) {
			cout << "Enter a card to pick up (1-24): " << endl;
			cin >> cardIndex;
			if (cardIndex >= 1 && cardIndex <= 24) {

				check++;
			}
			else {
				cout << "Value not in range." << endl;
			}
		}
		//Result points to selected card
		for (int i = 0; i < cardIndex - 1; i++) {
			result = result->next;
		}
		//Card is printed
		cout << result->nodeValue;

		//Card is set to selected value
		val.cardvalue = result->nodeValue.cardvalue;
		val.cardsuit = result->nodeValue.cardsuit;
		return val;
	}



//Overloaded operator to print deck
ostream& operator << (ostream& os, const deck& dt) {
	node<card>* front = dt.top;
	while (front->next != NULL) {
		os << front->nodeValue << endl;
		front = front->next;
	}
	os << front->nodeValue << endl;
	return os;
}



void playFlip() {
	//Sets point value to 0
	int points = 0;
	int control = 0;
	card tempcard;

	//Print all rules for user to read
	cout << "Welcome to the card game flip!" << endl << "The rules are below:" << endl;
	cout << "The deck of cards is shuffled three times." << endl;
	cout << "24 cards are then drawn from the deck." << endl;
	cout << "The player can elect to draw a card or end the game for each round." << endl;
	cout << "If a card is turned over, the player:" << endl;
	cout << "(a) Receives 10 points for an ace" << endl;
	cout << "(b) Receives 5 points for a king, queen or jack" << endl;
	cout << "(c) Receives 0 points for an 8, 9 or 10" << endl;
	cout << "(d) Loses half their points for a 7" << endl;
	cout << "(e) Loses all their points for a 2, 3, 4, 5 or 6" << endl;
	cout << "(f) Receives 1 point extra, in addition to the above, for a heart" << endl;

	//Full, sorted deck is initialized and printed
	deck cardDeck(0);
	cout << cardDeck;
	cout << "Shuffled deck:" << endl;
	//Deck is shuffled three times and reprinted
	cardDeck.shuffle();
	cardDeck.shuffle();
	cardDeck.shuffle();
	cout << cardDeck;

	//Take top 24 cards and place into hand
	deck cardHand = cardDeck;
	for (int i = 0; i < 28; i++) {
		cardHand.deal();
	}

	cout << "Card hand: " << cardHand;

	while (control == 0) {
		//Initialize card variable to determine point value
		card val;


		//Prompt user to 
		cout << "Press 0 to draw a card or press 1 to end the game" << endl;
		cin >> control;

		if (control == 0) {
			cardHand.flip(val);




			//Add/subtract points based on card suit and value as stated by rules
			if (val.cardvalue == 1) {
				points = points + 10;
			}
			else if (val.cardvalue == 11 || val.cardvalue == 12 || val.cardvalue == 13) {
				points = points + 5;
			}
			else if (val.cardvalue == 7) {
				points = points / 2;
			}
			else if (val.cardvalue == 2 || val.cardvalue == 3 || val.cardvalue == 4 || val.cardvalue == 5 || val.cardvalue == 6) {
				points = 0;
			}
			else {
				points = points;
			}
			if (val.cardsuit == 3) {
				points++;
			}

			//Print point value
			cout << "Points: " << points << endl;

		}
	}

}

int main()
{
	//Call function to start game
	playFlip();
}