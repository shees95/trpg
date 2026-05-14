#pragma once
#include <string>
class Character;
using namespace std;

class BattleUI
{
public:
    
    static void Print_BattleStart(Character& player, Character& monster);
    
    static void Print_PlayerTurn_Select();
    
    static void Print_BattleVictory();
    static void Print_BattleLose();
    
    static int SelectPlayerTurn(Character& chr, Character& monster, bool& isGameStart);
    
};
