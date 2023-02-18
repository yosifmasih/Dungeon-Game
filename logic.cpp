#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */

 //COMPLETED
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    
    //declare variables
    int playerRow, playerCol;
    int exitCount = 0;
    int doorCount = 0;

    //open the file
    ifstream fin;
    //ifstream file(fileName);
    fin.open(fileName);

    //check if the file is open
    if(!fin.is_open()){
        return nullptr;
    }
                                                                                            //flag A
                                                                                            //cout << "A" << endl;

    //check if the rows and cols in the file match the max rows and cols
    fin >> maxRow;
    if(fin.fail() || maxRow <= 0){
        return nullptr;
    }
    if(fin.eof()){
        return nullptr;
    }

                                                                                            //flag B
                                                                                            //cout << "B" << endl;
    fin >> maxCol;
    if(fin.fail() || maxCol <= 0){
        return nullptr;
    }
    if(fin.eof()){
        return nullptr;
    }

    if(maxRow  > INT32_MAX/maxCol){
        return nullptr;
    }
    if(maxCol > INT32_MAX/maxRow){
        return nullptr;
    }
                                                                                            //flag C
                                                                                            //cout << "C" << endl;
    //create map after validating the max row and col given in the file
    char** map = createMap(maxRow, maxCol);
    if(map == nullptr){
        deleteMap(map, maxRow);
        return nullptr;
    }
                                                                                            //flag D
                                                                                            //cout << "D" << endl;

    //check if the players starting position in the file matches that in the player struct
    fin >> playerRow;
    if(fin.fail() || playerRow >= maxRow || playerRow < 0){
        deleteMap(map, maxRow);
        return nullptr;
    }
    if(fin.eof()){
        deleteMap(map, maxRow);
        return nullptr;
    }
    player.row = playerRow;
                                                                                            //flag E
                                                                                            //cout << "E" << endl;
    fin >> playerCol;
    if(fin.fail() || playerCol >= maxCol || playerCol < 0){
        deleteMap(map, maxRow);
        return nullptr;
    }
    if(fin.eof()){
        deleteMap(map, maxRow);
        return nullptr;
    }
    player.col = playerCol;
                                                                                            //flag F
                                                                                           // cout << "F" << endl;
    //check if max row and max col is greater than or equal to 1
    if(maxRow < 1){
        deleteMap(map, maxRow);
        return nullptr;
    }
    if(maxCol < 1){
        deleteMap(map, maxRow);
        return nullptr;
    }
                                                                                            //flag G
                                                                                            //cout << "G" << endl;
    //load the rest of the data in the file to the 2D array that holds the map layout
    int i, j;
    if(fin.is_open()){
        for(i=0;i<maxRow;i++){
            for(j=0;j<maxCol;j++){
                //read data
                fin >> map[i][j];
                if(fin.fail()){
                    deleteMap(map, maxRow);
                    return nullptr;
                }
                if(fin.eof()){
                    deleteMap(map, maxRow);
                    return nullptr;
                }
                if(fin.fail() && !fin.eof()){
                    deleteMap(map, maxRow);
                    return nullptr;
                }
            }
        }
    }
                                                                                            //flag H
                                                                                            //cout << "H" << endl;
    //the file should end
    /*
    if(!file.eof()){
        deleteMap(map, maxRow);
        return nullptr;
    }
    */
                                                                                            //flag I
                                                                                            //cout << "I" << endl;
    //validate data
    for(i=0;i<maxRow;i++){
        for(j=0;j<maxCol;j++){
            if(map[i][j] != TILE_OPEN && map[i][j] != TILE_PLAYER && map[i][j] != TILE_TREASURE && map[i][j] != TILE_AMULET && map[i][j] != TILE_MONSTER && map[i][j] != TILE_PILLAR && map[i][j] != TILE_DOOR && map[i][j] != TILE_EXIT){
                deleteMap(map, maxRow);
                return nullptr;
            }
            if(map[i][j] == TILE_EXIT){
                exitCount++;
            }
            if(map[i][j] == TILE_DOOR){
                doorCount++;
            }
        }
    }

    //check if there are too many values
    char yosif;
    fin >> yosif;
    if(!fin.fail()){
        deleteMap(map, maxRow);
        return nullptr;
    }

    map[player.row][player.col] = TILE_PLAYER;
                                                                                            //flag J
                                                                                            //cout << "J" << endl;
    //check if there is at least one door or one exit
    
    if(doorCount == 0 && exitCount == 0){
        deleteMap(map, maxRow);
        return nullptr;
    }
    
                                                                                            //flag K
                                                                                            //cout << "K" << endl;
    //return the loaded 2D array
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */

 //COMPLETED
