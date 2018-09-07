#include <iostream>
#include "../include/ultimate_tic_tac_toe.h"

using namespace std;

UltimateTicTacToe::UltimateTicTacToe()
{
    _turn = TTTS_X;
    initStatuses();
}

void UltimateTicTacToe::initStatuses()
{
    /*
     * Initialise board statuses to NONE
     */
    for(int x = 0; x < 3; x++)
        for(int y = 0; y < 3; y++)
            _boardStatuses[x][y] = NONE;
}

char UltimateTicTacToe::getTurn()
{
    return _turn == TTTS_X ? 'X' : 'O'; 
}

void UltimateTicTacToe::setTurn()
{
    _turn = _turn == TTTS_X ? TTTS_O : TTTS_X;
}

int UltimateTicTacToe::getBoardNo()
{
    return _board_no;
}

void UltimateTicTacToe::setBoardNo(int board_no)
{
    _board_no = board_no;
}

bool UltimateTicTacToe::boardFinished()
{
        if(_boardStatuses[_board_no/3][_board_no%3] != NONE)
            return true;
        return false;
}

void UltimateTicTacToe::selectNewBoard()
{
    cout << "The game on the next board is finished, " << getTurn() << " select next board: ";
    cin >> _board_no;
    _board_no -= 1;
    if(boardFinished())
        selectNewBoard();
}

void UltimateTicTacToe::move(int cell)
{
    cout << "Board no: " << _board_no+1 << endl;
    // convert 1d index to 2d
    if(_boards[_board_no/3][_board_no%3].move(cell, _turn)) {
        // minus 1 for zero indexing and convert 2d index to 1d :D
        _board_no = cell - 1; 
    } else {
        // chosen cell is already occupied
        cout << "Position already occupied. Try again." << endl;
        cout << "cell: ";
        cin >> cell;
        move(cell);  // call the function again with new parameters
    }
}

void UltimateTicTacToe::displayBoards()
{
    /*
     * shape of data (3, 3, 3, 3)
     * To print to a terminal correctly
     * we need to print row n of each
     * board first.
     * [0, 1, 2] [9, 10, 11] -> row
     * [3, 4, 5] [12, 13, 14] -> row
     * see: https://gist.github.com/c-rhodes/12ee674cbf0a9c86cbcb 
     */
    cout << endl << endl;
    for(int w = 0; w < 3; w++) {
        for(int x = 0; x < 3; x++) {
            cout << "\t";
            for(int y = 0; y < 3; y++) {
                for(int z = 0; z < 3; z++) {
                    Piece player = _boards[w][y]._board[x][z];
                    char playerStr;
                    if(player == TTTS_O) 
                        playerStr = 'O';
                    else if(player == TTTS_X)
                        playerStr = 'X';
                    else
                        playerStr = '_';
                    cout << playerStr << " ";
                }
                cout << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl << endl;
}

Status UltimateTicTacToe::update()
{
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) { 
            _boardStatuses[x][y] = _boards[x][y].update();
        }
    }

    bool tie = true;
    /* check for a tie */
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(_boardStatuses[i][j] == NONE)
                tie = false;

    if(tie)
        return TIE;

    /* DIAGONALS */
    /* top-left to bottom-right */
    if(_boardStatuses[0][0] != NONE &&
       _boardStatuses[0][0] == _boardStatuses[1][1] && 
       _boardStatuses[1][1] == _boardStatuses[2][2]) 
        return getTurn() == 'X' ? X : O;
    
    /* top-right to bottom-left */
    if(_boardStatuses[0][2] != NONE &&
       _boardStatuses[0][2] == _boardStatuses[1][1] && 
       _boardStatuses[1][1] == _boardStatuses[2][0]) 
        return getTurn() == 'X' ? X : O;
    
    bool match;
    /* COLUMNS */
    for(int row = 0; row < 3; row++)
    {
        match = true;
        for(int column = 0; column < 3 - 1; column++)
        {
            if(_boardStatuses[column][row] == NONE || _boardStatuses[column][row] != _boardStatuses[column+1][row])
            {
                match = false;
                break;
            }
        }
        if(match)
            return getTurn() == 'X' ? X : O;
    }
    match = true; // match is false set it true for next check
    /* END COLUMNS */
    
    /* ROWS */
    for(int row = 0; row < 3; row++)
    {
        match = true;
        for(int column = 0; column < 3 - 1; column++)
        {
            if(_boardStatuses[row][column] == NONE || _boardStatuses[row][column] != _boardStatuses[row][column+1])
            {
                match = false;
                break;
            }
        }
        if(match)
            return getTurn() == 'X' ? X : O;
    }
    /* END ROWS */
    
    setTurn(); // change player
    return NONE; 
}

int main()
{
    UltimateTicTacToe board; 
    
    board.displayBoards();
    
    int board_no;
    cout << "Enter the board number to start with: ";
    cin >> board_no;
    board.setBoardNo(board_no-1); // minus 1 for zero-based indexing

    int cell;
    bool playing = true;
    while(playing)
    {
        cout << "Player " << board.getTurn() << " select cell" << endl;
        cout << "cell: ";
        cin >> cell;
        board.move(cell);
        board.displayBoards();
        int status = board.update();
 
        switch(status)
        {
            case X:
                cout << "X has won!" << endl;
                playing = false;
                break;
            case O:
                cout << "O has won!" << endl;
                playing = false;
                break;
            case TIE:
                cout << "Game over. Tie" << endl;
                playing = false;
                break;
            default:
                break;
        }    
        if(board.boardFinished())
            board.selectNewBoard();
    }
}
