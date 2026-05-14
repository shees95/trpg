#pragma once
#include <string>
#include <vector>
#include "ItemBase.h"

class Character;
class DBM;

using namespace std;


class Inventory 
{
private:
	Character* Owner;

	vector<ItemBase> Inven;
	int max = 10;
	int Money = 0;

public:
	Inventory(Character* Owner);

	void AddItem(const FItemBase& Item);
	void AddItems(const FItemBase& Item, int stack);
	void UseItem(const int& index);
	
	void SellItem(const int& index);
	void ExpandSlot(const int& index);
	
	void SetMaxSlot(const int& max);
	int GetMaxSlot() { return max; }

	void AddMoney(const int& money);
	void UseMoney(const int& money);
	const int& GetMoney() { return Money; }

	void ShowInventory();
	
	static bool CompareByPrice(const ItemBase& a, const ItemBase& b);
	void SortInventory();
};
