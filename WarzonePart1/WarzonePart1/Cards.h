/*  implement a deck and a hand
	each card has a type (bomb, reinforcement, blockade, airlift, diplomacy)
	deck: draw() - to draw a card from the deck at random & place it in the player's hand
		  play() - to play a card from the hand - which: creates an order, adds the order to the player's list of orders,
														 and returns the card to the deck
*/

#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Player.h"

using namespace std;
class Player;
class Territory;


struct Card {							// No attributes are of a user-defined type -> no need for pointers here

	enum cardType {						// 5 types of cards in a deck
		Bomb, Reinforcement, Blockade, Airlift, Diplomacy
	};
	cardType type{};

	Card();								// Default constructor
	~Card();							// Deck has no pointer attribute 
	Card(cardType);						// Param'd constructor
	Card(const Card& c);                // Copy-constructor: Making the param a const to make sure	 
										//					 we dont inadvertedly change the passed reference
	Card& operator =(const Card& c);				  // Overloaded assignment operator

	cardType getCardType();
	cardType play();
	cardType play2(Player*,Player*, Territory*, Territory*, int);


};

static int order_count{};              // for play() method (order simulation)
static vector<string> order_list{};    // for play() method (order simulation)

// -----------------------------------------------------------------------------------------------------------------------------

struct Deck {                       // No attributes are of a user-defined type -> no need for pointers here

	vector<Card*> deck;				// Decl is a vector of Card objects
	int deck_size = 0;
	int numBomb{};					// # of cards of Type Bomb in the deck
	int numReinforcement{};			//			  of Type Reinforcement
	int numBlockade{};				//			  of Type Blockade
	int numAirlift{};				//			  of Type Airlift
	int numDiplomacy{};				//			  of Type Diplomacy

	Deck();							// Default constructor
	~Deck();						// However Deck has no pointer attribute 
	Deck(const Deck& d);            // Copy-constructor: Making the param a const to make sure
									//					 we dont inadvertedly change the passed reference 

	Deck(int numCards);				  // Param'd constructor
	Deck& operator =(const Deck& c);  // Overloaded assignment operator

	Card* draw();					// draw() method, draws a card at random
	void deckStats();				// Details about the # of each 5 types of cards
	int getDeckSize();
	void printDeck();				// Prints out all the cards in the deck 
	void insertCard(Card* c);		// Takes a card and inserts it last in the deck

};

// -----------------------------------------------------------------------------------------------------------------------------

struct Hand {						// No attributes are of a user-defined type -> no need for pointers here

	vector<Card*> handOfCards{};		// A hand is a vector of Cards
	int numCards{};					// Current # of cards in the hand
	int maxCards;					// Maximum # of cards that a hand can hold 

	Hand();
	~Hand();
	Hand(const Hand& h);			  // Copy-constructor: Making the param a const to make sure
									  //				   we dont inadvertedly change the passed reference
	Hand(int);						  // Param'd constructor
	Hand& operator =(const Hand& c);  // Overloaded assignment operator

	void showHand();					// Prints out the cards in the hand, w corresponding slot #
	void insertCard(Card*);				// Takes a card, and insert it last in the hand
	int getHandSize();
	int getMaxCards();					// return the maximum number of cards a hand can hold
	


};

// -----------------------------------------------------------------------------------------------------------------------------
