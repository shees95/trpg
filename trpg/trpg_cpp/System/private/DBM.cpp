#include <string>
#include "../public/DBM.h"
#include "../public/ItemBase.h"
#include "../public/MonsterBase.h"

class MonsterDB;

namespace DB
{
	static map<string, FMonster> MonsterTable;
	static map<string, FItemBase> ItemTable;
	static map<string, vector<string>> DropItemTable;
	static map<int, vector<string>> LevelTable;
}

DBM::DBM()
{
	if(DB::MonsterTable.empty()) Init();
}

void DBM::Init()
{
	// 몬스터 DB
	DB::MonsterTable.emplace("Rat",		FMonster{"Rat", 1, 50, 20, 30, 20, 25, 1});
	DB::MonsterTable.emplace("Slime",	FMonster{"Slime", 1, 70, 20, 20, 20, 30, 1});
	DB::MonsterTable.emplace("Goblin",	FMonster{"Goblin", 1, 120, 40, 35, 25, 60, 2});
	
	DB::MonsterTable.emplace("Orc",		FMonster{"Orc", 2, 150, 10, 55, 45, 120, 4});
	DB::MonsterTable.emplace("Skeleton",FMonster{"Skeleton", 2, 120, 30, 65, 25, 130, 4});
	DB::MonsterTable.emplace("Harpy",	FMonster{"Harpy", 2, 230, 50, 85, 45, 230, 5});
	
	DB::MonsterTable.emplace("Lich",	FMonster{"Lich", 3, 240, 80, 125, 35, 350, 7});
	DB::MonsterTable.emplace("Kraken",	FMonster{"Kraken", 3, 310, 30, 105, 55, 450, 7});
	DB::MonsterTable.emplace("Chimera",	FMonster{"Chimera", 3, 420, 50, 135, 85, 600, 9});
	
	DB::MonsterTable.emplace("Dragon",	FMonster{"Dragon", 4, 800, 150, 175, 155, 1000, 15});
	
	for (auto& pair : DB::MonsterTable)
	{
		DB::LevelTable[pair.second.lv].push_back(pair.first);
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
	DB::ItemTable.emplace("Rat's tail",			FItemBase{"Rat's tail", 30, 10, -1, 0});
	DB::ItemTable.emplace("Slime's gel",		FItemBase{"Slime's gel", 45, 10, 0, 10});
	DB::ItemTable.emplace("Goblin's stab",		FItemBase{"Goblin's stab", 55, 5, 4, 1});
	
	DB::ItemTable.emplace("Orc's hammer",		FItemBase{"Orc's hammer", 75, 1, 4, 5});
	DB::ItemTable.emplace("Skeleton's bone",	FItemBase{"Skeleton's bone", 75, 1, 0, 25});
	DB::ItemTable.emplace("Harpy's feather",	FItemBase{"Harpy's feather", 90, 1, -1, 0});
	
	DB::ItemTable.emplace("Lich's wand",		FItemBase{"Lich's wand", 130, 1, 3, 35});
	DB::ItemTable.emplace("Kraken's leg",		FItemBase{"Kraken's leg", 180, 1, -1, 0});
	DB::ItemTable.emplace("Chimera's teeth",	FItemBase{"Chimera's teeth", 230, 1, -1, 0});
	
	DB::ItemTable.emplace("Dragon's heart",		FItemBase{"Dragon's heart", 530, 1, 1, 50});
	
	DB::ItemTable.emplace("herb",				FItemBase{"herb", 50, 1, 0, 50});
	DB::ItemTable.emplace("clear water",		FItemBase{"clear water", 80, 1, 2, 20});
	DB::ItemTable.emplace("berry",				FItemBase{"berry", 60, 1, 2, 30});

	DB::ItemTable.emplace("HP Potion",			FItemBase{"HP Potion", 200, 5, 0, 80});
	DB::ItemTable.emplace("MP Potion",			FItemBase{"MP Potion", 250, 5, 2, 70});
}

const FMonster& DBM::GetMonsterDB(string key)
{
	// TODO: insert return statement here
	return DB::MonsterTable.at(key);
}

const vector<string>& DBM::GetDropItemFromName(string key)
{
	return DB::DropItemTable.at(key);
}

const FItemBase& DBM::GetItemFromName(string key)
{
	return DB::ItemTable.at(key);
}


const string& DBM::GetRandomMonsterKey(int Lv)
{
	// TODO: insert return statement here
	vector<string>& monsters = DB::LevelTable[Lv];

	return monsters[rand() % monsters.size()];
}
