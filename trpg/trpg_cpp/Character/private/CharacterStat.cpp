#include <iostream>

#include "../public/CharacterStat.h"
#include "../public/Character.h"

#include "../../System/public/_TUI.h"


using namespace TUI;

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

	Print_ln("-> Level UP! (Lv." + to_string(GetLv() - 1) + " -> " + to_string(GetLv()) + ")");
	Print_ln("-> HP +10, MP +5, AP +5, DP +1");
}

void CharacterStat::SetExp(const int& exp)
{
	stat[8] = exp;
}

void CharacterStat::AddExp(const int& val)
{
	SetExp(GetExp() + val);
	Print_ln("-> +" + to_string(val) + "EXP! (EXP: " + to_string(GetExp()) + "/" + to_string(GetMaxExp()) + ")");
	
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
		Print("Enter HP and MP: ");
		cin >> HP >> MP;
		
		// 최소치
		if (HP < minHP || MP < minMP)
		{
			Print_ln("HP or MP is too low. Try again.");
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

	Print_ln(1);
	return;

}

void CharacterStat::Init_APDP()
{
	int AP = 0, DP = 0;
	int minAP = 50, minDP = 50;

	while (true)
	{
		Print("Enter AP and DP: ");
		cin >> AP >> DP;
		
		if (AP < minAP || DP < minDP)
		{
			Print_ln("AP or DP is too low. Try again.");
		}
		else
		{
			SetAP(AP);
			SetDP(DP);
			
			break;
		}
	}

	Print_ln(2);
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

void CharacterStat::Print_Stat()
{
	CharacterStat Stat = GetOwner()->GetStat();

	Print_BorderLine_Double();

	Print_ln(); Print_t();
	Print_t("Lv. " + to_string(GetLv()));
	Print_t(Owner->GetName() + "'s Stats");
	Print("(Exp: " + to_string(GetExp()) + "/" + to_string(GetMaxExp()) + ")");

	Print_ln();
	Print_BorderLine_Single();

	Print_t("HP: " + to_string(Stat.GetHP()) + " / " + to_string(Stat.GetMaxHP()));
								   									 
	Print_t("MP: " + to_string(Stat.GetMP()) + " / " + to_string(Stat.GetMaxMP()));
	Print_ln();					   
								   
	Print_t("AP: " + to_string(Stat.GetAP()));
								   
	Print_t("DP: " + to_string(Stat.GetDP()));
	Print_BorderLine_Double();
}

void CharacterStat::Buff_Add(int statindex, int value)
{

	switch (statindex)
	{
	case 0:
		SetHP(GetHP() + value);
		SetMaxHP(max(GetMaxHP(), GetHP()));
		Print("* HP has increased " + to_string(value));
		Print_ln(" point. ");
		
		break;

	case 1:
		SetMP(GetMP() + value);
		SetMaxMP(max(GetMaxMP(), GetMP()));
		Print("* MP has increased " + to_string(value));
		Print_ln(" point. ");
		
		break;

	case 2:
		SetAP(GetAP() + value);
		Print_ln("* AP has increased " + to_string(value));

		break;

	case 3:
		SetDP(GetDP() + value);
		Print_ln("* DP has increased " + to_string(value));

		break;
	}
}

void CharacterStat::Buff_Mul(int statindex, int value)
{

	switch (statindex)
	{
	case 0:
		SetHP(GetHP() * value);
		Print("* HP has multiplied " + to_string(value));
		Print(" point.");
		
		break;

	case 1:
		SetMP(GetMP() * value);
		Print("* MP has multiplied " + to_string(value));
		Print(" point. ");

		break;

	case 2:
		SetAP(GetAP() * value);
		Print_ln("* AP has multiplied " + to_string(value));
		Print_ln("* Now your AD is " + to_string(GetAP()));

		break;

	case 3:
		SetDP(GetDP() * value);
		Print_ln("* DP has multiplied " + to_string(value));
		Print_ln("* Now your AD is " + to_string(GetDP()));

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
