#include "rook.h"


Rook::Rook(Color c) :Piece(ROOK,c)
{
score = 8;
}

bool Rook::isValidMove() const
{

}


void Rook::set_image(QString address){
img_addr = address;
}

QString Rook::get_img(Color c){
if (c==BLACK)
{
    return ":/black/Black/b-rook.png";
}
else if (c == WHITE)
{
    return ":/white/White/w-rook.png";
}
}
