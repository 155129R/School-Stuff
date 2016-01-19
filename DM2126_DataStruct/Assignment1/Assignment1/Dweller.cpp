#include "Dweller.h"

Dweller::~Dweller()
{
}

Dweller::Dweller(const string& dwellerName, const int& assignedSPECIAL_)
:GameObject(dwellerName), position_(Vec2D(0, 0)), health_(100), weapon_(nullptr), radiation_(0), stimpak_(0), radaway_(0), outfit_(nullptr)
{
    SPECIAL_ = assignedSPECIAL_;
}

const int Dweller::getSPECIAL()
{
  
        int S, P, E, C, I, A, L;

        if ((outfit_ != NULL) && (outfit_->getDurability() > 0))
        {
    
            S = (this->SPECIAL_ / 1000000) + (outfit_->getSPECIAL() / 1000000);
            P = (this->SPECIAL_ / 100000 % 10) + (outfit_->getSPECIAL() / 100000 % 10);
            E = (this->SPECIAL_ / 10000 % 10) + (outfit_->getSPECIAL() / 10000 % 10);
            C = (this->SPECIAL_ / 1000 % 10) + (outfit_->getSPECIAL() / 1000 % 10);
            I = (this->SPECIAL_ / 100 % 10) + (outfit_->getSPECIAL() / 100 % 10);
            A = (this->SPECIAL_ / 10 % 10) + (outfit_->getSPECIAL() / 10 % 10);
            L = (this->SPECIAL_ % 10) + (outfit_->getSPECIAL() % 10);
        }
        else return SPECIAL_;

        if (S > 9)
        {
            S = 9;
        }

        if (P > 9)
        {
            P = 9;
        }
        if (E > 9)
        {
            E = 9;
        }
        if (C > 9)
        {
            C = 9;
        }
        if (I > 9)
        {
            I = 9;
        }
        if (A > 9)
        {
            A = 9;
        }
        if (L > 9)
        {
            L = 9;
        }

        const int newSPECIAL = S * 1000000 + P * 100000 + E * 10000 + C * 1000 + I * 100 + A * 10 + L;

        return newSPECIAL;
    
    
}

const int Dweller::getCurrentHealth()
{
    return health_;
}

const int Dweller::getCurrentRadDamage()
{
    return radiation_;
}

const int Dweller::getAttackDmg()
{
    if (weapon_ != NULL)
        return weapon_->getAttackDmg();
}

void Dweller::setPosition(const Vec2D& newPosition)
{
    position_ = newPosition;
}

const Vec2D Dweller::getPosition(void)
{
    return position_;
}

void Dweller::receiveRadDamage(const int& radiationDamageTaken)
{
    radiation_ -= radiationDamageTaken;
}

void Dweller::receiveEquipmentDamage(const int& damageToDurability)
{
    if (outfit_ != NULL)
        outfit_->receiveDamage(damageToDurability);
    if (weapon_ != NULL)
        weapon_->receiveDamage(static_cast<const int>(damageToDurability * 0.5));
}

void Dweller::addStimpak(const int& addedStimpak_)
{
    stimpak_++;
}

void Dweller::addRadAway(const int& addedRadaway_)
{
    radaway_++;
}

void Dweller::useStimpak()
{
    --stimpak_;
    health_ += 20;
    if (health_ >= (100 - radiation_))
    {
        health_ = 100 - radiation_;
    }
}

void Dweller::useRadAway()
{
    --radaway_;
    radiation_ -= 10;
}

Outfit* Dweller::assignOutfit(Outfit* newOutfit_)
{
    Outfit* previousOutfit = outfit_;
    outfit_ = newOutfit_;
    return outfit_;
}

Weapon* Dweller::assignWeapon(Weapon* newWeapon_)
{
    Weapon* previousWeapon = weapon_;
    weapon_ = newWeapon_;
    return weapon_;
}

void Dweller::receiveHealthDamage(const int& damageTaken)
{
    health_ -= damageTaken;

}

bool Dweller::isDead()
{
    if (health_ <= 0)
        return true;

    else
        return false;
}