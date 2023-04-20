//
//  board.hpp
//  Chess
//
//  Created by Ethan Quinn on 3/11/23.
//

#ifndef board_hpp
#define board_hpp

#include "piece.hpp"
#include <vector>
#include <iostream>

namespace Boards
{
    class Board
    {
        public:
            Board();
            void movePiece(int x1, int y1, int x2, int y2);
            void printBoard();
            bool verifyMove(int x1, int y1, int x2, int y2);
            bool verifyChecks(int x1, int y1, int x2, int y2, std::string color);
        private:
            Pieces::Piece board[8][8];
            std::vector<std::string> moveList;
            bool check;
    };
}

#endif /* board_hpp */
