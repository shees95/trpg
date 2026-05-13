#include <string>
#include "DBM.h"

class MonsterDB;

namespace DB
{
	map<string, MonsterDB> MonsterTable;
	map<string, vector<string>> DropItemTable;
	map<string, int> ItemTable;
	map<int, vector<string>> LevelTable;
}

DBM::DBM()
{
	if(DB::MonsterTable.empty()) Init();
}

void DBM::Init()
{
	// 몬스터 DB
	DB::MonsterTable.emplace("Rat",		MonsterDB("Rat", 1, 50, 20, 30, 20, 25, 1));
	DB::MonsterTable.emplace("Slime",	MonsterDB("Slime", 1, 70, 20, 20, 20, 30, 1));
	DB::MonsterTable.emplace("Goblin",	MonsterDB("Goblin", 1, 120, 40, 35, 25, 60, 2));
	
	DB::MonsterTable.emplace("Orc",		MonsterDB("Orc", 2, 150, 10, 55, 45, 120, 4));
	DB::MonsterTable.emplace("Skeleton",MonsterDB("Skeleton", 2, 120, 30, 65, 25, 130, 4));
	DB::MonsterTable.emplace("Harpy",	MonsterDB("Harpy", 2, 230, 50, 85, 45, 230, 5));
	
	DB::MonsterTable.emplace("Lich",	MonsterDB("Lich", 3, 240, 80, 125, 35, 350, 7));
	DB::MonsterTable.emplace("Kraken",	MonsterDB("Kraken", 3, 310, 30, 105, 55, 450, 7));
	DB::MonsterTable.emplace("Chimera",	MonsterDB("Chimera", 3, 420, 50, 135, 85, 600, 9));
	
	DB::MonsterTable.emplace("Dragon",	MonsterDB("Dragon", 4, 800, 150, 175, 155, 1000, 15));
	
	for (auto& pair : DB::MonsterTable)
	{
		DB::LevelTable[pair.second.getLv()].push_back(pair.first);
	}

	// 드랍 아이템 DB
	DB::DropItemTable.emplace("Rat",		vector<string>{ "Rat's tail" });
	DB::DropItemTable.emplace("Slime",		vector<string>{ "Slime's gel" });
	DB::DropItemTable.emplace("Goblin",		vector<string>{ "Goblin's stab" });
	
	DB::DropItemTable.emplace("Orc",		vector<string>{ "Orc's hammer" });
	DB::DropItemTable.emplace("Skeleton",	vector<string>{ "Skeleton's bone" });
	DB::DropItemTable.emplace("Harpy",		vector<string>{ "Harpy's feather" });
	
	DB::DropItemTable.emplace("Lich",		vector<string>{ "Lich's wand" });
	DB::DropItemTable.emplace("Kraken",		vector<string>{ "Kraken's leg" });
	DB::DropItemTable.emplace("Chimera",	vector<string>{ "Chimera's teeth" });
	
	DB::DropItemTable.emplace("Dragon",		vector<string>{ "Dragon's heart" });
	
	DB::DropItemTable.emplace("Common1",	vector<string>{ "herb" });
	DB::DropItemTable.emplace("Common2",	vector<string>{ "clear water" });
	DB::DropItemTable.emplace("Common3",	vector<string>{ "bottle" });


	// 아이템 정보
	DB::ItemTable.emplace("Rat's tail",			30);
	DB::ItemTable.emplace("Slime's gel",		40);
	DB::ItemTable.emplace("Goblin's stab",		55);
	
	DB::ItemTable.emplace("Orc's hammer",		70);
	DB::ItemTable.emplace("Skeleton's bone",	75);
	DB::ItemTable.emplace("Harpy's feather",	90);
	
	DB::ItemTable.emplace("Lich's wand",		130);
	DB::ItemTable.emplace("Kraken's leg",		180);
	DB::ItemTable.emplace("Chimera's teeth",	230);
	
	DB::ItemTable.emplace("Dragon's heart",		530);
	
	DB::ItemTable.emplace("herb",				30);
	DB::ItemTable.emplace("clear water",		30);
	DB::ItemTable.emplace("berry",				30);

	DB::ItemTable.emplace("HP Potion", 50);
	DB::ItemTable.emplace("MP Potion", 50);
}

MonsterDB& DBM::GetMonsterDB(string key)
{
	// TODO: insert return statement here
	return DB::MonsterTable.at(key);
}

int DBM::GetItemValue(string key)
{
	return DB::ItemTable.at(key);
}

vector<string> DBM::GetDropItemKeys(string key)
{
	return DB::DropItemTable.at(key);
}


string DBM::GetRandomMonsterKey(int Lv)
{
	// TODO: insert return statement here
	vector<string>& monsters = DB::LevelTable[Lv];

	return monsters[rand() % monsters.size()];
}


MonsterDB::MonsterDB(string name, int lv, int hp, int mp, int ap, int dp, int money, int var)
{
	this->name = name;

	this->lv = lv;

	this->hp = hp;
	this->mp = mp;
	this->ap = ap;
	this->dp = dp;

	this->money = money;

	this->var = var;
}
