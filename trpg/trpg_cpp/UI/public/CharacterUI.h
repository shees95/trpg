#pragma once
class Character;

class CharacterUI
{
public:
    static void Print_Buff_Info();
    static void Print_UseItem_menu();
    static void SelectItem(Character& chr, int min, int max);
	static void Print_Stat(Character& chr);
};
