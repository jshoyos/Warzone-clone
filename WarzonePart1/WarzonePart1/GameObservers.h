#include <vector>
#include <string>
using namespace std;
#pragma once
/// <summary>
/// Interface for all observers
/// </summary>
class IObservable {
protected:
	string observerName;
	static void clearScreen();
public:
	virtual void update(string) = 0; //Every child must implement their own update method
	string getName();
};

/// <summary>
/// This is the publisher class in charge of notifying all observers
/// </summary>
class Publisher {
private:
	vector<IObservable*> observers; //These are all the observers subscribed to the publisher
public:
	void subscribe(IObservable*); //method used for an observer to subscribe to a specific publisher
	void notifyAll(string observerName, string data); //iterates through all the observers subscribed and notifies them with their update method by polymorphism
	void unsubscribe(IObservable*); //method used to unsubscribe an observer from the publisher
	bool isSubscribed(IObservable*) const; //helper method to know if an observer is already subscribed to the publisher. will also be used in the subscribe method to ensure it is only subscribed once
};

/// <summary>
/// PhaseObserver is the view for the phases.
/// It will display important information on the current running phase
/// </summary>
class PhaseObserver : public IObservable {
public:
	PhaseObserver(string);
	void update(string) override; //Implements its own update method
};

/// <summary>
/// GameStatisticsObserver is the view for the game statistics
/// It will display how many territories each players owns and the percentage of the map they own
/// Will also display a banner with the winner
/// </summary>
class GameStatisticsObserver : public IObservable {
public:
	GameStatisticsObserver(string);
	void update(string) override; //Implements its own update method
};
