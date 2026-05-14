#pragma once
#include <string>

#include "../public/CharacterStat.h"
#include "../../System/public/Inventory.h"
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

	CharacterStat& GetStat() { return characterStat; }
	Inventory& GetInventory() { return inventory; }
	
	void CreateName();
	void SetName(const string& Name) { this->Name = Name; }
	void SetJob(Job* job);
	
	Job* GetJob();
	Character& GetOwner() { return *this; }
	
	const string& GetName() { return Name; }

	void PrintPlayerStatus();
};