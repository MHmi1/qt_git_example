#include "Piece.h"
#include <QDebug>
Piece::Piece(Type t, Color c)
{
    type = t;
    color = c;

    if (t == ROOK)
        score = 5;

    else if (t ==QUEEN)
  score = 9;

    else if (t == BISHOP)
  score = 3;

    else if (t == KNIGHT)
  score = 3;

    else if (t == PAWN)
  score = 1;

    else if (t == KING)
  score = 0;
}


Color Piece::getColor() const
{
    return color;
}

void Piece::setColor(Color color)
{
    Piece::color = color;
}

Type Piece::getType() const
{
    return type;
}

void Piece::setType(Type type)
{
    Piece::type = type;
}


char Piece::typeToChar(Type type) const
{
    switch(type)
    {
        case PAWN: return 'P';
        case KNIGHT: return 'N';
        case BISHOP: return 'B';
        case ROOK: return 'R';
        case QUEEN: return 'Q';
        case KING: return 'K';
        default: return ' ';
    }
}

char Piece::colorToChar(Color color) const
{
    switch(color)
    {
        case WHITE: return 'W';
        case BLACK: return 'B';
        default: return ' ';
    }
}

 void Piece::set_image(QString)
 {
     qDebug() <<"->error ! base function called ! "<<endl;
 }
QString Piece::get_img(Color)
{
    qDebug() <<"->error ! base function called ! "<<endl;
}

