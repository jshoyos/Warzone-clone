
#include "Cards.h"
#include <iostream>
using namespace std;

// -----------------------------------------------------------------------------------------------------------------------------

// CARD.CPP

Card::Card() {}

Card::Card(cardType c) { this->type = c; }

Card::cardType Card::getCardType() { return this->type; }

Card::cardType Card::play() {
	int user_int;
	string user_string;
	Card::cardType card_type = this->type;

	if (card_type == Card::Bomb) {
		order_count++;   // static variable to keep track of order # (card.h)
		cout << "\n* You have selected the Bomb card. \n* Enter name of target territory: ";
		cin >> user_string;
		order_list.push_back("Order " + to_string(order_count) + ": Bomb " + user_string + "\n");
		cout << "* Bomb order added to your order_list. \n* Card will now return to the deck.\n";
		// return card to the Deck... 
	}

	else if (card_type == Card::Reinforcement) {
		order_count++;
		cout << "\n* You have selected the Reinforcement card. \n* This card gives you 5 reinforcement units.";
		order_list.push_back("Order " + to_string(order_count) + ": Reinforcement\n");
		cout << "\n* Reinforcement order added to your order_list. \n* Card will now return to the deck.\n";
		// return card to the Deck...
	}

	else if (card_type == Card::Blockade) {
		order_count++;
		cout << "\n* You have selected the Blockade card. \n* Enter name of target territory: ";
		cin >> user_string;
		order_list.push_back("Order " + to_string(order_count) + ": Blockade on: " + user_string + "\n");
		cout << "* Blockade order added to your order_list. \n* Card will now return to the deck.\n";
		// return card to the Deck...	
	}
	else if (card_type == Card::Airlift) {
		order_count++;
		cout << "\n* You have selected the Airlift card. \n* Enter the number of units to airlift: ";
		cin >> user_int;
		cout << "* Enter the name of the territory to airlift to: ";
		cin >> user_string;
		order_list.push_back("Order " + to_string(order_count) + ": Airlift " + to_string(user_int) + " units to: " + user_string + "\n");
		cout << "* Airlift order added to your order_list. \n* Card will now return to the deck.\n";
		// return card to the Deck...
	}
	else if (card_type == Card::Diplomacy) {
		order_count++;
		cout << "\n* You have selected the Diplomacy card. \n* Enter name of Player you wish to negotiate with: ";
		cin >> user_string;
		order_list.push_back("Order " + to_string(order_count) + ": Diplomacy with: " + user_string + "\n");
		cout << "* Diplomacy order added to your order_list. \n* Card will now return to the deck.\n";
		// return card to the Deck...
	}
	cout << "\n*** Updated list of orders: ***" << endl;
	for (int i = 0; i < order_list.size(); i++) {
		cout << order_list.at(i);
	}

	return card_type;

}

//void displayOrderList() {   ////////////////// testing
//	for (int i = 0; i < order_list.size(); i++) {
//		cout << order_list.at(i);
//	}
//	order_list.clear();
//}

// -----------------------------------------------------------------------------------------------------------------------------

// DECK.CPP

Deck::Deck() {}

Deck::Deck(int numCards) {

	while (numCards % 5 != 0 || numCards == 0) {
		if (numCards == 0) cout << "Try again with a multiple of 5 (but not 0): ";
		else cout << "Try again with a multiple of 5: ";
		cin >> numCards;
	}

	deck_size = numCards;
	numBomb = numReinforcement = numBlockade = numAirlift = numDiplomacy = numCards / 5;
	int max1, max2, max3, max4, max5; 	max1 = max2 = max3 = max4 = max5 = numCards / 5;
	int random;

	for (int i = 0; i < deck_size; i++) {  // shuffles the deck as it gets created
		random = rand() % 5;
		if (random == 0 && max1 > 0) {
			deck.push_back(Card(Card::Bomb));
			max1--;
		}
		else if (random == 1 && max2 > 0) {
			deck.push_back(Card(Card::Reinforcement));
			max2--;
		}
		else if (random == 2 && max3 > 0) {
			deck.push_back(Card(Card::Blockade));
			max3--;
		}
		else if (random == 3 && max4 > 0) {
			deck.push_back(Card(Card::Airlift));
			max4--;
		}
		else if (random == 4 && max5 > 0) {
			deck.push_back(Card(Card::Diplomacy));
			max5--;
		}
		else {
			i--;  // redo the iteration
		}
	}
	cout << "Great, the deck was created!" << endl;
}


