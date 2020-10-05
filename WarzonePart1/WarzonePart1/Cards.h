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

using namespace std;

struct Card {

	enum cardType {
		Bomb, Reinforcement, Blockade, Airlift, Diplomacy
	};
	cardType type;

	Card();
	Card(cardType);
	cardType getCardType();
	cardType play();
	void displayOrderList();

};

static int order_count;              // for play() method (order simulation)
static vector<string> order_list;    // for play() method (order simulation)

// -----------------------------------------------------------------------------------------------------------------------------

struct Deck {

	vector<Card> deck;
	int deck_size;
	int numBomb;
	int numReinforcement;
	int numBlockade;
	int numAirlift;
	int numDiplomacy;

	Deck();
	Deck(int numCards);
	Card draw();
	void deckStats();
	int getDeckSize();
	void printDeck();
	void insertCard(Card c);

};

// -----------------------------------------------------------------------------------------------------------------------------

struct Hand {

	vector<Card> handOfCards;
	int numCards;

	Hand();
	Hand(int);
	void showHand();
	void insertCard(Card);
	int getHandSize();
	int getMaxCards();
	int maxCards;

};

// -----------------------------------------------------------------------------------------------------------------------------

