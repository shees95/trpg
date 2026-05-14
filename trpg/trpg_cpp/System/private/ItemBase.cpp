#include "../public/ItemBase.h"
#include "../../Character/public/Character.h"
void ItemBase::Init(const ItemBase& NewItem)
{
    ItemInfo.ItemName = NewItem.ItemInfo.ItemName;
    ItemInfo.Price = NewItem.ItemInfo.Price;
    
    ItemInfo.Max_Stack = NewItem.ItemInfo.Max_Stack;
    
    ItemInfo.AddType = NewItem.ItemInfo.AddType;
    ItemInfo.AddValue = NewItem.ItemInfo.AddValue;
}

void ItemBase::Init(const FItemBase& NewItem)
{
    ItemInfo.ItemName = NewItem.ItemName;
    ItemInfo.Price = NewItem.Price;
    
    ItemInfo.Max_Stack = NewItem.Max_Stack;
    
    ItemInfo.AddType = NewItem.AddType;
    ItemInfo.AddValue = NewItem.AddValue;
}

void ItemBase::AddItem(const int& amount)
{
    Cur_Stack += amount;
}

void ItemBase::SubItem(const int& amount)
{
    Cur_Stack -= amount;
}

void ItemBase::UseItem(Character& User)
{
    
    if (ItemInfo.AddType != -1&& Cur_Stack > 0)
    {
        User.GetStat().Restore_Add(ItemInfo.AddType, ItemInfo.AddValue);
        SetStack(GetStack() - 1);
    }
}

void ItemBase::SetStack(const int& New_Stack)
{
    Cur_Stack = New_Stack;
}
