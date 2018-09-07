#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.h"

class UltimateTicTacToe
{
public:
    UltimateTicTacToe();
    void displayBoards();
    char getTurn();
    void move(int cell);
    int getBoardNo();
    void setBoardNo(int board_no);
    bool boardFinished();
    void selectNewBoard();
    Status update();

private:
    void initStatuses();
    void setTurn();

    int _board_no;   // current # tictactoe board
    Piece _turn;     // hold current player
    TicTacToeBoard _boards[3][3];
    Status _boardStatuses[3][3];  // store the status of each tictictoe game
};

#endif
