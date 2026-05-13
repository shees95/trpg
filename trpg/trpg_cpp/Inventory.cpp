#include <vector>
#include "Inventory.h"
#include "Potion.h"
#include "TUI.h"
#include "DBM.h"

using namespace TUI;

Inventory::Inventory(Character* Owner)
{
	this->Owner = Owner;
	this->PotionBag = nullptr;
}


void Inventory::addItem(const string& name)
{
	if (Inven.size() >= getMaxSlot())
	{
		expandSlot(getMaxSlot() * 2);
		Print_ln("* Your bag has expanded.");
	}

	Inven.push_back(name);
	Print_ln("* Saved to inventory.");
}


void Inventory::sellItem(const int& index)
{
	//addMoney(Inven[index].price);
	Inven.erase(Inven.begin() + index);

}


void Inventory::expandSlot(int index)
{
	setMaxSlot(index);
}

void Inventory::setMaxSlot(int max)
{
	this->max = max;
	Inven.reserve(max);
}

void Inventory::setPotionBag()
{
	this->PotionBag = new Potion(Owner);
}

void Inventory::addMoney(int Money)
{
	this->Money += Money;
}

void Inventory::useMoney(int Money)
{
	this->Money -= Money;
}

void Inventory::ShowInventory(DBM& DB)
{
	Print_ln("[ Inventory (" + to_string(Inven.size()) + " / " + to_string(getMaxSlot()) + ") ]");
	for (int i = 0; i < Inven.size(); i++)
	{
		Print_ln(to_string(i + 1) + ": " + Inven[i] + " (" + to_string(DB.GetItemValue(Inven[i])) + "G)");
	}

	
	getPotion()->Print_Remain_Potion();

	Print_BorderLine_Single();
}
