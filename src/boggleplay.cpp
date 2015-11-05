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
//bool playerTurn (Boggle boggle);
void updateStatus (string message, Boggle& boggle, Vector <string>& found);
void playerTurn (Boggle& boggle, Vector<string>& found);

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
    Vector<string> found;
    playerTurn(boggle, found);

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

void playerTurn (Boggle& boggle, Vector<string>& found) {
    bool rightLastTurn = true;
    string message = "Its your turn!";

    while(true){
        clearConsole();
        updateStatus (message, boggle, found);
        string word;
        word = getLine("Type a word (or Enter to stop): ");
        if(word == ""){ break; }
        word= toUpperCase(word);
        if (boggle.checkWord(word)) {
            found.add(word);
            message = "You found a new word! \""  + word + "\"";
            rightLastTurn = true;
        }
        else {
            rightLastTurn = false;
            message = "You must enter an unfound 4+ letter word from the dictionary.";
        }
    }
}
void updateStatus (string message, Boggle& boggle, Vector <string>& found ) {
    cout<<message<< endl;
    cout<< boggle << endl;
    cout<<""<< endl;
    cout <<  "Your words (0): " << found.toString()<< endl;
    cout << "Your score: " << boggle.getScoreHuman()<< endl;
}


