#pragma once
#include "../public/Job.h"

class CharacterStat;
class Potion;

class Archer : public Job
{
	int DblRate = 30;
public:
	Archer(Character& Owner);
	~Archer();

	void Promoted() override;
	void Promote_Buff() override;
	void Attack(Character& Target) override;
	bool GetDoubleChance();
};
