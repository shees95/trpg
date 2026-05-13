#pragma once
#include <iostream>

class Character;

using namespace std;


class Potion
{
public:
	static constexpr int HP_POTION_SIZE = 5;
	static constexpr int MP_POTION_SIZE = 5;

	static constexpr int HP_Heal_Volumn = 20;
	static constexpr int MP_Heal_Volumn = 20;

	Potion(Character* Owner);
	~Potion();

private:
	Character* Owner;

	int PotionBag[2] = { 0 };


public:

	Character* getOwner();

	void Init_HP_Potion();
	void Init_MP_Potion();

	bool Use_HP_Potion();
	bool Use_MP_Potion();

	void Add_HP_Potion(const int& ex = 0);
	void Add_MP_Potion(const int& ex = 0);

	const int& get_HP_Potion() { return PotionBag[0]; }
	const int& get_MP_Potion() { return PotionBag[1]; }

	void set_HP_Potion(const int& amount = 0);
	void set_MP_Potion(const int& amount = 0);

	static int get_HP_Heal_Volumn() { return HP_Heal_Volumn; }
	static int get_MP_Heal_Volumn() { return MP_Heal_Volumn; }

	void Print_Remain_HP_Potion();
	void Print_Remain_MP_Potion();
	void Print_Remain_Potion();
};