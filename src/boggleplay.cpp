// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "Boggle.h"
using namespace std;

string promptForBoardText();
bool isLetters(string boardText);

void playOneGame(Lexicon& dictionary) {
    string boardText = "";
    if(!getYesOrNo("Do you want to generate a random board? ")){
        boardText = promptForBoardText();
    }
    Boggle boggle(dictionary, boardText);
    // clear console
    // IT'S YOUR TURN
    //Print the boggle board
    // endl
    /*Your words (0): {}
    Your score: 0
    Type a word (or Enter to stop):
    */

    string word;
    while(true){
        word = getLine("Type a word (or Enter to stop): ");
        if(word == ""){ break; }
        boggle.checkWord(word);
    }

}

/* Function: Prompts user for board text
 * Usage: string boardText = promptForBoardText()
 * ==================================================================
 * Description: Prompts user to manually configure the board with their own text.
 * The function will continuously prompt the user until the user input
 * a 16-letter string that contains only letters. Returns the string.
 */
string promptForBoardText(){
    string boardText;
    bool hasBeenPrompted = false;
    while(boardText.length() != 16 || !isLetters(boardText)){
        if(hasBeenPrompted){
            cout << "That is not a valid 16-letter board string. Try again." << endl;
        }
        boardText = getLine("Type the 16 letters to appear on the board: ");
        hasBeenPrompted = true;
    }
    return boardText;
}

/* Function: Checks if string is only letters
 * Usage: isLetters(str)
 * ==================================================================
 * Description: Returns whether a string is composed of only letters.
 */
bool isLetters(string str){
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < str.length(); i++){
        if(alphabet.find(str.at(i)) == string::npos){
            return false;
        }
    }
    return true;
}
