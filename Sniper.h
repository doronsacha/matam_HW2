//
// Created by ayele on 15/06/2021.
//

#ifndef THEGAME_SNIPER_H
#define THEGAME_SNIPER_H


#include "Character.h"

class Sniper: public Character
{

public:
    /**
     * Constructor of a sniper according to the instructions
     * @param team
     * @param health
     * @param ammo
     * @param range
     * @param power
     */
    Sniper(const mtm::Team team,const int health, const int ammo,const int range,const int power);

    /**
     * copy constructor of a snipper that is default
     * @param sniper
     */
    Sniper(const Sniper &sniper)=default;

    /**
     * Check if the target is in range according to the instructions
     * @param destination
     * @param source
     * @return
     *
     */
    bool targetIsInRange(GridPoint destination, GridPoint source);

    /**
     * clone a snipper
     * @return
     */
    Character *clone() const
    {
        return new Sniper(*this);
    }

};

#endif //THEGAME_SNIPER_H
