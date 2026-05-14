#include "../../Character/public/Character.h"
#include "../../Character/public/Job.h"
#include "../../UI/public/CharacterUI.h"
#include "../public/BattleUI.h"
#include "../public/BaseUI.h"
#include "../public/SystemUI.h"

void BattleUI::Print_BattleStart(Character& player, Character& monster)
{
    BaseUI::Print_BorderLine_Double();
    
    BaseUI::Print("[Battle Start!]\t" + player.GetName() + "(" + player.GetJob()->GetJobName() + ") vs " + monster.GetName());
    BaseUI::Print_ln(2);
    
    BaseUI::Wait_AnyKey();
}

void BattleUI::Print_PlayerTurn_Select()
{
    BaseUI::Print_ln("---- Player Turn ----");

    BaseUI::Print_t("1. Attack");
    BaseUI::Print_t("2. Use Item");
    BaseUI::Print_t("3. Show Your Stat");
    BaseUI::Print_t("4. Show Monster Stat");
    BaseUI::Print_ln("0. Run");

}

void BattleUI::Print_BattleVictory()
{
    BaseUI::Print_ln("★ Victory!");
}

void BattleUI::Print_BattleLose()
{
    BaseUI::Print_ln("* You Lose");
}

int BattleUI::SelectPlayerTurn(Character& chr, Character& monster, bool& isGameStart)
{
    int selection = -1;

    while (true)
    {
        Print_PlayerTurn_Select();

        switch (selection = BaseUI::Print_Choice_Number(0, 4))
        {
        case 0:
            Print_BattleLose();
            return selection;

        case 1:
            chr.GetJob()->Attack(monster);
            return selection;

        case 2:
            CharacterUI::SelectItem(chr, 0, 1);
            return selection;

        case 3:
            CharacterUI::Print_Stat(chr);
            break;
            
        case 4:
            CharacterUI::Print_Stat(monster);
            break;

        }
    }
    

    return selection;
}

