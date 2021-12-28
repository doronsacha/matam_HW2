//
// Created by ayele on 15/06/2021.
//

#include "Medic.h"


Medic::Medic(mtm::Team  team, const int health, const int ammo, const int range, const int power)
        :Character(team, health, ammo, range, power)
{
    type=mtm::MEDIC;
    to_charge=5;
    to_move=5;
    munition_by_shoot=1;
}




bool Medic::targetIsInRange(GridPoint destination, GridPoint source)
{
    int distance=GridPoint::distance(destination,source);
    if(distance>getRange())
    {
        return false;
    }
    return true;
}
