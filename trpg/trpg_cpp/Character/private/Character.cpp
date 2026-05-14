#include <iostream>
#include <string>

#include "../public/Character.h"

#include "../../Interface/public/Actor.h"
#include "../public/CharacterStat.h"
#include "../public/Job.h"
#include "../../System/public/Inventory.h"

#include "../../UI/public/BaseUI.h"

using namespace std;

Character::Character()
	: characterStat(this), inventory(this)
{
	job = nullptr;
}

Character::~Character()
{
	delete job;
}

void Character::CreateCharacter()
{
	CreateName();
	
	GetStat().Init();
}

void Character::CreateName()
{
	string Name = "";

	while (true)
	{
		BaseUI::Print("Enter your hero's name: ");
		cin >> Name;

		if (Name.length() > 0)
		{
			SetName(Name);

			BaseUI::Print_ln();
			break;
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
	BaseUI::Print_BorderLine_Double();

	BaseUI::Print_ln();
	BaseUI::Print_t("Name : " + GetName());
	BaseUI::Print_t("Job : " + GetJob()->GetJobName());
	BaseUI::Print_ln("Lv." + to_string(characterStat.GetLv()));

	BaseUI::Print_t("HP: " + to_string(characterStat.GetHP()));
	BaseUI::Print_t("MP: " + to_string(characterStat.GetMP()));
	BaseUI::Print_t("AP: " + to_string(characterStat.GetAP()));
	BaseUI::Print_t("DP: " + to_string(characterStat.GetDP()));

	BaseUI::Print_BorderLine_Double();

}
