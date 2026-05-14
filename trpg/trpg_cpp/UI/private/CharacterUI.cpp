#include "../public/CharacterUI.h"
#include "../../Character/public/Character.h"
#include "../public/BaseUI.h"

void CharacterUI::Print_Buff_Info()
{
    int index = -1;

    BaseUI::Print_BorderLine_Double();
    
    BaseUI::Print_ln("< Character Buff >");
    BaseUI::Print_t("1. HP UP");
    BaseUI::Print_t("2. MP UP");
    BaseUI::Print_ln("3. AP x2");

    BaseUI::Print_t("4. DP x2");
    BaseUI::Print_t("5. Current Stat");

    BaseUI::Print_ln("0. GameStart");
    

    BaseUI::Print_BorderLine_Single();
}



void CharacterUI::Print_UseItem_menu()
{
    BaseUI::Print_ln("0. Go Back");
    
    
}

void CharacterUI::SelectItem(Character& chr, int min, int max)
{
    int index = 0;
    while (true)
    {
        CharacterUI::Print_Stat(chr);
        CharacterUI::Print_UseItem_menu();
        chr.GetInventory().ShowInventory();
        
        BaseUI::Print("Select Use Item : ");
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


void CharacterUI::Print_Stat(Character& chr)
{
    CharacterStat Stat = chr.GetStat();

    BaseUI::Print_BorderLine_Double();

    BaseUI::Print_ln(); 
	
    BaseUI::Print_t();  BaseUI::Print_t("Lv. " + to_string(chr.GetStat().GetLv()));   BaseUI::Print_t(chr.GetName() + "'s Stats");
    BaseUI::Print("(Exp: " + to_string(chr.GetStat().GetExp()) + "/" + to_string(chr.GetStat().GetMaxExp()) + ")");

    BaseUI::Print_ln();
    BaseUI::Print_BorderLine_Single();

    BaseUI::Print_t("HP: " + to_string(Stat.GetHP()) + " / " + to_string(Stat.GetMaxHP()));
							   									 
    BaseUI::Print_t("MP: " + to_string(Stat.GetMP()) + " / " + to_string(Stat.GetMaxMP()));
    BaseUI::Print_ln();					   
						   
    BaseUI::Print_t("AP: " + to_string(Stat.GetAP()));
					   
    BaseUI::Print_t("DP: " + to_string(Stat.GetDP()));
    BaseUI::Print_BorderLine_Double();
}