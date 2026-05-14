#include <iostream>
#include <string>


#include "../../Character/public/Character.h"
#include "../../Character/public/CharacterStat.h"
#include "../../Character/public/Job.h"
#include "../../Character/public/Monster.h"

#include "../../System/public/Inventory.h"

#include "../../System/public/_TUI.h"


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
    int input;
    while (true)
    {
        Print("Select Number : ");
        if (!(cin >> input)) // 숫자가 아닌 값이 들어오면 false 반환
        {
            cin.clear(); // 에러 플래그 초기화
            cin.ignore(256, '\n'); // 버퍼 비우기
            Print_ln("! Invalid input. Please enter a number.");
            continue;
        }

        if (input >= min && input <= max) break;
        
        Print_ln("! Out of range. Try again.");
    }

    Print_ln();
    Print_BorderLine_Single();
    return input;
}

void TUI::Wait_AnyKey()
{
    Print("\nPress Enter to continue...");
    cin.ignore(256, '\n'); // 이전 입력의 잔여물 제거
    cin.get(); // 엔터 입력 대기
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
    
    Print("[Battle Start!]\t" + player.GetName() + "(" + player.GetJob()->GetJobName() + ") vs " + monster.GetName());
    Print_ln(2);
    
    Wait_AnyKey();
}

void TUI::Print_PlayerTurn_Select()
{
    Print_ln("---- Player Turn ----");

    Print_t("1. Attack");
    Print_t("2. Use Item");
    Print_t("3. Show Monster Stat");
    Print_ln("0. Run");

}

void TUI::Print_UseItem_menu()
{
    Print_ln("0. Go Back");
    
    
}
void TUI::Print_BattleVictory()
{
    Print_ln("★ Victory!");
}

void TUI::Print_BattleLose()
{
    Print_ln("* You Lose");
}

void TUI::Print_DropItem(const string& itemName)
{
    Print_ln(" >>> [획득] " + itemName + "을(를) 얻었습니다!");
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

