#include "Monster.h"

#include "Character.h"
#include "CharacterStat.h"
#include "Inventory.h"

#include "DBM.h"

#include "TUI.h"
#include <cstdlib>

using namespace TUI;

Monster::Monster(string name, MonsterDB m_db)
{
    setName(name);

    getStat().setMaxHP(m_db.getHP());
    getStat().setHP(m_db.getHP());
    getStat().setMaxMP(m_db.getMP());
    getStat().setMP(m_db.getMP());
    getStat().setAP(m_db.getAP());
    getStat().setDP(m_db.getDP());
             
    getStat().setLv(m_db.getLv());
    setVar(m_db.getVar());

    getStat().setDP(m_db.getDP());
}

void Monster::createHP(int a, int b)
{
    getStat().setHP(getRand(a, b));
}

void Monster::createMP(int a, int b)
{
    getStat().setMP(getRand(a, b));
}

void Monster::createAP(int a, int b)
{
    getStat().setAP(getRand(a, b));
}

void Monster::createDP(int a, int b)
{
    getStat().setDP(getRand(a, b));
}

int Monster::getRand(int a, int b)
{
    srand((unsigned)time(nullptr));
    int min = a, max = b;
    int random = rand() % (max - min + 1) + min;

    return random;
}

void Monster::Attack(Character& player)
{
    CharacterStat pst = player.getStat();
    CharacterStat ost = getStat();

    // 체력 적용
    int PushDamage = pst.getHP() - max(ost.getAP() - pst.getDP(), 1);
    pst.setHP(PushDamage);

    Print_HitLog(player, PushDamage);
}

void Monster::Print_HitLog(Character& Target, int PushDamage)
{
    Print_ln("* " + getName() + " attacked " + Target.getName() + "!! (" + to_string(PushDamage) + ")");
}