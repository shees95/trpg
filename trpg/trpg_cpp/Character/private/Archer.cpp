#include "../public/Archer.h"
#include "../public/Character.h"
#include "../public/CharacterStat.h"

#include "../../UI/public/BaseUI.h"
#include <algorithm>

Archer::Archer(Character& Owner)
	: Job(Owner)
{
	Job_Name = "Archer";
	Weapon_Name = "arrow";

	Promoted();
	Promote_Buff();

	BaseUI::Print_BorderLine_Double();
	BaseUI::Print_ln(2);

	maxAttackChance = 1;
}

Archer::~Archer()
{
}

void Archer::Promoted()
{
	BaseUI::Print_ln("* You became a " + Job_Name);
	BaseUI::Print_ln("* You can use " + Weapon_Name);
	
}

void Archer::Promote_Buff()
{
	GetOwner().GetStat().Buff_Add(0, 50);
}

void Archer::Attack(Character& Target)
{

	CharacterStat& tst = Target.GetStat();
	CharacterStat& ost = GetOwner().GetStat();


	if (GetDoubleChance()) maxAttackChance = 2;
	

	// 체력 적용
	int PlayerAP = ost.GetAP();
	int TargetDP = tst.GetDP();
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

	maxAttackChance = 1;
}

bool Archer::GetDoubleChance()
{
	int random = rand() % 100 + 1;
	return random <= DblRate;
}
