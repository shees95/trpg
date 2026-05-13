#include <iostream>
#include <string>

#include "Character.h"
#include "CharacterStat.h"
#include "Potion.h"
#include "Job.h"
#include "Inventory.h"

#include "TUI.h"

using namespace std;
using namespace TUI;

Character::Character()
	: characterStat(this), inventory(this)
{
	job = nullptr;
}

Character::~Character()
{
	delete job;
}

void Character::createName()
{
	string Name = "";

	while (true)
	{
		Print("Enter your hero's name: ");
		cin >> Name;

		if (Name.length() > 0)
		{
			setName(Name);

			Print_ln(2);
			return;
		}
	}
}

Job* Character::getJob()
{
	return job;
	
}

void Character::PrintPlayerStatus()
{
	Print_BorderLine_Double();

	Print_ln();
	Print("Name : " + getName()); Print_t();
	Print("Job : " + getJob()->getJobName()); Print_t();
	Print_ln("Lv." + to_string(characterStat.getLv()));

	Print_t("HP: " + to_string(characterStat.getHP()));
	Print_t("MP: " + to_string(characterStat.getMP()));
	Print_t("AP: " + to_string(characterStat.getAP()));
	Print_t("DP: " + to_string(characterStat.getDP()));

	Print_BorderLine_Double();

}
