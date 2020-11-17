#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include "TextTable.h"

using namespace std;

bool Publisher::isSubscribed(IObservable *observer) const
{
	for (IObservable *obs : observers) {
		if (obs == observer ){
			return true;
		}
	}
	return false;
}

void IObservable::clearScreen()
{
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif
}

void Publisher::subscribe(IObservable *observer)
{
	if (!isSubscribed(observer)) {
		observers.push_back(observer);
	}
}

void Publisher::notifyAll(string data)
{
	for (IObservable *observer : observers) {
		observer->update(data);
	}
}

void Publisher::unsubscribe(IObservable* observer)
{
	if (isSubscribed(observer)) {
		auto it = find(observers.begin(), observers.end(), observer);
		observers.erase(it);
	}
}

void PhaseObserver::update(string data)
{
	//IObservable::clearScreen();
	cout << data << endl;
}

void GameStatisticsObserver::update(string data)
{
	int mapSize = GameStart::map->getMapSizeTerritory();
	Player* winner = nullptr;
	bool GameOver = false;
	TextTable t('-', '|', '+');
	
	t.add("Player Name");
	t.add("Countries Owned");
	t.add("Percentage Conquered");
	t.endOfRow();

	for (Player* player : GameStart::players) {
		int countries = player->getTerritoryList()->size();
		auto str = to_string(countries);
		double percentage = countries / (double)mapSize;
		auto percentageString = to_string(percentage);
		if (percentage == 100) {
			GameOver = true;
			winner = player;
			break;
		}
		else if (percentage != 0) {
			t.add(player->getName());
			t.add(str);
			t.add(percentageString + "%");
			t.endOfRow();
		}
	}
	if (GameOver) {
		clearScreen();
		TextTable winBanner('-', '|', '#');
		winBanner.add("Congrats " + winner->getName() + " you have won!!!");
		winBanner.endOfRow();
		cout << winBanner;
	}
	else {
		t.setAlignment(2, TextTable::Alignment::RIGHT);
		cout << t;
	}
}
