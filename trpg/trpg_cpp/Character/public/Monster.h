#pragma once
#include <string>
#include <vector>
#include "../public/Character.h"
#include "../../System/public/DBM.h"

using namespace std;

class Monster : public Character
{
private:
	int var = 0;
	
public:
	Monster(const FMonster& NewMonster);
	~Monster() {};
	
	void Init(const FMonster& NewMonster);
	
	void SetVar(int var);
	
	void Attack(Character& player);

	void CreateHP(int a, int b);
	void CreateMP(int a, int b);
	void CreateAP(int a, int b);
	void CreateDP(int a, int b);

	int GetRand(int a, int b);

	void Print_HitLog(Character& Target, int PushDamage);
};