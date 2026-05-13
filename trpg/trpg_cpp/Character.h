#pragma once
#include <string>

#include "CharacterStat.h"
#include "Inventory.h"
class Job;
using namespace std;

class Character
{
public:
	Character();
	~Character();

private:
	string Name;

	CharacterStat characterStat;
	Inventory inventory;
	
	Job* job;

public:

	CharacterStat& getStat() { return characterStat; }
	Inventory& getInventory() { return inventory; }

	void createName();
	void setName(const string& Name) { this->Name = Name; }
	void setJob(Job* job) { this->job = job; }

	Job* getJob();
	Character& getOwner() { return *this; }
	
	const string& getName() { return Name; }

	void PrintPlayerStatus();
};