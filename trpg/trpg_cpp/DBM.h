#pragma once

#include <vector>
#include <map>

using namespace std;



class MonsterDB
{
	string name = "";

	int lv = 0;

	int hp;
	int mp;
	int ap;
	int dp;

	int money;

	int var;
public:
	MonsterDB(string name, int lv, int hp, int mp, int ap, int dp, int money, int var);

	string getName() { return name; }

	int getLv() { return lv; };
	int getHP() { return hp; };
	int getMP() { return mp; };
	int getAP() { return ap; };
	int getDP() { return dp; };

	int getVar() { return var; }

};

class DBM
{
public:

	void Init();

	MonsterDB& GetMonsterDB(string key);

	int GetItemValue(string key);

	vector<string> GetDropItemKeys(string key);

	string GetRandomMonsterKey(int Lv);

	DBM();
	~DBM() {};
};