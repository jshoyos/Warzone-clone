#pragma once
#include "Player.h"
class IPlayerStrategy {
private:
public:
	virtual void issueOrder(string, Player*, Player*, Territory*, Territory*, int) = 0;
	virtual vector<Territory*>* toAttack() = 0; 
	virtual vector<Territory*>* toDefend() = 0;
};

class HumanPlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack() override;
	vector<Territory*>* toDefend() override;
};

class AggressivePlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack() override;
	vector<Territory*>* toDefend() override;
};

class BenevolentPlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack() override;
	vector<Territory*>* toDefend() override;
};

class NeutralPlayerStrategy : public IPlayerStrategy {
public:
	void issueOrder(string, Player*, Player*, Territory*, Territory*, int) override;
	vector<Territory*>* toAttack() override;
	vector<Territory*>* toDefend() override;
};