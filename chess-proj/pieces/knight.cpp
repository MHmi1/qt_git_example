#include "knight.h"

Knight::Knight(Color c) :Piece(KNIGHT,c)
{
score = 8;
}

bool Knight::isValidMove() const
{

}

void Knight::set_image(QString address){
img_addr = address;
}
QString Knight::get_img(Color c){

    if (c==BLACK)
    {
        return ":/black/Black/b-knight.png";
    }
    else if (c == WHITE)
    {
        return ":/white/White/w-knight.png";
    }
}
