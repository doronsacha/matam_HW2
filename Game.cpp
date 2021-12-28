//
// Created by ayele on 15/06/2021.
//

#include "Game.h"

#include "Exceptions.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Medic.h"

#include <cmath>


/*
 *
 * pb de la tahmochet et du medic
 *
 */


namespace {
    using mtm::GridPoint;
    using mtm::CharacterType;
    using mtm::Team;
    using mtm::units_t;
}


Game::Game(int height, int width):height(height),width(width)
{
    if(height<=0 || width<=0)
    {
        throw mtm::IllegalArgument();
    }

    shared_ptr<Character> empty_case= nullptr;

    game.resize(height);

    for(int i=0; i<height; i++)
    {
        game[i].resize(width);
    }

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            game[i][j]=empty_case;
        }
    }
}

Game::~Game()=default;


Game::Game(const Game &other):height(other.height), width(other.width)
{
    this->game.resize(height);

    for(int i=0; i<height; i++)
    {
        this->game[i].resize(width);
    }

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(other.game[i][j]!= nullptr)
            {
                this->game[i][j]=(shared_ptr<Character>)other.game[i][j]->clone();
            }
            else
            {
                this->game[i][j]= nullptr;
            }

        }
    }
}


Game &Game::operator=(const Game &other)
{

    height=other.height;
    width=other.width;

    this->game.resize(height);
    for(int i=0; i<height; i++)
    {
        this->game[i].resize(width);
    }


    for(int i=0; i<height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (other.game[i][j] != nullptr)
            {
                shared_ptr<Character> temp = (shared_ptr<Character>) other.game[i][j]->clone();
                this->game[i][j] = temp;
            } else
                {
                this->game[i][j] = nullptr;
            }
        }
    }
    return *this;
}


void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
{
    int dest_row=coordinates.row;
    int dest_col=coordinates.col;

    if(dest_row>=height || dest_col>=width || dest_row<0 || dest_col<0)
    {
        throw mtm::IllegalCell();
    }

    if(game[dest_row][dest_col]!= nullptr)
    {
        throw mtm::CellOccupied();
    }
    else
    {
        game[dest_row][dest_col]=character;
    }
}

std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo,
                                               units_t range, units_t power)
{
    isValidArgument(team,health,ammo,range,power);

    if(type==mtm::SNIPER)
    {
        shared_ptr<Sniper> temp= nullptr;

        temp= std::make_shared<Sniper>(Sniper(team,health,ammo,range,power));
        shared_ptr<Character> conversion=temp;
        return conversion;

    }

    if(type==mtm::SOLDIER)
    {
        shared_ptr<Soldier> temp= nullptr;

        temp= std::make_shared<Soldier>(Soldier(team,health,ammo,range,power));
        shared_ptr<Character> conversion=temp;
        return conversion;
    }

    shared_ptr<Medic> temp= nullptr;

    temp= std::make_shared<Medic>(Medic(team,health,ammo,range,power));
    shared_ptr<Character> conversion=temp;
    return conversion;

}

void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
{
    int source_row=src_coordinates.row;
    int source_col=src_coordinates.col;
    int dest_row= dst_coordinates.row;
    int dest_col=dst_coordinates.col;

    if(source_col>=width || source_row>=height || dest_col>=width || dest_row>=height || source_col<0 || dest_col<0 || source_row<0 || dest_row<0)
    {
        throw mtm::IllegalCell();
    }

    if(game[source_row][source_col]== nullptr)
    {
        throw mtm::CellEmpty();
    }

    int to_move=game[source_row][source_col]->getMove();
    int distance=GridPoint::distance(src_coordinates,dst_coordinates);

    if(distance>to_move)
    {
        throw mtm::MoveTooFar();
    }

    if(game[dest_row][dest_col]!= nullptr)
    {
        throw mtm::CellOccupied();
    }

    game[dest_row][dest_col]=game[source_row][source_col];
    game[source_row][source_col]= nullptr;

}

