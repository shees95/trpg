#pragma once
#include <iostream>

class Character;

using namespace std;

class CharacterStat
{
public:
	static constexpr int STAT_SIZE = 5;

	CharacterStat(Character* Owner) 
	{
		this->Owner = Owner;
	}
	~CharacterStat() {};


private:
	Character* Owner;

	int stat[STAT_SIZE * 2] = { 0 };
	
	int Level = 1;
	
public:
	
	Character* GetOwner() { return Owner; }

	void Init();
	void Init_HPMP();
	void Init_APDP();
	
	const int& GetLv() const { return Level; }
	void SetLv(int lv = 1);
	void AddLv();
	
	
	const int& GetHP() const { return stat[0]; }
	void SetHP(int hp = 0);
	void AddHP(int hp);

	const int& GetMaxHP() const { return stat[1]; }
	void SetMaxHP(int maxhp = 100);
	
	
	const int& GetMP() const { return stat[2]; }
	void SetMP(int mp = 0);
	void AddMP(int mp);

	const int& GetMaxMP() const { return stat[3]; }
	void SetMaxMP(int maxmp = 100);
	
	
	const int& GetAP() const { return stat[4]; }
	void SetAP(int ap = 0);

	const int& GetMaxAP() const { return stat[5]; }
	void SetMaxAP(int maxap = 32767);
	
	
	const int& GetDP() const { return stat[6]; }
	void SetDP(int dp = 0);

	const int& GetMaxDP() const { return stat[7]; }
	void SetMaxDP(int maxdp = 32767);

	
	const int& GetExp() { return stat[8]; }
	void SetExp(const int& exp = 0);
	void AddExp(const int& val);
	
	const int& GetMaxExp() { return stat[9]; }
	void SetMaxExp(const int& maxexp);

	void Print_Stat();

	void Buff_Add(int index, int value = 0);
	void Buff_Mul(int index, int value = 1);
	
	void Restore_Add(int index, int value = 0);
};
