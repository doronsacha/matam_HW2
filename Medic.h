//
// Created by ayele on 15/06/2021.
//

#ifndef THEGAME_MEDIC_H
#define THEGAME_MEDIC_H

#include "Character.h"

class Medic: public Character {
public:
    /**
     * Constructor of a medic according to the instructions
     * @param team
     * @param health
     * @param ammo
     * @param range
     * @param power
     */
    Medic(mtm::Team team, const int health, const int ammo, const int range, const int power);

    /**
     * copy constructor default
     * @param medic
     */
    Medic(const Medic &medic)=default;

    /**
     * check if the target is in range (if the distance is more important than the range
     * @param destination
     * @param source
     * @return
     */
    bool targetIsInRange(GridPoint destination, GridPoint source);

    /**
     * clone a medic
     * @return
     */
    Character *clone() const
    {
        return new Medic(*this);
    }

};

#endif //THEGAME_MEDIC_H
