#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

// probability of randomly choosing 2 for a cell:
// PROB_2_NUM / PROB_2_DEN

const int
    PROB_2_NUM = 9,
    PROB_2_DEN = 10;

//==============================================================
// void displayBoard(int board[4][4],int score)
//  clear screen and display board and score
//
// Parameters
// board - the game board to be displayed
// score - current game score
//

void displayBoard(int board[4][4],int score) {

    // clear screen
    cout << "\033[2J\033[H";

    // display score
    cout << "Score: " << score << endl;

    // display board, one row at a time
    for (int row=0;row<4;row++) {
        // draw top of box and top row of space
        cout << "+--------+--------+--------+--------+\n"
                "|        |        |        |        |" << endl;

        // draw the row with numbers
        for (int col=0;col<4;col++) {
            cout << "| ";

            if (board[row][col] == 0)
                cout << "       ";
            else
                cout << setw(6) << board[row][col] << ' ';
        }

        // draw end of numbers row and bottom row of space
        cout << "|\n|        |        |        |        |"
            << endl;
    }

    // draw the bottom of game board
    cout << "+--------+--------+--------+--------+" << endl;

}

//==============================================================
// void fillCell(int board[4][4])
//  pick random empty cell in board and put 2 or 4 there
//
// Parameter
// board - game board to update
//

void fillCell(int board[4][4]) {
    int
        nEmpty = 0;
    static random_device
        rd;
    static mt19937
        mt(rd());

    // count number of empty cells (nEmpty)
    for (int row=0;row<4;row++)
        for (int col=0;col<4;col++)
            if (board[row][col] == 0)
                nEmpty++;

    // if nEmpty == 0, stop
    if (nEmpty == 0)
        return;

    // pick random number 1 -- nEmpty
    uniform_int_distribution<>
        dis(1,nEmpty);
    int
        pick = dis(mt);

    // scan board, stop when empty cell count == random pick
    int
        count = 0;
    for (int row=0;row<4;row++) {
        for (int col=0;col<4;col++) {
            if (board[row][col] == 0) {
                count++;
                if (count == pick) {
                    // randomly choose 2 or 4, place in that cell
                    uniform_int_distribution<>
                        dis2or4(1,PROB_2_DEN);

                    if (dis2or4(mt) <= PROB_2_NUM)
                        board[row][col] = 2;
                    else
                        board[row][col] = 4;

                    // stop
                    return;

                }
            }
        }
    }
}

int main() {
    int
        board[4][4]={0},
        score=0;
    char
        choice;

    // initialize game board
    // a. clear all positions (done)
    // b. choose empty cell randomly
    // c. randomly put 2 or 4 in that cell
    // d. repeat b and c one time
    fillCell(board);
    fillCell(board);

    // start do loop
    do {
        // see if player can slide

        // if player cannot slide and player cannot undo,
        // game is over

        // display board and score
        displayBoard(board,score);

        // get choice
        choice = 'q';

        // process choice

    // end do loop
    } while (choice != 'q' && choice != 'Q');

    // display final board and score
    displayBoard(board,score);

    return 0;
}