//
//  piece.hpp
//  Chess
//
//  Created by Ethan Quinn on 3/11/23.
//
#ifndef piece_hpp
#define piece_hpp

#include <string>

namespace Pieces
{
    class Piece
    {
        public:
            Piece();
            Piece(std::string type, std::string color);
            std::string getPieceType() const;
            std::string getPieceColor() const;
            void setEmpty();
        private:
            std::string type;
            std::string color;
    };
}
#endif /* piece_hpp */
