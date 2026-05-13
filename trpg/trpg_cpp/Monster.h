#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "DBM.h"

using namespace std;

class Monster : public Character
{
private:
	Character* Owner;
	string dropItemName = "";
	int dropItemPrice = 0;

	int Lv = 0;

	int var = 1;
	
public:
	Monster(string name, MonsterDB m_db);

	void setLv(int Lv) { this->Lv = Lv; }
	void setVar(int var) { this->var = var; }

	void Attack(Character& player);

	void createHP(int a, int b);
	void createMP(int a, int b);
	void createAP(int a, int b);
	void createDP(int a, int b);

	int getRand(int a, int b);

	void Print_HitLog(Character& Target, int PushDamage);
};