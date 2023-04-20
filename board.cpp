//
//  board.cpp
//  Chess
//
//  Created by Ethan Quinn on 3/11/23.
//

#include "board.hpp"

namespace Boards
{
    Board::Board()
    {
        Pieces::Piece whiteRook("rook", "white");
        board[0][0] = whiteRook;
        board[0][7] = whiteRook;
        Pieces::Piece whiteKnight("knight", "white");
        board[0][1] = whiteKnight;
        board[0][6] = whiteKnight;
        Pieces::Piece whiteBishop("bishop", "white");
        board[0][2] = whiteBishop;
        board[0][5] = whiteBishop;
        Pieces::Piece whiteQueen("queen", "white");
        board[0][3] = whiteQueen;
        Pieces::Piece whiteKing("king", "white");
        board[0][4] =  whiteKing;
        Pieces::Piece whitePawn("pawn", "white");
        for(int i = 0; i < 8; i++)
            board[1][i] = whitePawn;
        
        Pieces::Piece blackRook("rook", "black");
        board[7][0] = blackRook;
        board[7][7] = blackRook;
        Pieces::Piece blackKnight("knight", "black");
        board[7][1] = blackKnight;
        board[7][6] = blackKnight;
        Pieces::Piece blackBishop("bishop", "black");
        board[7][2] = blackBishop;
        board[7][5] = blackBishop;
        Pieces::Piece blackQueen("queen", "black");
        board[7][3] = blackQueen;
        Pieces::Piece blackKing("king", "black");
        board[7][4] =  blackKing;
        Pieces::Piece blackPawn("pawn", "black");
        for(int i = 0; i < 8; i++)
            board[6][i] = blackPawn;
        
        Pieces::Piece empty("", "");
        for(int i = 2; i < 6; i++)
            for(int j = 0; j < 8; j++)
                board[i][j] = empty;
    }
    void Board::printBoard()
    {
        std::cout << "   x: 1  2  3  4  5  6  7  8 " << std::endl << "y:" << std::endl;
        for (int i = 7; i >= 0; i--)
        {
            std::cout << " " << i + 1 << "   ";
            for (int j = 0; j < 8; j++)
            {
                std::string type = board[i][j].getPieceType();
                std::string color = board[i][j].getPieceColor();
                
                if(type == "king")
                    (color == "white") ? std::cout << " K " : std::cout << " k ";
                else if(type == "queen")
                    (color == "white") ? std::cout << " Q " : std::cout << " q ";
                else if(type == "bishop")
                    (color == "white") ? std::cout << " B " : std::cout << " b ";
                else if(type == "knight")
                    (color == "white") ? std::cout << " N " : std::cout << " n ";
                else if(type == "rook")
                    (color == "white") ? std::cout << " R " : std::cout << " r ";
                else if(type == "pawn")
                    (color == "white") ? std::cout << " P " : std::cout << " p ";
                else
                    std::cout << "   ";
            }
            std::cout << std::endl;
        }
    }
    void Board::movePiece(int x1, int y1, int x2, int y2)
    {
        if(verifyMove(x1, y1, x2, y2) && !verifyChecks(x1, y1, x2, y2, "white"))
        {
            std::cout << "Valid move" << std::endl;
            board[y2][x2] = board[y1][x1];
            board[y1][x1].setEmpty();
        }
        else
            std::cout << "Invalid move" << std::endl;
    }
    bool Board::verifyMove(int x1, int y1, int x2, int y2)
    {
        if(board[y1][x1].getPieceType() == "pawn")
        {
            if(x1 != x2)
            {
                if(board[y1][x1].getPieceColor() == "white")
                {
                    if(std::abs(x2 - x1) == 1 && y2 - y1 == 1 && board[y2][x2].getPieceColor() == "black" && y2 <= 7)
                        return true;
                    else
                        return false;
                }
                else
                {
                    if(std::abs(x2 - x1) == 1 && y2 - y1 == -1 && board[y2][x2].getPieceColor() == "white" && y2 >= 0)
                        return true;
                    else
                        return false;
                }
            }
            else
            {
                if(board[y1][x1].getPieceColor() == "white")
                {
                    if((y2 - y1 == 2 || y2 - y1 == 1) && board[y2][x2].getPieceType() == "" && y1 == 1 && y2 <= 7)
                        return true;
                    else if(y2 - y1 == 1 && board[y2][x2].getPieceType() == "" && y2 <= 7)
                        return true;
                    else
                        return false;
                }
                else
                {
                    if((y2 - y1 == -2 || y2 - y1 == -1) && board[y2][x2].getPieceType() == "" && y1 == 6 && y2 >= 0)
                        return true;
                    else if(y2 - y1 == -1 && board[y2][x2].getPieceType() == "" && y2 >= 0)
                        return true;
                    else
                        return false;
                }
            }
        }
        else if(board[y1][x1].getPieceType() == "knight")
        {
            if(board[y2][x2].getPieceColor() == board[y1][x1].getPieceColor() || x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8)
                return false;
            else if((std::abs(x2 - x1) == 2 && std::abs(y2 - y1) == 1) || (std::abs(x2 - x1) == 1 && std::abs(y2 - y1) == 2))
                return true;
        }
        else if(board[y1][x1].getPieceType() == "bishop")
        {
            if(abs(x2 - x1) != abs(y2 - y1) || x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8 || board[y2][x2].getPieceColor() == board[y1][x1].getPieceColor())
                return false;
            else
            {
                int dx = (x2 - x1 > 0) ? 1 : -1;
                int dy = (y2 - y1 > 0) ? 1 : -1;
                for(int i = 0; i < abs(x2 - x1 - 1); i++)
                {
                    if(board[y1 + dy][x1 + dx].getPieceType() != "")
                        return false;
                    dx += dx;
                    dy += dy;
                }
                return true;
            }
        }
        else if(board[y1][x1].getPieceType() == "rook")
        {
            if((x2 != x1 && y2 != y1) || x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8 || board[y2][x2].getPieceColor() == board[y1][x1].getPieceColor())
                return false;
            else
            {
                if(x2 == x1)
                {
                    int dy = (y2 - y1 > 0) ? 1 : -1;
                    int dx = 0;
                    for(int i = 0; i < abs(y2 - y1 - 1); i++)
                    {
                        if(board[y1 + dy][x1 + dx].getPieceType() != "")
                            return false;
                        dy += dy;
                    }
                }
                else if(y2 == y1)
                {
                    int dx = (x2 - x1 > 0) ? 1 : -1;
                    int dy = 0;
                    for(int i = 0; i < abs(x2 - x1 - 1); i++)
                    {
                        if(board[y1 + dy][x1 + dx].getPieceType() != "")
                            return false;
                        dx += dx;
                    }
                }
                return true;
            }
        }
        else if(board[y1][x1].getPieceType() == "queen")
        {
            if(x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8 || board[y2][x2].getPieceColor() == board[y1][x1].getPieceColor())
                return false;
            else if(x1 == x2 || y1 == y2)
            {
                if(x2 == x1)
                {
                    int dy = (y2 - y1 > 0) ? 1 : -1;
                    int dx = 0;
                    for(int i = 0; i < abs(y2 - y1 - 1); i++)
                    {
                        if(board[y1 + dy][x1 + dx].getPieceType() != "")
                            return false;
                        dy += dy;
                    }
                }
                else if(y2 == y1)
                {
                    int dx = (x2 - x1 > 0) ? 1 : -1;
                    int dy = 0;
                    for(int i = 0; i < abs(x2 - x1 - 1); i++)
                    {
                        if(board[y1 + dy][x1 + dx].getPieceType() != "")
                            return false;
                        dx += dx;
                    }
                }
            }
            else if(abs(x2 - x1) == abs(y2 - y1))
            {
                int dx = (x2 - x1 > 0) ? 1 : -1;
                int dy = (y2 - y1 > 0) ? 1 : -1;
                for(int i = 0; i < abs(x2 - x1 - 1); i++)
                {
                    if(board[y1 + dy][x1 + dx].getPieceType() != "")
                        return false;
                    dx += dx;
                    dy += dy;
                }
            }
            return true;
        }
        else if(board[y1][x1].getPieceType() == "king")
        {
            if(abs(x2 - x1) > 1 || abs(y2 - y1) > 1 || x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8)
                return false;
            else
                return true;
        }
        return false;
    }
    bool Board::verifyChecks(int x1, int y1, int x2, int y2, std::string color)
    {
        int kingX, kingY;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(board[i][j].getPieceType() == "king" && board[i][j].getPieceColor() == color)
                {
                    kingX = j;
                    kingY = i;
                }
            }
        }
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(board[i][j].getPieceType() == "pawn" && board[i][j].getPieceColor() != color)
                {
                    int dy = (color == "white") ? 1 : -1;
                    if((j - 1 == kingX || j + 1 == kingX) && i + dy == kingY)
                        return true;
                }
                if(board[i][j].getPieceType() == "knight" && board[i][j].getPieceColor() != color)
                {
                    if((j + 2 == kingX && (i + 2 == kingY || i - 2 == kingY))
                       || (j - 2 == kingX && (i + 2 == kingY || i - 2 == kingY))
                       || (i + 2 == kingY && (j + 2 == kingX || j - 2 == kingX))
                       || (i - 2 == kingY && (j + 2 == kingX || j - 2 == kingX)))
                        return true;
                }
                if(board[i][j].getPieceType() == "bishop" && board[i][j].getPieceColor() != color)
                {
                    for(int tempX = i + 1, tempY = j + 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX++, tempY++)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i - 1, tempY = j - 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX--, tempY--)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i + 1, tempY = j - 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX++, tempY--)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i - 1, tempY = j + 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX--, tempY++)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                }
                if(board[i][j].getPieceType() == "rook" && board[i][j].getPieceColor() != color)
                {
                    for(int tempX = i + 1; tempX <= 7 && tempX >= 0; tempX++)
                    {
                        if(board[j][tempX].getPieceType() == "king")
                            return true;
                        else if(board[j][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i - 1; tempX <= 7 && tempX >= 0; tempX--)
                    {
                        if(board[j][tempX].getPieceType() == "king")
                            return true;
                        else if(board[j][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempY = j + 1; tempY <= 7 && tempY >= 0; tempY++)
                    {
                        if(board[tempY][i].getPieceType() == "king")
                            return true;
                        else if(board[tempY][i].getPieceType() != "")
                            break;
                    }
                    for(int tempY = j - 1; tempY <= 7 && tempY >= 0; tempY--)
                    {
                        if(board[tempY][i].getPieceType() == "king")
                            return true;
                        else if(board[tempY][i].getPieceType() != "")
                            break;
                    }
                }
                if(board[i][j].getPieceType() == "queen" && board[i][j].getPieceColor() != color)
                {
                    for(int tempX = i + 1, tempY = j + 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX++, tempY++)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i - 1, tempY = j - 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX--, tempY--)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i + 1, tempY = j - 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX++, tempY--)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i - 1, tempY = j + 1; tempX <= 7 && tempX >= 0 && tempY <= 7 && tempY >= 0; tempX--, tempY++)
                    {
                        if(board[tempY][tempX].getPieceType() == "king")
                            return true;
                        else if(board[tempY][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i + 1; tempX <= 7 && tempX >= 0; tempX++)
                    {
                        if(board[j][tempX].getPieceType() == "king")
                            return true;
                        else if(board[j][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempX = i - 1; tempX <= 7 && tempX >= 0; tempX--)
                    {
                        if(board[j][tempX].getPieceType() == "king")
                            return true;
                        else if(board[j][tempX].getPieceType() != "")
                            break;
                    }
                    for(int tempY = j + 1; tempY <= 7 && tempY >= 0; tempY++)
                    {
                        if(board[tempY][i].getPieceType() == "king")
                            return true;
                        else if(board[tempY][i].getPieceType() != "")
                            break;
                    }
                    for(int tempY = j - 1; tempY <= 7 && tempY >= 0; tempY--)
                    {
                        if(board[tempY][i].getPieceType() == "king")
                            return true;
                        else if(board[tempY][i].getPieceType() != "")
                            break;
                    }
                }
            }
        }
        return false;
    }
}
