#include "../public/Warrior.h"
#include "../public/Character.h"
#include "../public/CharacterStat.h"

#include "../../System/public/_TUI.h"
#include <algorithm>

using namespace TUI;

Warrior::Warrior(Character& Owner) : Job(Owner)
{
	Job_Name = "Warrior";
	Weapon_Name = "sword";

	Promoted();
	Promote_Buff();

	Print_BorderLine_Double();
	Print_ln(2);

	maxAttackChance = 1;
}

Warrior::~Warrior()
{
}

void Warrior::Promoted()
{
	Print_ln("* You became a " + Job_Name);
	Print_ln("* You can use " + Weapon_Name);

}

void Warrior::Promote_Buff()
{
	GetOwner().GetStat().Buff_Add(3, 30);
}

void Warrior::Attack(Character& Target)
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

		if (PushDamage <= 0) Print_ln(" (Dead)");
		else Print_ln();
	}

	// 데미지 적용
	tst.SetHP(PushDamage);

}