#include "pawn.h"

Pawn::Pawn(Color c) :Piece(PAWN,c)
{
score = 3;
}

bool Pawn::isValidMove() const
{

}

void Pawn::set_image(QString address){
img_addr = address;
}
QString Pawn::get_img(Color c){
    if (c==BLACK)
    {
        return ":/black/Black/b-pawn.png";
    }
    else if (c == WHITE)
    {
        return ":/white/White/w-pawn.png";
    }
}
