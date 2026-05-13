#include "Warrior.h"
#include "Character.h"
#include "CharacterStat.h"

#include "TUI.h"
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
	getOwner().getStat().Buff_Add(3, 30);
}

void Warrior::Attack(Character& Target)
{

	CharacterStat& tst = Target.getStat();
	CharacterStat& ost = getOwner().getStat();


	// 체력 적용
	int PlayerAP = ost.getAP() / maxAttackChance;
	int TargetDP = tst.getDP() / maxAttackChance;
	int PushedDamage = tst.getHP();
	int PushDamage = tst.getHP();

	for (int attackChance = 0; attackChance < maxAttackChance; attackChance++)
	{

		PushDamage -= max(PlayerAP - TargetDP, 1);

		Print_HitLog(Target, PlayerAP, PushedDamage, PushDamage);

		PushedDamage = PushDamage;

		if (PushDamage <= 0) Print_ln(" (Dead)");
		else Print_ln();
	}

	// 데미지 적용
	tst.setHP(PushDamage);

}