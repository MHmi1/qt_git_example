#include "Piece.h"
#include <QDebug>
Chessman::Chessman(Type t, Color c)
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


Color Chessman::getColor() const
{
    return color;
}

void Chessman::setColor(Color color)
{
    Chessman::color = color;
}

Type Chessman::getType() const
{
    return type;
}

void Chessman::setType(Type type)
{
    Chessman::type = type;
}


 void Chessman::set_image(QString)
 {
     qDebug() <<"->error ! base function called ! "<<endl;
 }
QString Chessman::get_img()
{
    qDebug() <<"->error ! base function called ! "<<endl;
}

