#include "GameObservers.h"
#include <iostream>

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

void Publisher::subscribe(IObservable *observer)
{
	observers.push_back(observer);
}

void Publisher::nofityAll(string data)
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
	cout << "\e[1;1H\e[2J";
	cout << data;
}