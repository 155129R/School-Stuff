#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class Weapon :
    public Item
{
public:


    Weapon(const string& weaponName = "", const int& initialDurability_ = 0, const int& weaponDmg = 0); //[CONSTRUCTOR](Override) Intialize instance of Weapon class and instantiate member and take in name of weapon, initial Durability and weapon damage

    virtual ~Weapon();

    const int getAttackDmg();

    void receiveDamage(const int& damageToItemDurability); //Apply Damage to weapon's durability

private:
    const int kAttackDmg;
};

#endif /*WEAPON_H*/