#pragma once
#include <string>

class Character;
class Monster;
class DropItem;
class Potion;
class Inventory;
using namespace std;

namespace TUI
{
	void Print_BorderLine_Single();
	void Print_BorderLine_Double();

	void Print_t(int repeat = 1);
	void Print_ln(int repeat = 1);

	void Print_t(string text);
	void Print_ln(string text);

	void Print(string text);

	void Print_Logo();

	void Print_Buff_Info();
	int Print_Choice_Number(int min, int max);

	void Print_Choice_Job();

	void Print_GameStart();
	
	void Wait_AnyKey();
	
	void Print_BattleStart(Character& player, Character& monster);
	void Print_PlayerTurn_Select();

	void Print_UseItem_menu();
	
	void Print_BattleVictory();
	void Print_BattleLose();

	void Print_DropItem(const string& itemName);
	
	void Print_IdleMenu();

	void Print_PosionShopMenu();
}
