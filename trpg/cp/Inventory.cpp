//cpp trpg_cpp\Inventory.cpp
#include <vector>
#include "Inventory.h"
#include "Potion.h"
#include "TUI.h"
#include "DBM.h"

using namespace TUI;

Inventory::Inventory(Character* Owner)
{
	this->Owner = Owner;
	
}

void Inventory::addItem(string name)
{
	// keep previous user-visible behavior but reuse the template factory
	addImpl<GameItem>(name);

	// Inform user just like before
	if (Inven.size() > 0 && Inven.size() >= getMaxSlot() / 2) // no-op guard, message kept as original behavior
	{
		// original behavior printed expansion message inside add path; expansion already handled in addImpl
	}
	Print_ln("* Saved to inventory.");
}


void Inventory::sellItem(int index)
{
	//addMoney(Inven[index].price);
	if (index >= 0 && index < (int)Inven.size())
	{
		Inven.erase(Inven.begin() + index);
	}
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
	for (int i = 0; i < (int)Inven.size(); i++)
	{
		auto item = Inven[i];
		Print_ln(to_string(i + 1) + ": " + item->getName() + " (" + to_string(item->getValue(DB)) + "G)");
	}

	
	getPotion()->Print_Remain_Potion();

	Print_BorderLine_Single();
}


// ----- small function definitions that depend on DBM (keep in cpp) -----

int GameItem::getValue(DBM& db) const
{
	// defer to DBM using the stored name (keeps previous behavior)
	return db.GetItemValue(Name);
}

int PotionItem::getValue(DBM& db) const
{
	// If DBM has potion pricing keyed by label, use it; otherwise 0
	return db.GetItemValue(Label);
}