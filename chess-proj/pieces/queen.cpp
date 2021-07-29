#include "queen.h"

Queen::Queen(Color c) :Piece(QUEEN,c)
{
score = 15;
}

bool Queen::isValidMove() const
{

}

void Queen::set_image(QString address){
img_addr = address;
}
QString Queen::get_img(Color c){

    if (c==BLACK)
    {
        return ":/black/Black/b-queen.png";
    }
    else if (c == WHITE)
    {
        return ":/white/White/w-queen.png";
    }

}
