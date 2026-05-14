#include "../public/Warrior.h"
#include "../public/Character.h"
#include "../public/CharacterStat.h"

#include "../../UI/public/BaseUI.h"
#include <algorithm>

Warrior::Warrior(Character& Owner) : Job(Owner)
{
	Job_Name = "Warrior";
	Weapon_Name = "sword";

	Promoted();
	Promote_Buff();

	BaseUI::Print_BorderLine_Double();
	BaseUI::Print_ln(2);

	maxAttackChance = 1;
}

Warrior::~Warrior()
{
}

void Warrior::Promoted()
{
	BaseUI::Print_ln("* You became a " + Job_Name);
	BaseUI::Print_ln("* You can use " + Weapon_Name);

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

		if (PushDamage <= 0) BaseUI::Print_ln(" (Dead)");
		else BaseUI::Print_ln();
	}

	// 데미지 적용
	tst.SetHP(PushDamage);

}