#pragma once
#include <iostream>

class Character;

using namespace std;

class CharacterStat
{
public:
	static constexpr int STAT_SIZE = 4;

	CharacterStat() {};
	CharacterStat(Character* Owner) 
	{
		this->Owner = Owner;
	}
	~CharacterStat();


private:
	Character* Owner;

	int stat[STAT_SIZE] = { 0 };
	int maxstat[STAT_SIZE] = { 0 };

	int Level = 1;
	int exp = 0;
	int maxexp = 100;

public:

	Character* getOwner() { return Owner; }

	const int& getMaxHP() const { return maxstat[0]; }
	void setMaxHP(int maxhp = 100);

	const int& getMaxMP() const { return maxstat[1]; }
	void setMaxMP(int maxmp = 100);

	const int& getMaxAP() const { return maxstat[2]; }
	void setMaxAP(int maxap = 32767);

	const int& getMaxDP() const { return maxstat[3]; }
	void setMaxDP(int maxdp = 32767);


	const int& getHP() const { return stat[0]; }
	void setHP(int hp = 0);
	void addHP(int hp);

	const int& getMP() const { return stat[1]; }
	void setMP(int mp = 0);
	void addMP(int mp);

	const int& getAP() const { return stat[2]; }
	void setAP(int ap = 0);

	const int& getDP() const { return stat[3]; }
	void setDP(int dp = 0);

	const int& getLv() const { return Level; }
	void addLv();
	void setLv(const int& lv);
	void addExp(const int& val);

	void Init_HPMP();
	void Init_APDP();

	void Print_Stat();

	void Buff_Add(int index, int value = 0);
	void Buff_Mul(int index, int value = 1);
};
