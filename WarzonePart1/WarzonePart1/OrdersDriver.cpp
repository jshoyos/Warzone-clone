////This file contains the main function that serves for testing
//
//#include "Orders.h"
//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//	Deploy* order1 = new Deploy("deploy");
//	Bomb* order2 = new Bomb("bomb");
//	Airlift* order3 = new Airlift("airlift");
//	Blockade* order5 = new Blockade("blockade");
//	Negotiate* order4 = new Negotiate("negotiate");
//
//	OrdersList* commandList = new OrdersList();
//	//Testing validate method, this should fail since the order has not been added to the List.
//	order1->validate(&commandList->_ordersList);
//
//	commandList->queueOrder(dynamic_cast<Order*>(order1));
//	commandList->queueOrder(dynamic_cast<Order*>(order2));
//	commandList->queueOrder(dynamic_cast<Order*>(order3));
//	commandList->queueOrder(dynamic_cast<Order*>(order4));
//	commandList->queueOrder(dynamic_cast<Order*>(order5));
//
//	cout << "The list currently contains:\n" << endl;
//	cout << *commandList << endl;
//
//	cout << "Executing bomb command:\n" << endl;
//	order2->execute(&commandList->_ordersList);
//	cout << "--------------------------------------------------------------\n" << endl;
//	cout << "Using move command:\n" << endl;
//	commandList->move(&commandList->_ordersList, 2, 4);
//	cout << "Swapping elements 2 and 4 in the list and displaying new list:\n" << endl;
//	cout << *commandList << endl;
//	cout << "--------------------------------------------------------------\n" << endl;
//
//	commandList->remove(&commandList->_ordersList, 3);
//	cout << "Removing element 3 from the list" << endl;
//	cout << *commandList << endl;
//
//	delete commandList;
//	commandList = NULL;
//
//}