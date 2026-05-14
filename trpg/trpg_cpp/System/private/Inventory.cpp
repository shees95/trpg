#include <vector>
#include "../public/Inventory.h"
#include "../public/ItemBase.h"

#include "../../Character/public/Character.h"

#include "../../UI/public/BaseUI.h"

#include <typeinfo>
#include "algorithm"

class Actor;

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
	BaseUI::Print("* Saved to inventory.\n");
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
	BaseUI::Print_ln("* Your bag has expanded.");
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
	BaseUI::Print_ln("[ Inventory (" + to_string(Inven.size()) + " / " + to_string(GetMaxSlot()) + ") ]");
	for (int i = 0; i < Inven.size(); i++)
	{
		BaseUI::Print_ln(to_string(i + 1) + ": " + Inven[i].GetItemInfo().ItemName + " [" + to_string(Inven[i].GetStack()) + "] (" + to_string(Inven[i].GetPrice() * Inven[i].GetStack()) + "G)");
	}
	
	BaseUI::Print_BorderLine_Single();
}
void Inventory::SortInventory()
{
	std::sort(Inven.begin(), Inven.end(), [](const ItemBase& a, const ItemBase& b)
	{
		return a.GetPrice() > b.GetPrice();
	});
}