void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) //ayelete
{
    int source_row=src_coordinates.row;
    int source_col=src_coordinates.col;
    int dest_row= dst_coordinates.row;
    int dest_col=dst_coordinates.col;

    if(source_col>=width || source_row>=height || dest_col>=width || dest_row>=height || source_col<0 || dest_col<0 || source_row<0 || dest_row<0)
    {
        throw mtm::IllegalCell();
    }
    if(game[source_row][source_col]== nullptr)
    {
        throw mtm::CellEmpty();
    }
    if(!(game[source_row][source_col]->targetIsInRange(dst_coordinates,src_coordinates)))
    {
        throw mtm::OutOfRange();
    }

    if(game[source_row][source_col]->returnCharacterType()==mtm::MEDIC)
    {
        if(game[dest_row][dest_col]!= nullptr)
        {
            if(game[source_row][source_col]->getTeam()!=game[dest_row][dest_col]->getTeam())
            {
                if(game[source_row][source_col]->getAmmo()<game[source_row][source_col]->getToShoot())
                {
                    throw mtm::OutOfAmmo();
                }
            }
        }
    }

    if(game[source_row][source_col]->returnCharacterType()==mtm::SOLDIER || game[source_row][source_col]->returnCharacterType()==mtm::SNIPER)
    {
        if(game[source_row][source_col]->getAmmo()<game[source_row][source_col]->getToShoot())
        {
            throw mtm::OutOfAmmo();
        }
    }

    if((game[source_row][source_col]->returnCharacterType()==mtm::MEDIC || game[source_row][source_col]->returnCharacterType()==mtm::SNIPER) && game[dest_row][dest_col]==
                                                                                                                                      nullptr)
    {
        throw mtm::IllegalTarget();
    }

    if(game[source_row][source_col]->returnCharacterType()==mtm::SNIPER && game[source_row][source_col]->getTeam()==game[dest_row][dest_col]->getTeam())
    {
        throw mtm::IllegalTarget();
    }

    if(game[source_row][source_col]->returnCharacterType()==mtm::SOLDIER && source_row!=dest_row && source_col!=dest_col)
    {
        throw mtm::IllegalTarget();
    }


    if(game[source_row][source_col]->returnCharacterType()==mtm::MEDIC && source_col==dest_col && dest_row==source_row)
    {
        throw mtm::IllegalTarget();
    }


    CharacterType shooter_type=game[source_row][source_col]->returnCharacterType();
    mtm::Team shooter_team=game[source_row][source_col]->getTeam();

    //shoot
    if( shooter_type==mtm::SNIPER || shooter_type==mtm::SOLDIER || (shooter_type==mtm::MEDIC && game[dest_row][dest_col]->getTeam()!=shooter_team))
    {
        game[source_row][source_col]->shoot();
    }

    //damages
    mtm::Team team_of_shooter=game[source_row][source_col]->getTeam();
    CharacterType type_of_shooter=game[source_row][source_col]->returnCharacterType();
    int power_of_shooter=game[source_row][source_col]->getPower();
    int number_of_touchs=game[source_row][source_col]->getNumberOfTouchs();

    if(game[dest_row][dest_col]!= nullptr)
    {
        game[dest_row][dest_col]->getDamage(type_of_shooter,team_of_shooter,power_of_shooter, number_of_touchs);
        if(game[dest_row][dest_col]->getHealth()<=0)
        {
            //supprimer son charactere de la memoire???
            game[dest_row][dest_col]= nullptr;
        }
    }

    //collateral damages is the shooter is a soldier
    if(game[source_row][source_col]->returnCharacterType()==mtm::SOLDIER)
    {
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
               if(game[i][j]!= nullptr)
               {
                   GridPoint temp=GridPoint(i,j);
                   int temp_distance=GridPoint::distance(temp,dst_coordinates);
                   double temp_range=(double)game[source_row][source_col]->getRange()/3;
                   int collateral_range=ceil(temp_range);
                   if(!(temp==dst_coordinates) && (temp_distance<=collateral_range && (game[i][j]->getTeam()!=team_of_shooter)))
                   {
                       game[i][j]->getCollateralDamage(power_of_shooter);
                       if(game[i][j]->getHealth()<=0)
                       {
                           game[i][j]= nullptr;  //supprimer son charactere de la memoire???
                       }
                   }
               }
            }
        }
    }
}

void Game::reload(const GridPoint &coordinates)
{
    int row=coordinates.row;
    int col=coordinates.col;

    if(row>=height || col>=width || row<0 || col<0)
    {
        throw mtm::IllegalCell();
    }
    if(game[row][col]== nullptr)
    {
        throw mtm::CellEmpty();
    }

    game[row][col]->reload();
}

char returnTheChar(Team team,CharacterType type)
{
    if(team==mtm::POWERLIFTERS)
    {
        if(type==mtm::MEDIC)
        {
            return 'M';
        }
        if(type==mtm::SOLDIER)
        {
            return 'S';
        }
        if(type==mtm::SNIPER)
        {
            return 'N';
        }
    }
    if(type==mtm::MEDIC)
    {
        return 'm';
    }
    if(type==mtm::SOLDIER)
    {
        return 's';
    }
    if(type==mtm::SNIPER)
    {
        return 'n';
    }

    return 'o';
}


std::ostream &operator<<(std::ostream& os, const Game& game)
{
    std::string string;
    for (int i = 0; i < game.height; i++)
    {
        for (int j = 0; j < game.width; j++)
        {
            if (game.game[i][j] == nullptr)
            {
                string += ' ';
            } else
            {
                char char_to_add = returnTheChar(game.game[i][j]->getTeam(), game.game[i][j]->returnCharacterType());
                string += char_to_add;
            }
        }
    }
    char* get_last=&string[string.length()];
    return mtm::printGameBoard(os,string.data(),get_last,game.width);
}

bool Game::isOver(Team *winningTeam) const
{
    int counter_powerlifters=0;
    int counter_crossfitters=0;

    //shared_ptr<Character> temp;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(game[i][j]!= nullptr)
            {
                if(this->game[i][j]->getTeam()==mtm::CROSSFITTERS)
                {
                    counter_crossfitters++;
                }
                if(this->game[i][j]->getTeam()==mtm::POWERLIFTERS)
                {
                    counter_powerlifters++;
                }
            }

        }
    }
    if((counter_crossfitters==0 && counter_powerlifters==0) || (counter_powerlifters>0 && counter_crossfitters>0))
    {
        return false;
    }

    if(counter_powerlifters==0)
    {
        if(winningTeam!= nullptr)
        {
            *winningTeam=mtm::CROSSFITTERS;
        }
        return true;
    }

    if(counter_crossfitters==0)
    {
        if(winningTeam!= nullptr)
        {
            *winningTeam=mtm::POWERLIFTERS;
        }
        return true;
    }
    return false;
}


bool isValidTeam(const mtm::Team team)
{
    if(team!=mtm::CROSSFITTERS && team!=mtm::POWERLIFTERS)
    {
        return false;
    }
    return true;
}

void isValidArgument(const mtm::Team team,const int health, const int ammo,const int range,const int power)
{
    if(health<=0 || ammo<0 || range<0 || power<0 || !isValidTeam(team))
    {
        throw mtm::IllegalArgument();
    }
}