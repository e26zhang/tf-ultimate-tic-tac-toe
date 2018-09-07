#include <iostream>
#include "../include/tic_tac_toe.h"

using namespace std;

TicTacToeBoard::TicTacToeBoard()
{
    initBoard();
    _gameStatus = NONE;
}

void TicTacToeBoard::initBoard()
{
    for(int x = 0; x < 3; ++x)
        for(int y = 0; y < 3; ++y)
            _board[x][y] = TTTS_BLANK;
}

Status TicTacToeBoard::getStatus()
{
    return _gameStatus;
}

int TicTacToeBoard::move(int cell, Piece _turn)
{
    /* player grid is display from 1 
     * so 1 must be subtracted for the 
     * correct indice */
    cell = cell - 1;
    if(_board[cell/3][cell%3] == TTTS_BLANK) {
        _board[cell/3][cell%3] = _turn;
        return 1;
    }
    return 0;  // cell already occupied
}

Status TicTacToeBoard::update()
{ 
    bool tie = true;
    /* check for a tie */
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(_board[i][j] == TTTS_BLANK)
                tie = false;

    if(tie) {
        _gameStatus = TIE;
        return TIE;
    }

    /* DIAGONALS */
    /* top-left to bottom-right */
    if(_board[0][0] != TTTS_BLANK && 
       _board[0][0] == _board[1][1] && 
       _board[1][1] == _board[2][2]) {
        _gameStatus = _board[0][0] == TTTS_X ? X : O;
        return _gameStatus; // return winner
    }        
    
    /* top-right to bottom-left */
    if(_board[0][2] != TTTS_BLANK && 
       _board[0][2] == _board[1][1] && 
       _board[1][1] == _board[2][0]) {
        _gameStatus = _board[0][2] == TTTS_X ? X : O;
        return _gameStatus; // return winner
    }        

    /* COLUMNS */
    for(int column = 0; column < 3; column++)
    {
        if(_board[0][column] == _board[1][column] \
                && _board[0][column] != TTTS_BLANK \
                && _board[1][column] == _board[2][column]) {
            _gameStatus = _board[0][column] == TTTS_X ? X : O;
            return _gameStatus; // return winner
        }
    }
    
    /* ROWS */
    for(int row = 0; row < 3; row++)
    {
        if(_board[row][0] != TTTS_BLANK
            && _board[row][0] == _board[row][1] \
            && _board[row][1] == _board[row][2]) {
            _gameStatus = _board[row][0] == TTTS_X ? X : O;
            return _gameStatus; // return winner
        }
    }
    
    return NONE; // no one has won yet
}
