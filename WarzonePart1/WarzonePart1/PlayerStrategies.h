#pragma once
#include "Player.h"
class IPlayerStrategy {
private:
public:
	virtual void issueOrder(string, Player*, Player*, Territory*, Territory*, int) = 0;
	virtual vector<Territory*>* toAttack(Player*) = 0;
	virtual vector<Territory*>* toDefend(Player*) = 0;
};

class HumanPlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack(Player*) override;
	vector<Territory*>* toDefend(Player*) override;
};

class AggressivePlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack(Player*) override;
	vector<Territory*>* toDefend(Player*) override;
};

class BenevolentPlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack(Player*) override;
	vector<Territory*>* toDefend(Player*) override;
};

class NeutralPlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack(Player*) override;
	vector<Territory*>* toDefend(Player*) override;
};