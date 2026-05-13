#include <iostream>

#include <String>

#include "Job.h"
#include "Warrior.h"
#include "Archer.h"
#include "Magician.h"
#include "Thief.h"

#include "Character.h"

#include "TUI.h"

using namespace std;
using namespace TUI;

Job::Job(Character& Owner)
{ 
	this->Owner = &Owner;
}

Job::~Job()
{
}

string Job::getJobName()
{
	return Job_Name;
}

string Job::getWeapon()
{
	return Weapon_Name;
}

void Job::Print_HitLog(Character& Target, int PlayerAP, int PushedDamage, int PushDamage)
{
	Print_ln("You use " + Weapon_Name + " to " + Target.getName() + " (" + to_string(PlayerAP) + ")");
	Print(Target.getName() + " HP : " + to_string(PushedDamage) + " -> " + to_string(PushDamage));
}

