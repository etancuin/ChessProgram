//
//  piece.cpp
//  Chess
//
//  Created by Ethan Quinn on 3/11/23.
//

#include "piece.hpp"
namespace Pieces
{
    Piece::Piece()
    {
        type = "";
        color = "";
    }
    Piece::Piece(std::string type, std::string color)
    {
        this->type = type;
        this->color = color;
    }
    std::string Piece::getPieceType() const
    {
        return type;
    }
    std::string Piece::getPieceColor() const
    {
        return color;
    }
    void Piece::setEmpty()
    {
        type = "";
        color = "";
    }
}
