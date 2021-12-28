//
// Created by ayele on 15/06/2021.
//

#ifndef THEGAME_CHARACTER_H
#define THEGAME_CHARACTER_H

#define UNDEFINED -1


#include <iostream>
#include <memory>

#include "Auxiliaries.h"

namespace
{
    using mtm::GridPoint;
}

namespace
{
    using std::shared_ptr;
}

class Character
{
protected:
    mtm::CharacterType type;
    mtm::Team team;//team of the character
    int health; //health of the character
    int ammo;  //number of munitions
    int range;  //range of shoots
    int power;  //power of the shoots
    int munition_by_shoot; //cost of a shoot
    int number_of_touchs;
    int to_charge; //when reload how many munitions we get
    int to_move; //where the character can move
//s

public:

    /**
     * Constructor of a character.
     * After verify than the arguments are valid
     * @param new_team team of the character
     * @param new_health health of the character
     * @param new_ammo ammo of the character
     * @param new_range range of the character
     * @param new_power range of the character
     *
     */
    Character(const mtm::Team new_team, const int new_health, const int new_ammo, const int new_range, const int new_power);

    ~Character()=default;

    /**
     * copy a character
     * @param character - the character that we have to copy
     *
     */
    Character(const Character& character)=default;

    /**
     * shoot - and adapt the ammo of the shooter after the shoot
     *
     */
    void shoot();

    /**
     * If this character is the target get the damages according to the parameters of the shooter
     * @param type_of_shooter
     * @param team_of_shooter
     * @param power_of_shooter
     * @param number_of_touchs
     *
     */
    void getDamage(mtm::CharacterType type_of_shooter,mtm::Team team_of_shooter,int power_of_shooter, int number_of_touchs);

    /**
     * If the shooter is a soldier and  this character is near of the target  he get collateral dammages (according to the instructions)
     * @param power_of_shooter
     *
     */
    void getCollateralDamage(int power_of_shooter);

    /**
     * reload a character, he get more ammo
     */
    void reload();

    /**
     * Check if the target is in the range of the shooter (acoording to the instructions and the team of the shooter
     * @param destination gridpoint of the target
     * @param source gris point of the shooter
     * @return true or false if the target is in the range or not
     *
     */
    virtual bool targetIsInRange(GridPoint destination, GridPoint source)=0;

    /**
     * clone a character
     */
    virtual Character* clone() const=0;\


/**
 * Allof the following functions are returning a specific  information about a character
 * @return
 */
    mtm::CharacterType returnCharacterType() const
    {
        return this->type;
    }

    int getRange()const
    {
        return this->range;
    }
    int getAmmo()const
    {
        return this->ammo;
    }
    int getMove() const
    {
        return this->to_move;
    }
    int getCharge() const
    {
        return this->to_charge;
    }
    int getPower() const
    {
        return this->power;
    }
    int getToShoot()const
    {
        return this->munition_by_shoot;
    }
    mtm::Team getTeam()const
    {
        return this->team;
    }
    int getHealth() const
    {
        return this->health;
    }

    int getNumberOfTouchs() const
    {
        return this->number_of_touchs;
    }


};




#endif //THEGAME_CHARACTER_H
