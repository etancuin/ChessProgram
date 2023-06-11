//  main.cpp
//  Chess
//
//  Created by Ethan on 3/11/23.
//  To be completed at a later date...

#include <iomanip>
#include "board.hpp"
//#include <SFML/Graphics.hpp>

int main() {
    Boards::Board newGame;
    int x1, y1, x2, y2;
    
    do
    {
        newGame.printBoard();
        std::cout << std::endl << std::setfill('-') << std::setw(30) << "" << std::endl;
        std::cin >> x1 >> y1 >> x2 >> y2;
        newGame.movePiece(x1 - 1, y1 - 1, x2 - 1, y2 - 1);
    }
    while(x1 != -1);
    
    return 0;
}

//add castling
//add en passant
//verying move isn't self check
//see if move checks opponent
