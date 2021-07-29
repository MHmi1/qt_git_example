#include "king.h"

King::King( Color c) :Piece(KING,c)
{
score = 0;
}

bool King::isValidMove() const
{

}

void King::set_image(QString address){
img_addr = address;
}
QString King::get_img(Color c){

    if (c==BLACK)
    {
        return ":/black/Black/b-king.png";
    }
    else if (c == WHITE)
    {
        return ":/white/White/w-king.png";
    }

}
