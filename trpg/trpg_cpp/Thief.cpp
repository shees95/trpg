#include "Thief.h"
#include "Character.h"
#include "CharacterStat.h"

#include "TUI.h"
#include <algorithm>

using namespace TUI;

Thief::Thief(Character& Owner) : Job(Owner)
{
	Job_Name = "Thief";
	Weapon_Name = "dagger";

	Promoted();
	Promote_Buff();

	Print_BorderLine_Double();
	Print_ln(2);

	maxAttackChance = 5;
}

Thief::~Thief()
{
}

void Thief::Promoted()
{
	Print_ln("* You became a " + Job_Name);
	Print_ln("* You can use " + Weapon_Name);

}

void Thief::Promote_Buff()
{
	getOwner().getStat().Buff_Add(2, 30);
}

void Thief::Attack(Character& Target)
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