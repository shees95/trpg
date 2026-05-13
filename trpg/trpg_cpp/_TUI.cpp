#include <iostream>
#include <string>

#include "TUI.h"

#include "Character.h"
#include "CharacterStat.h"
#include "Potion.h"
#include "Inventory.h"
#include "Job.h"


#include "Monster.h"

using namespace std;

void TUI::Print_BorderLine_Single()
{
    cout << "\n-------------------------------------------\n";
}

void TUI::Print_BorderLine_Double()
{
    cout << "\n===========================================\n";
}

void TUI::Print_t(int repeat)
{
    for(int i = 0; i < repeat; i++) cout << "\t";
}
void TUI::Print_ln(int repeat)
{
    for (int i = 0; i < repeat; i++) cout << "\n";
}

void TUI::Print_t(string text)
{
    cout << text << "\t";
}
void TUI::Print_ln(string text)
{
    cout << text << "\n";
}

void TUI::Print(string text)
{
    cout << text;
}

void TUI::Print_Logo()
{
    Print_BorderLine_Double();

    Print_ln();
    Print_t(); Print("[Dungeon Escape Text RPG]"); Print_t();
    Print_ln();

    Print_BorderLine_Double();
}

void TUI::Print_Buff_Info()
{
    int index = -1;

    Print_BorderLine_Double();
    
    Print_ln("< Character Buff >");
    Print_t("1. HP UP");
    Print_t("2. MP UP");
    Print_ln("3. AP x2");

    Print_t("4. DP x2");
    Print_t("5. Current Stat");

    Print_ln("0. GameStart");
    

    Print_BorderLine_Single();
}

int TUI::Print_Choice_Number(int min, int max)
{
    int input = -1;


    while (true)
    {
        input = -1;
        Print("Select Number : ");
        cin >> input;

        if (input >= min && input <= max) break;
    }
    

    Print_ln();
    Print_BorderLine_Single();

    return input;
}

void TUI::Print_Choice_Job()
{
    Print_BorderLine_Double();

    Print_ln("< Job Selection >");
    Print_ln("John, choose your job!");
    Print_ln("1. Warrior   2. Mage   3. Rogue   4. Archer");
    
}

void TUI::Print_GameStart()
{

    Print_ln(3);
    Print_BorderLine_Double();

    Print("! GAME START !");

    Print_BorderLine_Double();
    Print_ln(4);
}

void TUI::Print_BattleStart(Character& player, Character& monster)
{
    Print_BorderLine_Double();

    Print("[Battle Start!]\t" + player.getName() + "(" + player.getJob()->getJobName() + ") vs " + monster.getName());
    Print_ln(2);

}

void TUI::Print_PlayerTurn_Select()
{
    Print_ln("---- Player Turn ----");

    Print_t("1. Attack");
    Print_t("2. Use Item");
    Print_t("3. Show Monster Stat");
    Print_ln("0. Run");

}

void TUI::Print_UseItem_menu(Inventory& inventory)
{
    Print_ln("0. Go Back");
    inventory.getPotion()->Print_Remain_Potion();
    
}
void TUI::Print_BattleVictory()
{
    Print_ln("★ Victory!");
}

void TUI::Print_BattleLose()
{
    Print_ln("* You Lose");
}

void TUI::Print_DropItem(DropItem* target)
{

}

void TUI::Print_IdleMenu()
{

    Print_ln("=== Main Menu ===");

    Print_ln("1. Enter Dungeon");
    Print_ln("2. Check Inventory");
    Print_ln("3. Check Stat");
    Print_ln("4. Potion Shop");

    Print_ln("0. Quit");

    Print_BorderLine_Single();
}

void TUI::Print_PosionShopMenu()
{
    Print_ln("=== Potion Shop ===");
    Print_ln("1. Show all recipes");
    Print_ln("2. Search by potion name");
    Print_ln("3. Search by ingredient");
    Print_ln("0. Go back");
}

