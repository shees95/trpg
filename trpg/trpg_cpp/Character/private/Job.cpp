#include <iostream>

#include <String>

#include "../public/Job.h"
#include "../public/Warrior.h"
#include "../public/Archer.h"
#include "../public/Magician.h"
#include "../public/Thief.h"

#include "../public/Character.h"

#include "../../System/public/_TUI.h"

using namespace std;
using namespace TUI;

Job::Job(Character& Owner)
{ 
	this->Owner = &Owner;
}

Job::~Job()
{
}

string Job::GetJobName()
{
	return Job_Name;
}

string Job::GetWeapon()
{
	return Weapon_Name;
}

void Job::Print_HitLog(Character& Target, int PlayerAP, int PushedDamage, int PushDamage)
{
	Print_ln("You use " + Weapon_Name + " to " + Target.GetName() + " (" + to_string(PlayerAP) + ")");
	Print(Target.GetName() + " HP : " + to_string(PushedDamage) + " -> " + to_string(PushDamage));
}

