#include "../public/Monster.h"

#include "../public/Character.h"
#include "../public/CharacterStat.h"
#include "../../System/public/Inventory.h"

#include "../../System/public/MonsterBase.h"
#include "../../System/public/DBM.h"

#include "../../System/public/_TUI.h"
#include <cstdlib>

using namespace TUI;

Monster::Monster(const FMonster& NewMonster)
    : Character()
{
    CharacterStat& m_stat = GetStat();
    
    SetName(NewMonster.name);
    
    m_stat.SetMaxHP(NewMonster.hp);
    m_stat.SetHP(NewMonster.hp);
    m_stat.SetMaxMP(NewMonster.mp);
    m_stat.SetMP(NewMonster.mp);
    m_stat.SetAP(NewMonster.ap);
    m_stat.SetDP(NewMonster.dp);
    
    m_stat.SetLv(NewMonster.lv);
    var = NewMonster.var;
}

void Monster::SetVar(int var)
{
    this->var = var;
}

void Monster::CreateHP(int a, int b)
{
    GetStat().SetHP(GetRand(a, b));
}

void Monster::CreateMP(int a, int b)
{
    GetStat().SetMP(GetRand(a, b));
}

void Monster::CreateAP(int a, int b)
{
    GetStat().SetAP(GetRand(a, b));
}

void Monster::CreateDP(int a, int b)
{
    GetStat().SetDP(GetRand(a, b));
}

int Monster::GetRand(int a, int b)
{
    srand((unsigned)time(nullptr));
    int min = a, max = b;
    int random = rand() % (max - min + 1) + min;

    return random;
}

void Monster::Attack(Character& player)
{
    CharacterStat& pst = player.GetStat();
    CharacterStat& ost = GetStat();

    // 체력 적용
    int PushDamage = pst.GetHP() - max(ost.GetAP() - pst.GetDP(), 1);
    pst.SetHP(PushDamage);

    Print_HitLog(player, PushDamage);
}

void Monster::Print_HitLog(Character& Target, int PushDamage)
{
    Print_ln("* " + GetName() + " attacked " + Target.GetName() + "!! (" + to_string(PushDamage) + ")");
}