#include "GameObservers.h"
#include "GameObservers.h"

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

void Publisher::nofityAll()
{
	for (IObservable *observer : observers) {
		observer->update();
	}
}

void Publisher::unsubscribe(IObservable* observer)
{
	if (isSubscribed(observer)) {
		auto it = find(observers.begin(), observers.end(), observer);
		observers.erase(it);
	}
}
