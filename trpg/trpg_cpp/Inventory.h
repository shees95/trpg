#pragma once
#include <string>
#include <vector>
class Character;
class DBM;
class Potion;

using namespace std;


class Inventory 
{
private:
	Character* Owner;

	vector<string> Inven;
	int max = 10;
	int Money = 0;

	Potion* PotionBag;

public:
	Inventory(Character* Owner);

	void addItem(const string& name);
	
	void sellItem(const int& index);
	void expandSlot(int index);
	
	void setMaxSlot(int max);
	int getMaxSlot() { return max; }
	Potion* getPotion() { return PotionBag; }

	void addMoney(int money);
	void useMoney(int money);
	int getMoney() { return Money; }

	void setPotionBag();
	void setPotionBag(Potion* ptr) { this->PotionBag = ptr; }

	void ShowInventory(DBM& DB);
};
