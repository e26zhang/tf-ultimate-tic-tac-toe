#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h  

enum Piece {TTTS_BLANK, TTTS_O, TTTS_X};
enum Status {NONE, TIE, O, X};

class TicTacToeBoard
{
public:
    TicTacToeBoard();
    void initBoard();
    void displayBoard();
    int move(int cell, Piece _turn);
    Status update();
    Status getStatus();
    Piece _board[3][3];

private:
    Status _gameStatus;
};

#endif
