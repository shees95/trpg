#include <iostream>

#include "CharacterStat.h"
#include "Character.h"
#include "Potion.h"

#include "TUI.h"


using namespace TUI;

CharacterStat::~CharacterStat()
{
}

void CharacterStat::addLv()
{

	exp -= maxexp;
	maxexp += 30;
	this->Level = getLv() + 1;

	this->setMaxHP(getMaxHP() + 10);
	this->addHP(getHP() + 10);
	this->setMaxMP(getMaxMP() + 5);
	this->addMP(getMP() + 5);
	this->setAP(getAP() + 5);
	this->setDP(getDP() + 1);

	Print_ln("-> Level UP! (Lv." + to_string(getLv()) + " -> " + to_string(getLv() - 1) + ")");
	Print_ln("-> HP +10, MP +5, AP +5, DP +1");
}
void CharacterStat::setLv(const int& lv)
{

	this->Level = lv;
}

void CharacterStat::addExp(const int& val)
{
	this->exp += val;
	Print_ln("-> +" + to_string(val) + "EXP! (EXP: " + to_string(this->exp) + "/" + to_string(this->maxexp) + ")");
	

	if (exp >= maxexp)
	{
		addLv();
	}
}

void CharacterStat::Init_HPMP()
{
	int HP = 0, MP = 0;
	int minHP = 50, minMP = 50;

	while (getHP() < minHP || getMP() < minMP)
	{
		Print("Enter HP and MP: ");
		cin >> HP >> MP;

		setHP(HP);
		setMP(MP);
		setMaxHP(HP);
		setMaxMP(MP);

		if (getHP() < 50 || getMP() < 50)
		{
			Print_ln("HP or MP is too low. Try again.");
		}
	}

	Print_ln(1);
	return;

}

void CharacterStat::Init_APDP()
{
	int AP = 0, DP = 0;
	int minAP = 50, minDP = 50;

	while (getAP() < minAP || getDP() < minDP)
	{
		Print("Enter AP and DP: ");
		cin >> AP >> DP;

		setAP(AP);
		setDP(DP);

		if (getAP() < minAP || getDP() < minDP)
		{
			Print_ln("AP or DP is too low. Try again.");
		}
	}

	Print_ln(2);
	return;

}

void CharacterStat::setMaxHP(int maxhp)
{
	maxstat[0] = maxhp;
}

void CharacterStat::setMaxMP(int maxmp)
{
	maxstat[1] = maxmp;
}

void CharacterStat::setMaxAP(int maxap)
{
	maxstat[2] = maxap;
}

void CharacterStat::setMaxDP(int maxdp)
{
	maxstat[3] = maxdp; 
}

void CharacterStat::setHP(int hp)
{
	this->stat[0] = max(hp, 0);
}

void CharacterStat::addHP(int hp)
{
	setHP(min(getHP() + hp, getMaxHP()));
}

void CharacterStat::setMP(int mp)
{
	this->stat[1] = max(mp, 0);
}

void CharacterStat::addMP(int mp)
{
	setMP(min(getMP() + mp, getMaxMP()));
}

void CharacterStat::setAP(int ap)
{
	this->stat[2] = max(ap, 1);
}

void CharacterStat::setDP(int dp)
{
	this->stat[3] = max(dp, 1);
}

void CharacterStat::Print_Stat()
{
	CharacterStat Stat = getOwner()->getStat();

	Print_BorderLine_Double();

	Print_ln(); Print_t();
	Print_t("Lv. " + to_string(getLv()));
	Print_t(Owner->getName() + "'s Stats");
	Print("(Exp: " + to_string(exp) + "/" + to_string(maxexp) + ")");

	Print_ln();
	Print_BorderLine_Single();

	Print_t("HP: " + to_string(Stat.getHP()) + " / " + to_string(Stat.getMaxHP()));
								   									 
	Print_t("MP: " + to_string(Stat.getMP()) + " / " + to_string(Stat.getMaxMP()));
	Print_ln();					   
								   
	Print_t("AP: " + to_string(Stat.getAP()));
								   
	Print_t("DP: " + to_string(Stat.getDP()));
	Print_BorderLine_Double();
}

void CharacterStat::Buff_Add(int statindex, int value)
{

	switch (statindex)
	{
	case 0:
		setHP(getHP() + value);
		setMaxHP(max(getMaxHP(), getHP()));
		Print("* HP has increased " + to_string(value));
		Print_ln(" point. ");
		
		break;

	case 1:
		setMP(getMP() + value);
		setMaxMP(max(getMaxMP(), getMP()));
		Print("* MP has increased " + to_string(value));
		Print_ln(" point. ");
		
		break;

	case 2:
		setAP(getAP() + value);
		Print_ln("* AP has increased " + to_string(value));

		break;

	case 3:
		setDP(getDP() + value);
		Print_ln("* DP has increased " + to_string(value));

		break;
	}
}

void CharacterStat::Buff_Mul(int statindex, int value)
{

	switch (statindex)
	{
	case 0:
		setHP(getHP() * value);
		Print("* HP has multiplied " + to_string(value));
		Print(" point.");
		
		break;

	case 1:
		setMP(getMP() * value);
		Print("* MP has multiplied " + to_string(value));
		Print(" point. ");

		break;

	case 2:
		setAP(getAP() * value);
		Print_ln("* AP has multiplied " + to_string(value));
		Print_ln("* Now your AD is " + to_string(getAP()));

		break;

	case 3:
		setDP(getDP() * value);
		Print_ln("* DP has multiplied " + to_string(value));
		Print_ln("* Now your AD is " + to_string(getDP()));

		break;
	}
}