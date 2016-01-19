#ifndef ITEM_H
#define ITEM_H
#include "GameObject.h"

class Item : public GameObject
{
public:


    virtual ~Item(); //[DESTRUCTOR]	Delete instance of Item class

    Item(const string& kName = "", const int& durability_ = 0);//[CONSTRUCTOR] Intialize instance of Item class and instantiate member variables and takes in name of object and initial durability value

    virtual void receiveDamage(const int& damageToItemDurability) = 0;  //Apply or Receive damage (Define in outfit and weapon)

    const int getDurability(); //[GETTER] Gets durability value of item

protected:

    int durability_;

private:

};

#endif /*ITEM_H*/