Card Deck::draw() {
	if (!deck.empty()) {             // deck being a vector<Cards>
		int randomIndex = 0;
		randomIndex = rand() % this->getDeckSize();

		Card card_drawn = deck.at(randomIndex);     // pick a card at index: randomIndex, and assign it to: card_drawn
		deck.erase(deck.begin() + randomIndex);    // erase that card at index: randomIndex from the deck
		Card::cardType card_type = card_drawn.getCardType();  // get card_type

		if (card_type == Card::Bomb) numBomb--;                         // update info about the remaining cards in the deck
		else if (card_type == Card::Reinforcement) numReinforcement--;
		else if (card_type == Card::Blockade) numBlockade--;
		else if (card_type == Card::Airlift) numAirlift--;
		else if (card_type == Card::Diplomacy) numDiplomacy--;

		return card_drawn;
	}

	else cout << "The deck is empty\n";		// in case there was no more card to draw from the deck

	exit(EXIT_FAILURE);

}

void Deck::insertCard(Card c) {
	deck.push_back(c);
	Card::cardType card_type = c.getCardType();
	if (card_type == Card::Bomb) numBomb++;                         // update info about the remaining cards in the deck
	else if (card_type == Card::Reinforcement) numReinforcement++;
	else if (card_type == Card::Blockade) numBlockade++;
	else if (card_type == Card::Airlift) numAirlift++;
	else if (card_type == Card::Diplomacy) numDiplomacy++;


}

void Deck::deckStats() {


	cout << "\n*** Cards left in the deck: ***" << endl;
	cout << "# Bomb cards: " << numBomb << endl;
	cout << "# Reinforcement: " << numReinforcement << endl;
	cout << "# Blockade cards: " << numBlockade << endl;
	cout << "# Airlift cards: " << numAirlift << endl;
	cout << "# Diplomacy cards:" << numDiplomacy << endl;
}


int Deck::getDeckSize() {
	return deck.size();
}

void Deck::printDeck() {
	if (deck.empty())
		cout << "Deck is empty" << endl;

	else {
		for (int i = 0; i < deck.size(); i++) {
			Card::cardType t;
			t = deck.at(i).getCardType();
			string type;
			if (t == Card::Bomb) type = "Bomb";
			else if (t == Card::Reinforcement) type = "Reinforcement";
			else if (t == Card::Blockade) type = "Blockade";
			else if (t == Card::Airlift) type = "Airlift";
			else if (t == Card::Diplomacy) type = "Diplomacy";
			cout << "Deck[" << i << "] : " << type << endl;
		}
	}
}

// -----------------------------------------------------------------------------------------------------------------------------

// HAND.CPP


Hand::Hand() {
	maxCards = 0;
	numCards = 0;
}

Hand::Hand(int max) {
	maxCards = max;
	numCards = 0;
}

void Hand::insertCard(Card c) {      // whatever card is passed (ie: card_drawn from the Deck) is added to the Hand. 
	handOfCards.push_back(c);		 //add new card to the hand
	numCards++;
}

void Hand::showHand() {
	cout << "\n*** Current Hand: ***" << endl;
	for (int i = 0; i < numCards; i++) {

		if (!handOfCards.empty() && i < handOfCards.size()) {

			Card::cardType t;
			t = handOfCards.at(i).getCardType();
			string type;

			if (t == Card::Bomb) type = "Bomb";
			else if (t == Card::Reinforcement) type = "Reinforcement";
			else if (t == Card::Blockade) type = "Blockade";
			else if (t == Card::Airlift) type = "Airlift";
			else if (t == Card::Diplomacy) type = "Diplomacy";

			cout << "Card Slot " << i << ": " << type << endl;
		}
	}
	cout << "# of free slots left: " << (this->maxCards - this->numCards) << endl;
}


int Hand::getHandSize() {
	return handOfCards.size();
}

int Hand::getMaxCards() {
	return maxCards;
}
