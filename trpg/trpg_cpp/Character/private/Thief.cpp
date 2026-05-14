#include "../public/Thief.h"
#include "../public/Character.h"
#include "../public/CharacterStat.h"

#include "../../UI/public/BaseUI.h"
#include <algorithm>

Thief::Thief(Character& Owner) : Job(Owner)
{
	Job_Name = "Thief";
	Weapon_Name = "dagger";

	Promoted();
	Promote_Buff();

	BaseUI::Print_BorderLine_Double();
	BaseUI::Print_ln(2);

	maxAttackChance = 5;
}

Thief::~Thief()
{
}

void Thief::Promoted()
{
	BaseUI::Print_ln("* You became a " + Job_Name);
	BaseUI::Print_ln("* You can use " + Weapon_Name);

}

void Thief::Promote_Buff()
{
	GetOwner().GetStat().Buff_Add(2, 30);
}

void Thief::Attack(Character& Target)
{
	CharacterStat& tst = Target.GetStat();
	CharacterStat& ost = GetOwner().GetStat();
	
	
	// 체력 적용
	int PlayerAP = ost.GetAP() / maxAttackChance;
	int TargetDP = tst.GetDP() / maxAttackChance;
	int PushedDamage = tst.GetHP();
	int PushDamage = tst.GetHP();

	for (int attackChance = 0; attackChance < maxAttackChance; attackChance++)
	{

		PushDamage -= max(PlayerAP - TargetDP, 1);

		Print_HitLog(Target, PlayerAP, PushedDamage, PushDamage);

		PushedDamage = PushDamage;

		if (PushDamage <= 0) BaseUI::Print_ln(" (Dead)");
		else BaseUI::Print_ln();
	}

	// 데미지 적용
	tst.SetHP(PushDamage);

}