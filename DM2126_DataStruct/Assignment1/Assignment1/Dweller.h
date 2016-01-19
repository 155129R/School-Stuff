#ifndef DWELLER_H
#define DWELLER_H

#include "GameObject.h"
#include "Outfit.h"
#include "Weapon.h"
#include "Vec2D.h"

class Dweller : public GameObject
{

public:

    virtual ~Dweller();

    Dweller(const string& dwellerName = "", const int& assignedSPECIAL_ = 0);     //[CONSTRUCTOR](Override) Intialize instance of Dweller class and instantiate member variables and take in name and special value of the dweller

    const int getSPECIAL();     //[GETTER] Get special value of dweller

    const int getCurrentHealth();   //[GETTER] Get current health

    const int getCurrentRadDamage();    //[GETTER] Get current Radiation Damage

    const int getAttackDmg();           //[GETTER] Get attack damage

    void setPosition(const Vec2D& newPosition);       //[SETTER] Set position(location) of dweller

    const Vec2D getPosition();                      //[GETTER] Get position(location) of dweller

    void receiveHealthDamage(const int& damageTaken);   //Apply damage to health

    void receiveRadDamage(const int& radiationDamageTaken); //Apply Radiation Damage

    void receiveEquipmentDamage(const int& damageToDurability); //Apply damage to durability

    void addStimpak(const int& addedStimpak_);   //Add stimpak

    void addRadAway(const int& addedRadaway_);   //Add RadAway

    void useStimpak();

    void useRadAway();

    Outfit* assignOutfit(Outfit* newOutfit_);  //Assign outfit

    Weapon* assignWeapon(Weapon* newWeapon_);  //Assign weapon

    bool isDead();     //Is Dweller Dead?

protected:

private:

    Vec2D position_;

    int SPECIAL_;

    int health_;

    int radiation_;

    int stimpak_;

    int radaway_;

    Outfit* outfit_;

    Weapon* weapon_;



};

#endif /*DWELLER_H*/