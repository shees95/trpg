#include <iostream>
#include <vector>

#include "System/public/Inventory.h"
#include "System/public/ItemBase.h"

#include "Character/public/Character.h"
#include "Character/public/CharacterStat.h"

#include "Character/public/Monster.h"

#include "System/public/DBM.h"
#include "System/public/PotionShop.h"

#include "UI/public/BaseUI.h"
#include "UI/public/BattleUI.h"
#include "UI/public/CharacterUI.h"
#include "UI/public/PotionShopUI.h"
#include "UI/public/SystemUI.h"

using namespace std;

int main()
{
    bool isGameStart = false;
    int selection = -1;

    // 변수화
    DBM DB_Manager;
    Character chr;
    PotionShop potionShop;

    // 로고 출력
    SystemUI::Print_Logo();



    // 캐릭터 생성

    // 플레이어 이름 설정, 스탯 설정
    chr.CreateCharacter();

    // 포션 입력
    chr.GetInventory().AddItems(DBM::GetItemFromName("HP Potion"), 5);
    chr.GetInventory().AddItems(DBM::GetItemFromName("MP Potion"), 5);
    
    // 스탯 출력
    CharacterUI::Print_Stat(chr);
    
        // 게임 시작
    SystemUI::Print_GameStart();

        // 클래스 선택
    SystemUI::Print_ChoiceJob(chr);

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
            selection = SystemUI::SelectVillageMenu(chr, position);
            
            // 게임 종료
            if (selection == 0)
            {
                isGameStart = false;
                break;
            }
            
        }
        // ==========================================
        
        // ------------------ 포션샵 ------------------
        if(position == 3)
        {
            SystemUI::Print_PosionShopMenu();
            SystemUI::SelectPotionShop(potionShop, chr, position);

        }
        // ==========================================
        
        // ------------------ 던전 고르기 ------------------ 
        if(position == 1) dungeon_lv = SystemUI::SelectDungeon(position);
        if (dungeon_lv == 0) position = 0;  // 마을로 귀환
        // ==========================================
        
        // ------------------ 던전 ------------------
        if(position == 2)
        {
            // 몬스터 생성
            
            string m_name = DBM::GetRandomMonsterKey(dungeon_lv);
            monster = new Monster(DBM::GetMonsterDB(m_name));
            
            // 전투 시작 UI
            BattleUI::Print_BattleStart(chr, *monster);
            
            // 전투 루프
            while (position == 2)
            {
                // 플레이어 턴
                
                selection = BattleUI::SelectPlayerTurn(chr, *monster, isGameStart);

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
                        BaseUI::Print("******* You Defeated *******");
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
                    BattleUI::Print_BattleVictory();

                    // 보상 생성
                    vector<string> drops = DB_Manager.GetDropItemFromName(m_name);
                    for (const string& itemName : drops)
                    {
                        BaseUI::Print_ln(" -> Got : " + itemName + "!");

                        // 보상 삽입
                        chr.GetInventory().AddItems(DB_Manager.GetItemFromName(itemName), 1);
                    }

                    BaseUI::Print_ln();
                    BaseUI::Print_BorderLine_Single();

                    // 경험치 + 렙업
                    chr.GetStat().AddExp(50);
                        // 레벨업 보상

                    BaseUI::Print_ln();

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
        
        

        
    }

}
