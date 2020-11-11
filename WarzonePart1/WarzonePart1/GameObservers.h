//#include <vector>
//#include <string>
//using namespace std;
//#pragma once
//class IObservable {
//public:
//	virtual void update() = 0;
//};
//
//class Publisher {
//private:
//	vector<reference_wrapper<IObservable>> subscribers;
//public:
//	void subscribe(IObservable&);
//	void nofityAll();
//	void unsubscribe(IObservable&);
//	bool isSubscribed(const IObservable&);
//};
//
//class PhaseObserver : IObservable {
//public:
//	void update() override;
//};
//
//class GameStatisticsObserver : IObservable {
//
//};