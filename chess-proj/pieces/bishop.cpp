#include "bishop.h"
extern Tile *tile[8][8];
extern int exp[60],max,wR,wC;
extern bool king_at_check;
Bishop::Bishop(Color c) :Chessman(BISHOP,c)
{
score = 8;
}
int bishop_threats=0;

void Bishop::cal_threat(const Tile * foe) const
{

    qDebug()<<"in Bishop::cal_threat "<<endl;
    if  (foe->pieceName == 'Q')
    {
      bishop_threats+=5;
    }
    else if  (foe->pieceName == 'H')
    {
        bishop_threats+=2;
    }
   else if  (foe->pieceName == 'R')
    {
       bishop_threats+=2;
    }
    else if  (foe->pieceName == 'B')
     {
          bishop_threats+=2;
     }
    else if (foe->pieceName == 'P')
    {
           bishop_threats+=1;
    }
    else if (foe->pieceName == 'K')
    {
           king_at_check=1;
    }

}
 bool Bishop::isValidMove(Tile * temp) const
{
      bishop_threats=0;
     int r,c;
     int retVal=0;

     r=temp->row;
     c=temp->col;
     while(r-->0 && c++<7) //orib south-east movement
     {
         if(!tile[r][c]->piece )
         {
             exp[max++]=tile[r][c]->tileNum;

             retVal=1;
         }

         else if(tile[r][c]->pieceColor==temp->pieceColor )
         {

             break;
         }
         else if(tile[r][c]->pieceColor!=temp->pieceColor)
         {
             if (tile[r][c]->pieceName !='K')
             {
                 exp[max++]=tile[r][c]->tileNum;
                  retVal=1;
             }
             if (tile[r][c]->piece){this->cal_threat(tile[r][c]);}
             break;
         }
     }

     r=temp->row;
     c=temp->col;
     while(r-->0 && c-->0) //orib south-west movement
     {
         if(!tile[r][c]->piece)
         {
             exp[max++]=tile[r][c]->tileNum;

             retVal=1;
         }

         else if(tile[r][c]->pieceColor==temp->pieceColor )
         {

              break;
         }

         else if(tile[r][c]->pieceColor!=temp->pieceColor )
         {
             if (tile[r][c]->pieceName !='K')
             {
                 exp[max++]=tile[r][c]->tileNum;
                  retVal=1;
             }

            if (tile[r][c]->piece){this->cal_threat(tile[r][c]);}


             break;
         }
     }

     r=temp->row;
     c=temp->col;
     while(r++<7 && c++<7) //orib north-east movement
     {
         if(!tile[r][c]->piece )
         {
             exp[max++]=tile[r][c]->tileNum;
            // qDebug()<<"there 7 "<<endl;
             retVal=1;
         }

         else if(tile[r][c]->pieceColor==temp->pieceColor)
         {
          //qDebug()<<"there 8 "<<endl;
            break;
         }
         else if(tile[r][c]->pieceColor!=temp->pieceColor)
         {
             if (tile[r][c]->pieceName !='K')
             {
                 exp[max++]=tile[r][c]->tileNum;
                  retVal=1;
             }
             if (tile[r][c]->piece){this->cal_threat(tile[r][c]);}


             break;
         }
     }

     r=temp->row;
     c=temp->col;
     while(r++<7 && c-->0) //orib north-west movement
     {
         if(!tile[r][c]->piece)
         {
             exp[max++]=tile[r][c]->tileNum;

             retVal=1;
         }

         else if(tile[r][c]->pieceColor==temp->pieceColor )
         {

              break;
         }

         else if(tile[r][c]->pieceColor!=temp->pieceColor )
         {
             if (tile[r][c]->pieceName !='K')
             {
                 exp[max++]=tile[r][c]->tileNum;
                  retVal=1;
             }
             if (tile[r][c]->piece){this->cal_threat(tile[r][c]);}
             break;
         }
     }
     return retVal;
}

 void Bishop::set_image(QString address)
 {
     img_addr = address;
 }
 QString Bishop::get_img()
 {
     if (color==BLACK)
     {
         return ":/black/Black/b-bishop.svg";
     }
     else if (color == WHITE)
     {
         return ":/white/White/w-bishop.svg";
     }
 }
