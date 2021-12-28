//
// Created by ayele on 15/06/2021.
//

#include "Soldier.h"



Soldier::Soldier(const mtm::Team team, const int health, const int ammo, const int range, const int power)
        :Character(team, health, ammo, range, power)
{
    type=mtm::SOLDIER;
    to_charge=3;
    to_move=3;
    munition_by_shoot=1;
}




bool Soldier::targetIsInRange(GridPoint destination, GridPoint source)
{
    int distance=GridPoint::distance(destination, source);
    if(distance<= this->getRange())
    {
        return true;
    }
    return false;
}

