#include <iostream>
#include <vector>

#include "Character/public/Character.h"
#include "Character/public/CharacterStat.h"
#include "System/public/Inventory.h"
#include "System/public/ItemBase.h"

#include "Character/public/Archer.h"
#include "Character/public/Magician.h"
#include "Character/public/Thief.h"
#include "Character/public/Warrior.h"

#include "Character/public/Monster.h"
#include "System/public/DBM.h"
#include "System/public/PotionShop.h"

#include "System/public/_TUI.h"

using namespace std;
using namespace TUI;

int selectPlayerTurn(Character& chr, Character& monster, bool& isGameStart);
int selectIdleMenu(Character& chr, int& position, int& dungeon_lv, DBM& DB_Manager);
int selectDungeon(int& position);
void SelectItem(Character& chr, int min, int max);

int main()
{
    bool isGameStart = false;
    int selection = -1;

    // 변수화
    Character chr;

    DBM DB_Manager;
    PotionShop potionShop;

        // 로고 출력
    Print_Logo();



        // 캐릭터 생성

    // 플레이어 이름 설정
    chr.CreateName();

    // 스탯 입력
    chr.GetStat().Init_HPMP();
    chr.GetStat().Init_APDP();

    // 포션 입력
    chr.GetInventory().AddItems(DB_Manager.GetItemFromName("HP Potion"), 5);
    chr.GetInventory().AddItems(DB_Manager.GetItemFromName("MP Potion"), 5);
    
    // 스탯 출력
    chr.GetStat().Print_Stat();
    
        // 게임 시작
    Print_GameStart();

        // 클래스 선택
    Print_Choice_Job();

    switch (int selection = Print_Choice_Number(1, 4))
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


    isGameStart = true;

    // 메인 게임 루프
    int position = 0;   // 0 : idle, 1 : dungeon, 2 : battle, 3 : position shop
    int dungeon_lv = 1;
    Monster* monster;
    string input = "";
    while (isGameStart)
    {


        // ------------------ 마을 ------------------
        if (position == 0)
        {
            // 던전 선택 시, isBattleStart = true;
            selection = selectIdleMenu(chr, position, dungeon_lv, DB_Manager);
            
            // 게임 종료
            if (selection == 0)
            {
                isGameStart = false;
                break;
            }
            
            
        }
        // ==========================================
        
        
        
        // ------------------ 던전 고르기 ------------------ 
        if(position == 1) dungeon_lv = selectDungeon(position);
        if (dungeon_lv == 0) position = 0;  // 마을로 귀환
        // ==========================================
        


        // ------------------ 던전 ------------------
        if(position == 2)
        {
            // 몬스터 생성
            
            string m_name = DB_Manager.GetRandomMonsterKey(dungeon_lv);
            monster = new Monster(DB_Manager.GetMonsterDB(m_name));
            
            // 전투 시작 UI
            Print_BattleStart(chr, *monster);
            
            // 전투 루프
            while (position == 2)
            {
                // 플레이어 턴
                
                selection = selectPlayerTurn(chr, *monster, isGameStart);

                // 플레이어 도망
                if (selection == 0)
                {
                    position = 0;

                    delete monster;
                    monster = nullptr;

                    break;
                }

                // 몬스터 턴
                // 몬스터 생존 체크
                if (monster->GetStat().GetHP() > 0)
                {
                    monster->Attack(chr);
    
                    // 플레이어 패배
                    if (chr.GetStat().GetHP() <= 0)
                    {
                        Print("******* You Defeated *******");
                        position = 0;
                        isGameStart = false;
                        
                        delete monster;
                        monster = nullptr;

                        break;
                    }
                }
                else
                {

                    // 플레이어 승리 UI
                    Print_BattleVictory();

                    // 보상 생성
                    vector<string> drops = DB_Manager.GetDropItemFromName(m_name);
                    for (const string& itemName : drops)
                    {
                        Print_ln(" -> Got : " + itemName + "!");

                        // 보상 삽입
                        chr.GetInventory().AddItems(DB_Manager.GetItemFromName(itemName), 1);
                    }

                    Print_ln();
                    Print_BorderLine_Single();

                    // 경험치 + 렙업
                    chr.GetStat().AddExp(50);
                        // 레벨업 보상

                    Print_ln();

                    // 마을
                    position = 0;

                    delete monster;
                    monster = nullptr;

                    break;
                }
            }
            
            //  비 전투 시 항상 포인터 해제
            if (monster != nullptr)
            {
                delete monster;
                monster = nullptr;
            }
        }
        
        

        // ------------------ 포션샵 ------------------
        if(position == 3)
        {
            Print_PosionShopMenu();
            switch (Print_Choice_Number(0, 3))
            {
            case 0:
                position = 0;
                break;

            case 1:
                potionShop.ShowAllRecipes();
                break;

            case 2:
                Print("Search Potion name : ");
                cin >> input;
                potionShop.SearchByName(input, true);
                break;

            case 3:
                Print("Search Ingredient name : ");
                cin >> input;
                potionShop.SearchByIngredient(input, true);
                break;
            }

        }
    }

}

int selectPlayerTurn(Character& chr, Character& monster, bool& isGameStart)
{

    int selection = -1;

    while (true)
    {
        Print_PlayerTurn_Select();

        switch (selection = Print_Choice_Number(0, 3))
        {
        case 0:
            Print_BattleLose();
            return selection;

        case 1:
            chr.GetJob()->Attack(monster);
            return selection;

        case 2:
            SelectItem(chr, 0, 1);
            return selection;

        case 3:
            monster.GetStat().Print_Stat();
            break;

        }
    }
    

    return selection;
}

int selectIdleMenu(Character& chr, int& position, int& dungeon_lv, DBM& DB_Manager)
{
    int selection = -1;

    while (true)
    {
        Print_IdleMenu();

        switch (selection = Print_Choice_Number(0, 4))
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
            chr.GetStat().Print_Stat();
            break;

        case 4:
            // 포션샵
            position = 3;
            return selection;

        }
    }
    
}

int selectDungeon(int& position)
{
    while (true)
    {
        Print_ln("Select Dungeon Level");

        Print_ln("1. Easy");
        Print_ln("2. Normal");
        Print_ln("3. Hard");
        Print_ln("4. Boss");
        Print_ln("0. Go Back");
        position = 2;
        return Print_Choice_Number(0,4);
    }
    
}

void SelectItem(Character& chr, int min, int max)
{
    int index = 0;
    while (true)
    {
        chr.GetStat().Print_Stat();
        Print_UseItem_menu();
        chr.GetInventory().ShowInventory();
        
        Print("Select Use Item : ");
        cin >> index;
        
        if (index == 0) return;

        // 인벤토리 인덱스 검사 (1-based 입력 대응)
        index -= 1; 
        if (index >= 0 && index < chr.GetInventory().GetMaxSlot())
        {
            chr.GetInventory().UseItem(index);
            break;
        }

    }
}
// main test