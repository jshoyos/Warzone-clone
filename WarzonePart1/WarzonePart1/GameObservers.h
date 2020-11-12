#include <vector>
#include <string>
using namespace std;
#pragma once
class IObservable {
public:
	virtual void update(string) = 0;
};

class Publisher {
private:
	vector<IObservable*> observers;
public:
	void subscribe(IObservable*);
	void nofityAll(string data);
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