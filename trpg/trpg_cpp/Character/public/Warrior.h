#pragma once
#include "../public/Job.h"

class CharacterStat;
class Potion;

class Warrior : public Job
{
public:
	Warrior(Character& Owner);
	~Warrior();

	void Promoted() override;
	void Promote_Buff() override;
	void Attack(Character& Target) override;
};