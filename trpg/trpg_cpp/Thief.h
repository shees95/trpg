#pragma once
#include "Job.h"

class CharacterStat;
class Potion;

class Thief : public Job
{
public:
	Thief(Character& Owner);
	~Thief();


	void Promoted() override;
	void Promote_Buff() override;
	void Attack(Character& Target) override;
};