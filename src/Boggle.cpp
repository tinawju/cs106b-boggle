// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "random.h"
#include "grid.h"
#include "vector.h"
#include "strlib.h"
#include "bogglegui.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function: Boggle constructor
 * Usage: Boggle(dictionary) OR Boggle(dictionary, boardText)
 * ==================================================================
 * Description: FILL ME!
 */
Boggle::Boggle(Lexicon& dictionary, string boardText) {
    //store dictionary in Boggle's private Lexicon
    this->dict = dictionary;
    this-> humanScore = 0;

    //set size of board
    this->board.resize(size, size);

    //fill the Boggle board
    if(boardText.length() > 0){     //assume string is of letters + length == size^2 - checking to be added later.
        boardText = toUpperCase(boardText);
        int strPos = 0;
        for(int row = 0; row < this->size; row++){
            for(int col = 0; col < this->size; col++){
                board[row][col] = boardText.at(strPos);
                strPos++;
            }
        }
    } else {    //randomly place blocks AND randomly choose which letter faces up
        //instantiate string vector and store CUBES
        Vector<string> cubes;
        for(int i = 0; i < this->size*this->size; i++){
            cubes.add(CUBES[i]);
        }
        //for each location, randomly place a "cube" with a random side facing up
        for(int row = 0; row < this->size; row++){
            for(int col = 0; col < this->size; col++){
                int randCube = randomInteger(0, cubes.size()-1);         //choose random cube from vector
                int randSide = randomInteger(0, cubes[0].length()-1);    //choose random side of cube
                char letter = cubes[randCube].at(randSide);
                this->board[row][col] = letter;
                cubes.remove(randCube);                                 //remove the chosen cube
                boardText += letter;
            }
        }
    }


