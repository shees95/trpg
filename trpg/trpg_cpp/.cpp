#include "Warrior.h"
#include "Character.h"
#include "CharacterStat.h"
#include "TUI.h"

using namespace TUI;


Warrior::Warrior(Character* Owner) : Job(Owner)
{
	
}

Warrior::~Warrior()
{
}



void Warrior::Promoted()
{
	Job_Name = "Warrior";
	Weapon_Name = "Sword";
}

void Warrior::Promoted_Message()
{
	Print_ln("* You promoted to warrior.");

	Owner->getStat()->Buff_Add(0, 50);
	Print_ln();

	Print_ln("* You can swing your sword!");
}

void Warrior::Attack(Character* Target)
{
	Print_ln(Target->getName() + "을(를) " + Weapon_Name + "(으)로 베었습니다." + " (" + to_string(Owner->getStat()->getAP()) + ")");

}

void Warrior::Hit(Character* Causer)
{
	Print_ln(Causer->getName() + "(에)게 공격 당했습니다." + " (" + to_string(Causer->getStat()->getAP()) + ")");

}