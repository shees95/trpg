#pragma once

#include <vector>
#include <map>


struct FMonster;
struct FItemBase;

using namespace std;

class DBM
{
private:
	static map<string, FMonster> MonsterTable;
	static map<string, FItemBase> ItemTable;
	static map<string, vector<string>> DropItemTable;
	static map<int, vector<string>> LevelTable;
	
public:
	DBM();
	~DBM() {};

	void Init();

	static const FMonster& GetMonsterDB(string key);
	static const vector<string>& GetDropItemFromName(string key);
	static const FItemBase& GetItemFromName(string key);
	static const string& GetRandomMonsterKey(int Lv);
	
};