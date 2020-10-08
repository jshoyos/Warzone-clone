/* Driver creates a deck of Warzone cards (of all 5 types)
		& creates one hand object that gets filled by drawing cards from deck
		and then calls play() on all the cards in the hand object.
*/

#include "Cards.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


int main(int argc, char* argv[]) {

	Deck myDeck;
	Card card_drawn;
	Hand myHand;
	string user_string;
	int user_int;

	srand((int)time(0));

	cout << "Let's create a deck. \nEnter a finite # of cards for the deck: ";
	cin >> user_int;
	myDeck = Deck(user_int);

	cout << "Enter a maximum # of cards per hand: ";
	cin >> user_int;
	while (user_int < 1 || user_int > myDeck.getDeckSize()) {
		cout << "Try again with a number from 1 to " << myDeck.getDeckSize() << ": ";
		cin >> user_int;
	}
	myHand = Hand(user_int);

	cout << "We have shuffled the deck for you. \nWould you like to see its content? Enter yes/no: ";
	cin >> user_string;


	if (user_string == "yes") {
		cout << endl;
		myDeck.printDeck();
		cout << endl;
	}

	cout << "We have created a hand. \nThe hand can hold at most: " << myHand.getMaxCards() << " cards" << endl;
	cout << "How many cards do you want to draw (at random) ? ";
	cin >> user_int;

	while (user_int < 1 || user_int > myHand.getMaxCards()) {
		if (user_int < 1) {
			cout << "Try again with a number greater or equal to 1: ";
			cin >> user_int;
		}
		else {
			cout << "A hand can hold at most " << myHand.getMaxCards() << " cards. You currently hold: " << myHand.getHandSize() << " cards. Try again: ";
			cin >> user_int;
		}
	}
	for (int i = 0; i < user_int; i++) {
		card_drawn = myDeck.draw();
		myHand.insertCard(card_drawn);
	}
	while (myHand.getHandSize() < myHand.getMaxCards()) {
		cout << "Draw more cards? How many: ";
		cin >> user_int;
		if (user_int == 0)
			break;
		else {
			while ((user_int + myHand.getHandSize()) > myHand.getMaxCards()) {
				cout << "A hand can hold at most " << myHand.getMaxCards() << " cards. You currently hold: " << myHand.getHandSize() << " cards. Try again: ";
				cin >> user_int;
			}
			for (int i = 0; i < user_int; i++) {
				card_drawn = myDeck.draw();
				myHand.insertCard(card_drawn);
			}
		}
		if (user_string == "0")
			break;
	}

	cout << "Perfect. Your hand now has " << myHand.getHandSize() << " cards. Here it is: " << endl;
	myHand.showHand();

	cout << "\nCheck the deck? (Enter yes/no): ";
	cin >> user_string;
	if (user_string == "yes") myDeck.deckStats();

	cout << "\nLet's play() the cards. You now have " << myHand.getHandSize() << " cards." << endl;
	cout << "Which card would you like to play() first? Enter slot # (0-" << myHand.getHandSize() - 1 << "): ";
	cin >> user_int;


	while (user_int<0 || user_int>(myHand.getHandSize() - 1)) {
		cout << "Try again. Enter slot # between 0 and " << myHand.getHandSize() - 1 << ": ";
		cin >> user_int;
	};

	Card c;
	c = myHand.handOfCards.at(user_int).play();
	myDeck.insertCard(c);
	myHand.handOfCards.erase(myHand.handOfCards.begin() + user_int);

	if (myHand.getHandSize() > 0) {
		cout << "\nLet's play() all (" << myHand.getHandSize() << ") remaining cards one by one: \n";
		while (myHand.getHandSize() > 0) {
			c = myHand.handOfCards.at(0).play();
			myDeck.insertCard(c);
			myHand.handOfCards.erase(myHand.handOfCards.begin());
		}
	}

	//cout << "\nOK. Let's now display the order_list... \n";
	//cout << order_list.size() << endl;
	//for (int i = 0; i < order_list.size(); i++) {
	//
	//	cout << order_list.at(i); 
	//}
	//order_list.clear(); 

	cout << "\nAnd let's check the deck again.\n";
	cout << "Deck is of size: " << myDeck.getDeckSize() << endl;
	myDeck.deckStats();



}