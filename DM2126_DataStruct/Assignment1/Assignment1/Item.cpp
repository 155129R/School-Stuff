#include "Item.h"
#include <iostream>

using std::cout;
using std::endl;

Item::~Item()
{
    cout << "Item destroyed" << endl;
}

Item::Item(const string& kName, const int& durability_)
:GameObject(kName), durability_(durability_)
{
    cout << "Item instantiated with kName and durability_" << endl;
}

const int Item::getDurability()
{
    if (durability_ > 0)
        return durability_;
    else
        return 0;
}