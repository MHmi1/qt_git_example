#include "bishop.h"

Bishop::Bishop(Color c) :Piece(BISHOP,c)
{
score = 8;
}

 bool Bishop::isValidMove() const
{

}

 void Bishop::set_image(QString address)
 {
     img_addr = address;
 }
 QString Bishop::get_img(Color c)
 {
     if (c==BLACK)
     {
         return ":/black/Black/b-bishop.png";
     }
     else if (c == WHITE)
     {
         return ":/white/White/w-bishop.png";
     }
 }
