#pragma once
#include "../public/Job.h"

class CharacterStat;
class Potion;

class Magician : public Job
{
public:
	Magician(Character& Owner);
	~Magician();


	void Promoted() override;
	void Promote_Buff() override;
	void Attack(Character& Target) override;
};