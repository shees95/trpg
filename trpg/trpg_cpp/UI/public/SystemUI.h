#pragma once
class Character;
class PotionShop;

class SystemUI
{
public:
     
    static void Print_Logo();
    static void Print_GameStart();
    
    static void Print_IdleMenu();
    static int SelectVillageMenu(Character& chr, int& position);
    
    static void Print_PosionShopMenu();
    static void SelectPotionShop(PotionShop& PotionShop, Character& chr, int& position);
    
    static int SelectDungeon(int& position);
    
    static void Print_DropItem(const string& itemName);
    
    static void Print_ChoiceJob(Character& chr);
    //static  void SelectItem(Character& chr, int min, int max);
};
