#include "Potion.h"
#include "Character.h"
#include "CharacterStat.h"

#include "TUI.h"

using namespace TUI;

Potion::Potion(Character* Owner)
{
	this->Owner = Owner;

	Init_HP_Potion();
	Init_MP_Potion();

	Print_ln("* HP Potion [5], MP Potion [5] have been provided");
}

Potion::~Potion()
{

}

Character* Potion::getOwner()
{
	return this->Owner;
}

void Potion::Init_HP_Potion()
{
	set_HP_Potion(HP_POTION_SIZE);

}

void Potion::Init_MP_Potion()
{
	set_MP_Potion(MP_POTION_SIZE);

}

bool Potion::Use_HP_Potion()
{
	if (get_HP_Potion() <= 0)
	{
		Print_ln("!! HP Potion is not remained !!");

		return false;
	}
	else
	{
		set_HP_Potion(get_HP_Potion() - 1);

		return true;
	}
	
}

bool Potion::Use_MP_Potion()
{
	if (get_MP_Potion() <= 0)
	{
		Print_ln("!! MP Potion is not remained !!");

		return false;
	}
	else
	{
		set_MP_Potion(get_MP_Potion() - 1);

		return true;
	}
}

void Potion::Add_HP_Potion(const int& amount)
{
	set_HP_Potion(get_HP_Potion() + amount);
}

void Potion::Add_MP_Potion(const int& amount)
{
	set_MP_Potion(get_MP_Potion() + amount);
}

void Potion::set_HP_Potion(const int& amount)
{
	PotionBag[0] = max(amount, 0);
}

void Potion::set_MP_Potion(const int& amount)
{
	PotionBag[1] = max(amount, 0);
}

void Potion::Print_Remain_HP_Potion()
{
	Print_ln("1. HP Potion [" + to_string(get_HP_Potion()) + "]");
}

void Potion::Print_Remain_MP_Potion()
{
	Print_ln("2. MP Potion [" + to_string(get_MP_Potion()) + "]");
}

void Potion::Print_Remain_Potion()
{
	Print_ln("[ Potion Bag ]");

	Print_Remain_HP_Potion();
	Print_Remain_MP_Potion();
}
