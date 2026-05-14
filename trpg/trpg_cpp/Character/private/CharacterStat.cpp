#include <iostream>

#include "../public/CharacterStat.h"
#include "../public/Character.h"

#include "../../UI/public/BaseUI.h"


void CharacterStat::Init()
{
	SetMaxExp(100);
	SetExp(0);
	Init_HPMP();
	Init_APDP();
}

void CharacterStat::SetLv(int lv)
{
	this->Level = lv;
}

void CharacterStat::AddLv()
{

	SetExp(GetExp() - GetMaxExp());
	SetMaxExp(GetMaxExp() + 30);
	
	this->Level = GetLv() + 1;

	this->SetMaxHP(GetMaxHP() + 10);
	this->AddHP(GetHP() + 10);
	this->SetMaxMP(GetMaxMP() + 5);
	this->AddMP(GetMP() + 5);
	this->SetAP(GetAP() + 5);
	this->SetDP(GetDP() + 1);

	BaseUI::Print_ln("-> Level UP! (Lv." + to_string(GetLv() - 1) + " -> " + to_string(GetLv()) + ")");
	BaseUI::Print_ln("-> HP +10, MP +5, AP +5, DP +1");
}

void CharacterStat::SetExp(const int& exp)
{
	stat[8] = exp;
}

void CharacterStat::AddExp(const int& val)
{
	SetExp(GetExp() + val);
	BaseUI::Print_ln("-> +" + to_string(val) + "EXP! (EXP: " + to_string(GetExp()) + "/" + to_string(GetMaxExp()) + ")");
	
	while (GetExp() >= GetMaxExp()) 
	{
		AddLv();
	}
	
}

void CharacterStat::SetMaxExp(const int& maxexp)
{
	stat[9] = maxexp;
}


void CharacterStat::Init_HPMP()
{
	int HP = 0, MP = 0;
	int minHP = 50, minMP = 50;

	while (true)
	{
		BaseUI::Print("Enter HP and MP: ");
		cin >> HP >> MP;
		
		// 최소치
		if (HP < minHP || MP < minMP)
		{
			BaseUI::Print_ln("HP or MP is too low. Try again.");
		}
		else
		{
			SetHP(HP);
			SetMP(MP);
			SetMaxHP(HP);
			SetMaxMP(MP);
			
			break;
		}
	}

	BaseUI::Print_ln(1);
	return;

}

void CharacterStat::Init_APDP()
{
	int AP = 0, DP = 0;
	int minAP = 50, minDP = 50;

	while (true)
	{
		BaseUI::Print("Enter AP and DP: ");
		cin >> AP >> DP;
		
		if (AP < minAP || DP < minDP)
		{
			BaseUI::Print_ln("AP or DP is too low. Try again.");
		}
		else
		{
			SetAP(AP);
			SetDP(DP);
			
			break;
		}
	}

	BaseUI::Print_ln(2);
	return;

}

void CharacterStat::SetMaxHP(int maxhp)
{
	stat[1] = maxhp;
}

void CharacterStat::SetMaxMP(int maxmp)
{
	stat[3] = maxmp;
}

void CharacterStat::SetMaxAP(int maxap)
{
	stat[5] = maxap;
}

void CharacterStat::SetMaxDP(int maxdp)
{
	stat[7] = maxdp; 
}

void CharacterStat::SetHP(int hp)
{
	stat[0] = max(hp, 0);
}

void CharacterStat::AddHP(int hp)
{
	SetHP(min(GetHP() + hp, GetMaxHP()));
}

void CharacterStat::SetMP(int mp)
{
	stat[2] = max(mp, 0);
}

void CharacterStat::AddMP(int mp)
{
	SetMP(min(GetMP() + mp, GetMaxMP()));
}

void CharacterStat::SetAP(int ap)
{
	stat[4] = max(ap, 1);
}

void CharacterStat::SetDP(int dp)
{
	stat[6] = max(dp, 1);
}



void CharacterStat::Buff_Add(int statindex, int value)
{

	switch (statindex)
	{
	case 0:
		SetHP(GetHP() + value);
		SetMaxHP(max(GetMaxHP(), GetHP()));
		BaseUI::Print("* HP has increased " + to_string(value));
		BaseUI::Print_ln(" point. ");
		
		break;

	case 1:
		SetMP(GetMP() + value);
		SetMaxMP(max(GetMaxMP(), GetMP()));
		BaseUI::Print("* MP has increased " + to_string(value));
		BaseUI::Print_ln(" point. ");
		
		break;

	case 2:
		SetAP(GetAP() + value);
		BaseUI::Print_ln("* AP has increased " + to_string(value));

		break;

	case 3:
		SetDP(GetDP() + value);
		BaseUI::Print_ln("* DP has increased " + to_string(value));

		break;
	}
}

void CharacterStat::Buff_Mul(int statindex, int value)
{

	switch (statindex)
	{
	case 0:
		SetHP(GetHP() * value);
		BaseUI::Print("* HP has multiplied " + to_string(value));
		BaseUI::Print(" point.");
		
		break;

	case 1:
		SetMP(GetMP() * value);
		BaseUI::Print("* MP has multiplied " + to_string(value));
		BaseUI::Print(" point. ");

		break;

	case 2:
		SetAP(GetAP() * value);
		BaseUI::Print_ln("* AP has multiplied " + to_string(value));
		BaseUI::Print_ln("* Now your AD is " + to_string(GetAP()));

		break;

	case 3:
		SetDP(GetDP() * value);
		BaseUI::Print_ln("* DP has multiplied " + to_string(value));
		BaseUI::Print_ln("* Now your AD is " + to_string(GetDP()));

		break;
	}
}

void CharacterStat::Restore_Add(int index, int value)
{
	if (index % 2 == 0)
	{
		// max 를 넘지 않음
		stat[index] = min(stat[index] + value, stat[index + 1]);		
	}
	else
	{
		// max 값 자체를 늘려줌
		stat[index] = stat[index] + value;
	}
	
}