void getDirection(char input, int& nextRow, int& nextCol) {
    switch(input){
        case INPUT_QUIT: 
            //quit the program
            break;
        case INPUT_STAY: 
            //do nothing
            break;
        case MOVE_UP:
            nextRow--;
            break;
        case MOVE_LEFT:
            nextCol--;
            break;
        case MOVE_DOWN:
            nextRow++;
            break;
        case MOVE_RIGHT:
            nextCol++;
            break;
        default:
            //do nothing
            break;
    } 
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
 //COMPLETED
char** createMap(int maxRow, int maxCol) {
    int i, j;

    //if the maxRow and maxCol is not a positive integer or it is zero
    if(maxRow <= 0 || maxCol <= 0){
        return nullptr;
    }

    char** map = new char*[maxRow] {};

    for(i=0;i<maxRow;i++){
        map[i] = new char[maxCol] {};
    }
    for(i=0;i<maxRow;i++){
        for(j=0;j<maxCol;j++){
            map[i][j] = TILE_OPEN;
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
 //COMPLETED
void deleteMap(char**& map, int& maxRow) {
    int i;

    if(map == nullptr){
        map = nullptr;
        maxRow = 0;
    }
    //check if map is nullptr, return
    for(i=0;i<maxRow;i++){
        delete[] map[i];
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
//COMPLETED
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    //check if args are valid
    if(maxRow <= 0 || maxCol <= 0){
        return nullptr;
    }
    if(maxRow >= INT32_MAX){
        return nullptr;
    }
    if(maxCol >= INT32_MAX){
        return nullptr;
    }
    if(map == nullptr){
        return nullptr;
    }
    int i, j;
    int row = maxRow * 2;
    int col = maxCol * 2;

    //double map dimensions
    char** finalMap = createMap(row, col);

    //copy over values and move map layout 

    //first quadrant
    for(i=0;i<maxRow;i++){
        for(j=0;j<maxCol;j++){
            finalMap[i][j] = map[i][j];
        }
    }

    //third quadrant
    for(i=0;i<maxRow;i++){
        for(j=0;j<maxCol;j++){
            finalMap[i+maxRow][j] = map[i][j];
            if(finalMap[i][j] == TILE_PLAYER){
                finalMap[i + maxRow][j] = TILE_OPEN;
            }
        }
    }

    //second quadrant
    for(i=0;i<maxRow;i++){
        for(j=0;j<maxCol;j++){
            finalMap[i][j+maxCol] = map[i][j];
            if(finalMap[i][j] == TILE_PLAYER){
                finalMap[i][j + maxCol] = TILE_OPEN;
            }
        }
    }

    //fourth quadrant
    for(i=0;i<maxRow;i++){
        for(j=0;j<maxCol;j++){
            finalMap[i + maxRow][j + maxCol] = map[i][j];
            if(finalMap[i][j] == TILE_PLAYER){
                finalMap[i + maxRow][j + maxCol] = TILE_OPEN;
            }
        }
    }

    deleteMap(map, maxRow);

    maxRow = row;
    maxCol = col;

    return finalMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
//COMPLETED
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    //if nextCol or nextRow is invalid
    if(nextRow < 0 || nextCol < 0){
        //player stays
        return STATUS_STAY;
    }
    //if a player moves outside array bounds, to a monster, or to a pillar
    if(nextRow > maxRow-1 || nextCol > maxCol-1 || map[nextRow][nextCol] == 'M' || map[nextRow][nextCol] == '+'){
        //dont move player
        player.row = player.row;
        player.col = player.col;
        return STATUS_STAY;
    }
    //if a player moves to a treasure
    if(map[nextRow][nextCol] == '$'){
        //move player and increment treasure
        player.treasure++;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
        return STATUS_TREASURE;
    }
    //if a player moves to an amulet, set status accordingly
    if(map[nextRow][nextCol] == '@'){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
        //set amulet status
        return STATUS_AMULET;
    }
    //if a player moves next to a door, set status accordingly
    if(map[nextRow][nextCol] == '?'){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
        //set leave status
        return STATUS_LEAVE;
    }
    //if player moves to an exit and has at least one piece of treasure, set status accordingly
    if(map[nextRow][nextCol] == '!' && player.treasure >= 1){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
        //set exit status
        return STATUS_ESCAPE;
    }
    //if player moves to an exit and has no treasure, treat the door as a pillar
    if(map[nextRow][nextCol] == '!' && player.treasure <= 0){
        //dont move
        return STATUS_STAY;
    }

    //if a player moves in any valid direction
    if(map[nextRow][nextCol] != 'M' || map[nextRow][nextCol] != '+' || (map[nextRow][nextCol] == TILE_DOOR && player.treasure <= 0)){
        //move player accordingly
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
        return STATUS_MOVE;
    }

    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
//COMPLETED
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {

    int i, j;

    //check whether there is a pillar or a monster in the players line of site

    //ABOVE (w)
    for(i=player.row;i>=0;i--){ 
        if(map[i][player.col] == TILE_PILLAR){
            break;
        }
        else if(map[i][player.col] == TILE_MONSTER){
            map[i+1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        }
    }

    //LEFT (a)
    for(i=player.col;i>=0;i--){
        if(map[player.row][i] == TILE_PILLAR){
            break;
        }
        else if(map[player.row][i] == TILE_MONSTER){
            map[player.row][i+1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    //DOWN (s)
    for(i=player.row;i<maxRow;i++){
        if(map[i][player.col] == TILE_PILLAR){
            break;
        }
        else if(map[i][player.col] == TILE_MONSTER){
           map[i-1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN; 
        }
    }

    //RIGHT (d)
    for(i=player.col;i<maxCol;i++){
        if(map[player.row][i] == TILE_PILLAR){
            break;
        }
        else if(map[player.row][i] == TILE_MONSTER){
            map[player.row][i-1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    //monster reaches the player
    if(map[player.row][player.col] == TILE_MONSTER){
        return true;
    }

    return false;
}