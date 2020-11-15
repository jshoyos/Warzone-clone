#include <vector>
#include <string>
using namespace std;
#pragma once
class IObservable {
protected:
	static void clearScreen();
public:
	virtual void update(string) = 0;
};

class Publisher {
private:
	vector<IObservable*> observers;
public:
	void subscribe(IObservable*);
	void notifyAll(string data);
	void unsubscribe(IObservable*);
	bool isSubscribed(IObservable*) const;
};

class PhaseObserver : IObservable {
public:
	void update(string) override;
};

class GameStatisticsObserver : IObservable {
public:
	void update(string) override;
};
