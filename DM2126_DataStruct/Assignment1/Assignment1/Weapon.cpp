#include "Weapon.h"
#include <assert.h>

Weapon::~Weapon()
{
}

Weapon::Weapon(const string& weaponName, const int& initialDurability_, const int& weaponDmg)
: kAttackDmg{ weaponDmg }, Item(weaponName, initialDurability_)
{

}
const int Weapon::getAttackDmg()
{
    return kAttackDmg;
}

void Weapon::receiveDamage(const int& damageToItemDurability)
{
    Weapon::durability_ -= damageToItemDurability;
    if (durability_ <= 0)
    {
        durability_ = 0;
    }
}

