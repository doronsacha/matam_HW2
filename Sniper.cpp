//
// Created by ayele on 15/06/2021.
//

#include "Sniper.h"


Sniper::Sniper(const mtm::Team team,const int health, const int ammo,const int range,const int power)
        :Character(team, health, ammo, range, power)
{
    type=mtm::SNIPER;
    to_charge=2;
    to_move=4;
    munition_by_shoot=1;
}



bool Sniper::targetIsInRange(GridPoint destination, GridPoint source)
{
    double distance=(double)GridPoint::distance(destination,source);
    double range=this->getRange();
    if((range/2 <=distance) && (distance<=range))
    {
        return true;
    }
    return false;
}
