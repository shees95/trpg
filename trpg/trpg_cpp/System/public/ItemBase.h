#pragma once
#include <process.h>
#include <string>

// #include "../../Character/public/Character.h"
class Character;
class Actor;
using namespace std;

class Character;

struct FItemBase
{
    string ItemName;
    int Price;
    
    int Max_Stack = 10;
    
    int AddType = -1;
    int AddValue = 0;
};

class ItemBase
{
private:
    FItemBase ItemInfo;
    int Cur_Stack = 0;
    
public:
    
    void Init(const ItemBase& NewItem);
    void Init(const FItemBase& NewItem);
    
    void AddItem(const int& amount);
    void SubItem(const int& amount);
    virtual void UseItem(Character& User);
    const FItemBase& GetItemInfo() { return ItemInfo; }
    
    const int& GetStack() const { return Cur_Stack; }
    
    const string& GetItemName() const { return ItemInfo.ItemName; }
    const int& GetPrice() const { return ItemInfo.Price; }
    const int& GetMaxStack() const { return ItemInfo.Max_Stack; }
    const int& GetAddType() const { return ItemInfo.AddType; }
    const int& GetAddValue() const { return ItemInfo.AddValue; }
    
    void SetStack(const int& New_Stack);
};
