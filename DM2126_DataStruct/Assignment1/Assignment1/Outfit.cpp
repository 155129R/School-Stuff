#include "Outfit.h"



Outfit::~Outfit()
{
}

Outfit::Outfit(const string& outfitName, const int& initalDurability, const int& outfitSPECIALValue)
:Item(outfitName, initalDurability), kSPECIAL(outfitSPECIALValue)
{
    
}

const int Outfit::getSPECIAL()
{
   
    return this->kSPECIAL;
}

void Outfit::receiveDamage(const int& damageToItemDurability)
{
    Outfit::durability_ -= damageToItemDurability;
}