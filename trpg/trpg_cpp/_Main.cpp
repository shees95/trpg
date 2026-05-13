#include <iostream>
#include <vector>

#include "Character.h"
#include "CharacterStat.h"
#include "Potion.h"
#include "Inventory.h"

#include "Archer.h"
#include "Magician.h"
#include "Thief.h"
#include "Warrior.h"

#include "Monster.h"
#include "DBM.h"
#include "PotionShop.h"

#include "TUI.h"

using namespace std;
using namespace TUI;

int selectBuff(Character& chr);
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
    chr.createName();

    // 스탯 입력
    chr.getStat().Init_HPMP();
    chr.getStat().Init_APDP();

    // 포션 입력
    chr.getInventory().setPotionBag();

    // 스탯 출력
    chr.getStat().Print_Stat();
     /*
    // 버프 정보
    while (!isGameStart)
    {
        Print_Buff_Info();

        if (selectBuff(chr) == 0) isGameStart = true;

        Print_BorderLine_Double();
    }
    */

        // 게임 시작
    Print_GameStart();

        // 클래스 선택
    Print_Choice_Job();

    switch (int selection = Print_Choice_Number(1, 4))
    {
    case 1:
        chr.getOwner().setJob(new Warrior(chr.getOwner()));
        break;
    
    case 2:
        chr.getOwner().setJob(new Magician(chr.getOwner()));
        break;
    
    case 3:
        chr.getOwner().setJob(new Thief(chr.getOwner()));
        break;
    case 4:
        chr.getOwner().setJob(new Archer(chr.getOwner()));
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
            monster = new Monster(m_name, DB_Manager.GetMonsterDB(m_name));

            // 전투 시작 UI
            Print_BattleStart(chr, *monster);

            // 전투 루프
            while (position == 2)
            {
                // 플레이어 턴
                
                selection = selectPlayerTurn(chr, *monster, isGameStart);

                // 도망 시, 배틀 종료
                if (selection == 0)
                {
                    position = 0;

                    delete monster;
                    monster = nullptr;

                    break;
                }

                // 몬스터 턴
                // 몬스터 생존 체크
                if (monster->getStat().getHP() > 0)
                {
                    monster->Attack(chr);

                    if (chr.getStat().getHP() <= 0)
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

                    // 승리 UI
                    Print_BattleVictory();

                    // 보상 생성
                    vector<string> drops = DB_Manager.GetDropItemKeys(m_name);
                    for (const string& itemName : drops)
                    {
                        Print_ln(" -> Got : " + itemName + "!");

                        // 보상 삽입
                        chr.getInventory().addItem(itemName);
                    }

                    Print_ln();
                    Print_BorderLine_Single();

                    // 경험치 + 렙업
                    chr.getStat().addExp(50);
                        // 레벨업 보상

                    Print_ln();

                    // 마을
                    position = 0;

                    delete monster;
                    monster = nullptr;

                    break;
                }
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

int selectBuff(Character& chr)
{
    CharacterStat chrSt = chr.getStat();
    Potion* chrPt = chr.getInventory().getPotion();

    int selection = -1;
    switch (selection = Print_Choice_Number(0, 5))
    {
    case 0:
        return selection;

    case 1:
        if (!chrPt->Use_HP_Potion()) break;

        chrSt.Buff_Add(0, 20);
        chrPt->Print_Remain_HP_Potion();
        return selection;

    case 2:
        if (!chrPt->Use_MP_Potion()) break;

        chrSt.Buff_Add(1, 20);
        chrPt->Print_Remain_MP_Potion();
        return selection;

    case 3:
        chrSt.Buff_Mul(2, 2);
        return selection;

    case 4:
        chrSt.Buff_Mul(3, 2);
        return selection;

    case 5:
        chrSt.Print_Stat();
        return selection;
        
    default:
        break;
    }

    return selection;
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
            chr.getJob()->Attack(monster);
            return selection;

        case 2:
            SelectItem(chr, 0, 1);
            return selection;

            Print_BorderLine_Double();

            break;

        case 3:
            monster.getStat().Print_Stat();
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
            chr.getInventory().ShowInventory(DB_Manager);
            break;

        case 3:
            // 스텟 체크
            chr.getStat().Print_Stat();
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
        chr.getStat().Print_Stat();
        Print_UseItem_menu(chr.getInventory());

        Print("Select Use Item : ");
        cin >> index;

        switch (index)
        {
        case 0:
            return;
        case 1:
            chr.getStat().Print_Stat();
            chr.getInventory().getPotion()->Use_HP_Potion();
            chr.getStat().addHP(20);
            break;
        case 2:
            chr.getStat().Print_Stat();
            chr.getInventory().getPotion()->Use_MP_Potion();
            chr.getStat().addMP(20);
            break;
        }

    }
}
// main test