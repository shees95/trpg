#include "Archer.h"
#include "Character.h"
#include "CharacterStat.h"

#include "TUI.h"
#include <algorithm>

using namespace TUI;

Archer::Archer(Character& Owner)
	: Job(Owner)
{
	Job_Name = "Archer";
	Weapon_Name = "arrow";

	Promoted();
	Promote_Buff();

	Print_BorderLine_Double();
	Print_ln(2);

	maxAttackChance = 1;
}

Archer::~Archer()
{
}

void Archer::Promoted()
{
	Print_ln("* You became a " + Job_Name);
	Print_ln("* You can use " + Weapon_Name);
	
}

void Archer::Promote_Buff()
{
	getOwner().getStat().Buff_Add(0, 50);
}

void Archer::Attack(Character& Target)
{

	CharacterStat& tst = Target.getStat();
	CharacterStat& ost = getOwner().getStat();


	if (getDoubleChance()) maxAttackChance = 2;
	

	// 체력 적용
	int PlayerAP = ost.getAP();
	int TargetDP = tst.getDP();
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

	maxAttackChance = 1;
}

bool Archer::getDoubleChance()
{
	srand(time(NULL));
	int min = 1, max = 100;
	int random = rand() % (max - min + 1) + min;

	return random < DblRate;
}
