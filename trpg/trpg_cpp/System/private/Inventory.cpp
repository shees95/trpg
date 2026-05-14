#include <vector>
#include "../public/Inventory.h"
#include "../public/DBM.h"
#include "../public/_TUI.h"
#include "../public/ItemBase.h"
#include "../../Character/public/Character.h"
#include <typeinfo>
#include "algorithm"

class Actor;

using namespace TUI;

Inventory::Inventory(Actor* Owner)
{
	this->Owner = Owner;
}


void Inventory::AddItem(const FItemBase& NewItem)
{
	
	if (Inven.size() >= GetMaxSlot())
	{
		ExpandSlot(GetMaxSlot() * 2);
	}
	
	bool isExists = false;
	for (int i = 0; i < Inven.size(); i++)
	{
		if (Inven[i].GetItemInfo().ItemName == NewItem.ItemName && Inven[i].GetStack() < Inven[i].GetMaxStack())
		{
			isExists = true;
			Inven[i].AddItem(1);
			break;
		}
	}
	
	if (!isExists)
	{
		ItemBase InsertInventoryItem;
		InsertInventoryItem.Init(NewItem);
		InsertInventoryItem.AddItem(1);
		Inven.push_back(InsertInventoryItem);
		
	}
	
	
}

void Inventory::AddItems(const FItemBase& Item, int stack)
{
	for (int i=0;i<stack;i++)
	{
		AddItem(Item);
	}
	SortInventory();
	Print_ln("* Saved to inventory.");
}

void Inventory::UseItem(const int& index)
{
	if (index < 0 || index >= (int)Inven.size()) 
	{
		std::cout << "Invalid Index!" << std::endl;
		return;
	}

	Character* _Owner = (Character*)Owner; // 순환 참조 주의
	
	if (_Owner != nullptr)
	{
		Inven[index].UseItem(*_Owner);
		if (Inven[index].GetStack() <= 0)
		{
			Inven.erase(Inven.begin() + index);
		}
	}
	
}


void Inventory::SellItem(const int& index)
{
	AddMoney(Inven[index].GetItemInfo().Price * Inven[index].GetStack());
	Inven.erase(Inven.begin() + index);
}


void Inventory::ExpandSlot(const int& index)
{
	SetMaxSlot(index);
	Print_ln("* Your bag has expanded.");
}

void Inventory::SetMaxSlot(const int& max)
{
	this->max = max;
	Inven.reserve(max);
}

void Inventory::AddMoney(const int& Money)
{
	this->Money += Money;
}

void Inventory::UseMoney(const int& Money)
{
	this->Money -= Money;
}

void Inventory::ShowInventory()
{
	Print_ln("[ Inventory (" + to_string(Inven.size()) + " / " + to_string(GetMaxSlot()) + ") ]");
	for (int i = 0; i < Inven.size(); i++)
	{
		Print_ln(to_string(i + 1) + ": " + Inven[i].GetItemInfo().ItemName + " [" + to_string(Inven[i].GetStack()) + "] (" + to_string(Inven[i].GetPrice() * Inven[i].GetStack()) + "G)");
	}
	
	Print_BorderLine_Single();
}
void Inventory::SortInventory()
{
	std::sort(Inven.begin(), Inven.end(), [](const ItemBase& a, const ItemBase& b)
	{
		return a.GetPrice() > b.GetPrice();
	});
}
