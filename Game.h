//
// Created by ayele on 15/06/2021.
//

#ifndef THEGAME_GAME_H
#define THEGAME_GAME_H




#include "Character.h"
#include "Auxiliaries.h"
#include <memory>
#include <vector>

namespace {
    using mtm::GridPoint;
    using mtm::CharacterType;
    using mtm::Team;
    using mtm::units_t;
}

namespace
{
    using std::vector;
    using std::shared_ptr;
}

class Game{
    int height;
    int width;
    vector<vector<shared_ptr<Character>>> game;


public:
    /**
     *
     * Game constructor - build a game designed by his height and his width
     * This constructor buid a vector of vectors of shared pointers that are pointing on characters
     *
     * @param height number of rows in the game
     * @param width numbers of columns in the game
     */
    Game(int height, int width);

    /**
     * ~Game
     * Destructor of the game
     * Is default because we are not doing allocation and the pointers in the game are shared ptr so they don"t need delete
     */
    ~Game();

    /**
     * Copy Constructor of a game
     *
     * @param other - the game that we have to copy
     *
     * Build a new gane in this of the size of others, copy all the informations of others (clone the characters)
     * Make shared pointers on those new characters and put them in the new game
     *
     */
    Game(const Game& other);

    /**
     * Operator =
     * @param other -the game that we have to take his informations to put in the this.
     *
     * take the information sof other to put them into this.
     * In case of need resize before the size of this.
     * Clone all the characters that other is pointing one to create a new character (other and this have to be independent) and create a pointer on this new character.
     *
     * @return a pointer on this new game
     *
     */
    Game& operator=(const Game& other);

    /**
     * AddCharacter - Put a new character in the game
     * @param coordinates - the location on the board where  we have to add the characte
     * @param character a shared pointer on the new character that we have to add.
     *
     */
    void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

    /**
     *
     * @param type the new's character type (Medic/Sniper/Soldier)
     * @param team  the new's character team (POWERLIFTERS/ CROSSFITTERS)
     * @param health the new's character health - have to be positive
     * @param ammo the new's character ammo - have to be not negative
     * @param range the new's character range - have to be non negative
     * @param power the new's character power - have to be non negative
     *
     * @throw Illegal Argument - if one of the values is incorrect
     *
     * @return - a shared pointer on the new character
     */
    static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                    units_t health, units_t ammo, units_t range, units_t power);

    /**
     * Move a character in the current board (in fact move the shared pointer that is pointing on this character)
     *
     * @param src_coordinates - a grid point on the character taht we have to move
     * @param dst_coordinates - a grid point (the localisation where he ave to move)
     *
     * @throw IllegalCell - if one of the cells designed by the gridpoints are not in the board
     * @throw CellEmpty - if there is no one character on the source
     * @throw MoveTooFar - if the character have to moove too far (according to his possibilities)
     * @throw CellOccupied - if there is already a character is the destination
     *
     */
    void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

    /**
     * Attack - a character attack another character the game
     * @param src_coordinates a grid point on the character that is attacking
     * @param dst_coordinates a grid point on the character that is attacked
     *
     * The function is doing the attack (shoot), the target is getting the dammages (according to the instructions) and in case of the attaquant is a soldier the nears cells are getting collateral dammages
     *
     * @throw IllegalCell in case of of the cells is not in the board
     * @throw CellEmpty in case the cell of the shooter is empty (the shooter dosesnt exist)
     * @throw OutOfRange - in case the distance between the shooter and the target is more imporant than the range of the shooter (he cant touch the target)
     * @throw OutOfAmmo in case the shooter doesn't have ammo to touch the target
     * @throw IllegalTarget - in case the shooter is a medic or a sniper and he try to touch a empty case
     * @throw IllegalTarget - in case the shooter is a snipper and he try to touch a member of his team
     * @throw IllegalTarget - in case a soldier try to touvh a cell in his row or in his column
     * @throw IllegalTarget - in case a medic try to touch himself
     *
     */
    void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

    /**
     * Reload a character, revharge his ammo
     * @param coordinates a gridpoint of the character that have to recharge his ammo
     *
     * @throw illegalCell in case the celle is out of the board
     * @throw CellEmpty in case there is no one the character on this cell.
     *
     */
    void reload(const GridPoint & coordinates);

    /**
     * PrintTheBoard
     * First convert the game to a string by an helper function that is converting each pointer to a letter or " ".
     * And after is printing the board with the print operastor that we have and sending the letters.
     * @return teh printGameBoard
     *
     */
    friend std::ostream& operator<<(std::ostream&, const Game&);

    /**
     * Checking if the game is over
     * @param winningTeam a pointer on a team that we have to modify with the team taht won
     * @return true if one of team won (there are no more players of the other team on the game)
     *@return false if no one won (still players of the two teams on the board or all the players were removed
     *
     */
    bool isOver(Team* winningTeam= nullptr) const;

};
/**
 * Check that the team is on eof the two teams in the exercice
 * @param team the team that we have to verify
 * @return true or false id it is valid or not
 *
 */
bool isValidTeam(const mtm::Team team);
/**
 * Before making a character, check if the arguments are valids (according to the instructions)
 * @param team
 * @param health
 * @param ammo
 * @param range
 * @param power
 * @return true or false if it is valid or not
 *
 */
void isValidArgument(const mtm::Team team,const int health, const int ammo,const int range,const int power);

/**
 * returnTheChar: function helper in the print
 * For each pointer in the board this function returns the char corresponding (if the character is a snipper, soldier, powerliffter...)
 *
 */
char returnTheChar(Team team,CharacterType type);



#endif //THEGAME_GAME_H
