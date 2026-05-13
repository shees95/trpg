#pragma once

#include <string>

class Character;

using namespace std;

class Job
{
protected:
	Character* Owner;
	
	string Job_Name;
	string Weapon_Name;

	int maxAttackChance = 1;

public:
	Job(Character& Owner);
	virtual ~Job();

	Character& getOwner() { return *Owner; }

	virtual void Promoted() = 0;
	virtual void Promote_Buff() = 0;
	virtual void Attack(Character& Target) = 0;

	string getJobName();
	string getWeapon();

	void Print_HitLog(Character& Target, int PlayerAP, int PushedDamage, int PushDamage);
};
