//
// Created by ayele on 15/06/2021.
//

#ifndef THEGAME_SOLDIER_H
#define THEGAME_SOLDIER_H


#include "Character.h"

class Soldier: public Character
{

public:

    /**
     * Constructor of a soldier according to the instructions
     * @param team
     * @param health
     * @param ammo
     * @param range
     * @param power
     *
     */
    Soldier(const mtm::Team team, const int health, const int ammo, const int range, const int power);

    /**
     * copy constructor of a soldier that is default
     * @param soldier
     */
    Soldier(const Soldier &soldier)=default;

    /**
     * Check if the target is in range according to the instructions
     * @param destination
     * @param source
     * @return
     *
     */
    bool targetIsInRange(GridPoint destination, GridPoint source);

    /**
     * Clone a soldier
     */
    Character *clone() const
    {
        return new Soldier(*this);
    }
};



#endif //THEGAME_SOLDIER_H
