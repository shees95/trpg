#include <iostream>
#include <string>

#include "../public/Character.h"
#include "../public/CharacterStat.h"
#include "../public/Job.h"

#include "../../System/public/Inventory.h"

#include "../../System/public/_TUI.h"

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

void Character::CreateName()
{
	string Name = "";

	while (true)
	{
		Print("Enter your hero's name: ");
		cin >> Name;

		if (Name.length() > 0)
		{
			SetName(Name);

			Print_ln(2);
			return;
		}
	}
}

void Character::SetJob(Job* job)
{
	if (this->job != nullptr)
	{
		delete this->job;
	}
	this->job = job;
}

Job* Character::GetJob()
{
	return job;
	
}

void Character::PrintPlayerStatus()
{
	Print_BorderLine_Double();

	Print_ln();
	Print("Name : " + GetName()); Print_t();
	Print("Job : " + GetJob()->GetJobName()); Print_t();
	Print_ln("Lv." + to_string(characterStat.GetLv()));

	Print_t("HP: " + to_string(characterStat.GetHP()));
	Print_t("MP: " + to_string(characterStat.GetMP()));
	Print_t("AP: " + to_string(characterStat.GetAP()));
	Print_t("DP: " + to_string(characterStat.GetDP()));

	Print_BorderLine_Double();

}
