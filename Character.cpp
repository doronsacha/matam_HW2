//
// Created by ayele on 15/06/2021.
//

#include "Character.h"


Character::Character(const mtm::Team new_team, const int new_health, const int new_ammo, const int new_range, const int new_power)
        :team(new_team), health(new_health), ammo(new_ammo), range(new_range), power(new_power)
{

    number_of_touchs=0;
    type=mtm::SOLDIER;
    munition_by_shoot=UNDEFINED;
    to_charge=UNDEFINED;
    to_move=UNDEFINED;
}
//s
void Character::getDamage(mtm::CharacterType type_of_shooter,mtm::Team team_of_shooter,int power_of_shooter, int number_of_touchs)
{
    if (type_of_shooter == mtm::SNIPER)
    {
        if (number_of_touchs%3==0 && number_of_touchs!=0)
        {
            this->health -= (power_of_shooter) * 2;
        }
        else
        {
            this->health -= (power_of_shooter);
        }
    }

    if (type_of_shooter == mtm::MEDIC)
    {
        if (this->getTeam() == team_of_shooter)
        {
            this->health += power_of_shooter;
        }
        else
        {
            this->health -= power_of_shooter;
        }
    }
    if (type_of_shooter == mtm::SOLDIER)
    {
        if (team_of_shooter == this->getTeam())
        {

        }
        else
        {
            this->health -= power_of_shooter;
        }
    }
}

void Character::getCollateralDamage(int power_of_shooter)
{
    double to_subtract=(double)power_of_shooter/2;
    int next=ceil(to_subtract);
    this->health-=next;
}

void Character::reload()
{
    this->ammo+=this->getCharge();
}



void Character::shoot()
{
    this->ammo -= getToShoot();
    this->number_of_touchs++;
}





