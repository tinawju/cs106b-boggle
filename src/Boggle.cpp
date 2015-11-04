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
    BoggleGUI::labelAllCubes(boardText);
    BoggleGUI::setStatusMessage("Its your turn!");
}

/* Function: Gets letter at specific board location
 * Usage: char ch = b.getLetter(row, col)
 * ==================================================================
 * Description: Returns the character at the specific location given in the board.
 * If out of bounds, will throw an int error - if either row or col,
 * will throw that row or col value. If both are out of bounds, will throw row value.
 */
char Boggle::getLetter(int row, int col) {      //may be error because of only one return in the if-else statement ???
    if(row > this->size || row < 0){
        throw row;
    } else if(col > this->size || col < 0){
        throw col;
    } else {
        return this->board[row][col];
    }
}

/* Function: Checks if word is valid
 * Usage: bool isValid = checkWord(word)
 * ==================================================================
 * Description: Returns whether the given word is valid, according to the following rules:
 * (1) At least 4 letters long
 * (2) Found in the English dictionary
 * (3) Can be formed by connecting neighboring letters (using any cube only once)
 * (4) Has not already been formed by player during game
 */
bool Boggle::checkWord(string word) {
    if(word.length() >= 4 && this->dict.contains(word) && !alreadyFound(word)){
        if(humanWordSearch(word)){
            //string message = "You found a new word! \"" + toUpperCase(word) + "\"";
            BoggleGUI::setStatusMessage("You found a new word! \"" + toUpperCase(word) + "\"");
            BoggleGUI::setScore(humanScore, BoggleGUI::HUMAN);
            return true;
        } else {
            BoggleGUI::setStatusMessage("That word can't be formed on this board.");
        }
    } else {
        BoggleGUI::setStatusMessage("You must enter an unfound 4+ letter word from the dictionary.");
        }
    return false;
}

bool Boggle::humanWordSearch(string word) {     //assume word is >= 4 letters, has not been used, is in English dictionary aka vetted by checkWord
    word = toUpperCase(word);
    BoggleGUI::setAnimationDelay(100);
    //search board for all locations with first letter
    for(int row = 0; row < this->size; row++){
        for(int col = 0; col < this->size; col++){
            BoggleGUI::setHighlighted(row, col, true);
            if(this->board[row][col] == word.at(0)){
                if(humanWordSearchHelper(word.substr(1), row, col)){
                    this->found.add(word);
                    this->humanScore++;
                    return true;
                }
            }
            BoggleGUI::setHighlighted(row, col, false);
        }
    }
    return false;
}

bool Boggle::humanWordSearchHelper(string word, int row, int col){
    //BoggleGUI::setHighlighted(row, col, false);
    if(word.empty()){
        return true;
    } else {
        //check all neighbors
        for(int r = -1; r <= 1; r++){
            for(int c = -1; c <= 1; c++){
                if(!(r == 0 && c == 0)){   //remove original location
                    int nRow = row + r;
                    int nCol = col + c;
                    if(!(nRow < 0 || nRow >= this->size || nCol < 0 || nCol >= this->size)){    //if not out of bounds
                        BoggleGUI::setHighlighted(nRow, nCol, true);
                        if(this->board[nRow][nCol] == word.at(0)){    //if location has the next character
                            if(humanWordSearchHelper(word.substr(1), nRow, nCol)){
                                return true;
                        }
                    }
                    BoggleGUI::setHighlighted(nRow, nCol, false);
                }
            }
        }
    }
    }
    BoggleGUI::setHighlighted(row, col, false);
    return false;
}

int Boggle::getScoreHuman() {
    return this-> humanScore;

}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    return this-> computerScore;
}

int Boggle::getSize(){
    return this->size;
}

bool Boggle::alreadyFound(string word){
    for(string str : this->found){
        if(str == word){
            return true;
        }
    }
    return false;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    string boardLine = "";
    int n = boggle.getSize();
    for (int r =0; r< n; r++){
        string boardLine = "";
        for (int c =0; c < n; c++){
            boardLine += boggle.getLetter(r,c);
        }
        cout <<boardLine<<endl;
    }
    return out;
}



