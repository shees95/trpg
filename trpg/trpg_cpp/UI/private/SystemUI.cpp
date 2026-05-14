#include "../../Character/public/Character.h"
#include "../../Character/public/Job.h"

#include "../public/CharacterUI.h"
#include "../public/SystemUI.h"
#include "../public/BaseUI.h"

#include "../../Character/public/Archer.h"
#include "../../Character/public/Magician.h"
#include "../../Character/public/Thief.h"
#include "../../Character/public/Warrior.h"

#include "../../System/public/PotionShop.h"

#include <iostream>


void SystemUI::Print_Logo()
{
    BaseUI::Print_BorderLine_Double();
    
    BaseUI::Print("\n\t");
    BaseUI::Print("[Dungeon Escape Text RPG]"); 
    BaseUI::Print("\n\t");
    
    BaseUI::Print_BorderLine_Double();
}

void SystemUI::Print_GameStart()
{

    BaseUI::Print_ln(3);
    BaseUI::Print_BorderLine_Double();

    BaseUI::Print("! GAME START !");

    BaseUI::Print_BorderLine_Double();
}



void SystemUI::Print_DropItem(const string& itemName)
{
    BaseUI::Print_ln(" >>> [GET] You got " + itemName + "!");
}

void SystemUI::Print_ChoiceJob(Character& chr)
{
    BaseUI::Print_BorderLine_Double();

    BaseUI::Print_ln("< Job Selection >");
    BaseUI::Print_ln("John, choose your job!");
    BaseUI::Print_ln("1. Warrior   2. Mage   3. Rogue   4. Archer");
    
    switch (int selection = BaseUI::Print_Choice_Number(1, 4))
    {
    case 1:
        chr.GetOwner().SetJob(new Warrior(chr.GetOwner()));
        break;
    
    case 2:
        chr.GetOwner().SetJob(new Magician(chr.GetOwner()));
        break;
    
    case 3:
        chr.GetOwner().SetJob(new Thief(chr.GetOwner()));
        break;
    case 4:
        chr.GetOwner().SetJob(new Archer(chr.GetOwner()));
        break;
    
    default:
        break;
    }
}


void SystemUI::Print_IdleMenu()
{

    BaseUI::Print_ln("=== Main Menu ===");

    BaseUI::Print_ln("1. Enter Dungeon");
    BaseUI::Print_ln("2. Check Inventory");
    BaseUI::Print_ln("3. Check Stat");
    BaseUI::Print_ln("4. Potion Shop");

    BaseUI::Print_ln("0. Quit");

    BaseUI::Print_BorderLine_Single();
}

void SystemUI::Print_PosionShopMenu()
{
    BaseUI::Print_ln("=== Potion Shop ===");
    BaseUI::Print_ln("1. Show all recipes");
    BaseUI::Print_ln("2. Search by potion name");
    BaseUI::Print_ln("3. Search by ingredient");
    BaseUI::Print_ln("4. Buy Potions");
    BaseUI::Print_ln("0. Go back");
}

void SystemUI::SelectPotionShop(PotionShop& potionShop, Character& chr, int& position)
{
    string input;
    switch (BaseUI::Print_Choice_Number(0, 4))
    {
    case 0:
        position = 0;
        break;

    case 1:
        potionShop.ShowAllRecipes();
        break;

    case 2:
        BaseUI::Print("Search Potion name : ");
        cin >> input;
        potionShop.SearchByName(input, true);
        break;

    case 3:
        BaseUI::Print("Search Ingredient name : ");
        cin >> input;
        potionShop.SearchByIngredient(input, true);
        break;
    case 4:
        potionShop.ShowShopBuyUI(chr);
        break;
    }
}

int SystemUI::SelectVillageMenu(Character& chr, int& position)
{
    int selection = -1;

    while (true)
    {
        Print_IdleMenu();

        switch (selection = BaseUI::Print_Choice_Number(0, 4))
        {
        case 0:
            // 종료
            position = 0;
            return selection;

        case 1:
            // 던전 입장
            position = 1;
            return selection;

        case 2:
            // 인벤 체크
            chr.GetInventory().ShowInventory();
            break;

        case 3:
            // 스텟 체크
            CharacterUI::Print_Stat(chr);
            break;

        case 4:
            // 포션샵
            position = 3;
            return selection;

        }
    }
    
}

int SystemUI::SelectDungeon(int& position)
{
    while (true)
    {
        BaseUI::Print_ln("Select Dungeon Level");
        
        BaseUI::Print_ln("1. Easy");
        BaseUI::Print_ln("2. Normal");
        BaseUI::Print_ln("3. Hard");
        BaseUI::Print_ln("4. Boss");
        BaseUI::Print_ln("0. Go Back");
        position = 2;
        return BaseUI::Print_Choice_Number(0,4);
    }
    
}