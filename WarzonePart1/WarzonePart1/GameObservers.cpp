//#include "GameObservers.h"
//
//bool Publisher::isSubscribed(const IObservable& observer)
//{
//	for (IObservable& sub : subscribers) {
//		if (&sub == &observer ){
//			return true;
//		}
//	}
//	return false;
//}
//
//void Publisher::subscribe(IObservable& observer)
//{
//	subscribers.push_back(observer);
//}
//
//void Publisher::nofityAll()
//{
//	for (IObservable& subscriber : subscribers) {
//		subscriber.update();
//	}
//}
//
//void Publisher::unsubscribe(IObservable&)
//{
//	remove_if(subscribers.begin(), subscribers.end(), isSubscribed);
//}
