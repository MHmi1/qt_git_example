#include "rook.h"
extern Tile *tile[8][8];
extern int exp[60],max,wR,wC;
extern bool king_at_check;
Rook::Rook(Color c) :Chessman(ROOK,c)
{
score = 8;
}

int rook_threats=0;
void Rook::cal_threat(const Tile * foe) const
{
    qDebug()<<"in rook::cal_threat "<<endl;
    if  (foe->pieceName == 'Q')
    {
      rook_threats+=5;
    }
    else if  (foe->pieceName == 'H')
    {
        rook_threats+=2;
    }
   else if  (foe->pieceName == 'R')
    {
       rook_threats+=2;
    }
    else if  (foe->pieceName == 'B')
     {
          rook_threats+=2;
     }
    else if (foe->pieceName == 'P')
    {
         rook_threats+=1;
    }
    else if (foe->pieceName == 'K')
    {
           king_at_check=1;
    }

}

bool Rook::isValidMove(Tile * temp) const
{
    rook_threats=0;

        int r, c;

        bool retVal = 0;

        r = temp->row;
        c = temp->col;
        while (r-- > 0 )
        {
            if (!tile[r][c]->piece)
            {  //south movement
                exp[max++] = tile[r][c]->tileNum;

                retVal = 1;
            }

            else if (tile[r][c]->pieceColor == temp->pieceColor )

                break;

            else if (tile[r][c]->pieceColor != temp->pieceColor )
            { //enemy in view of white peiece
                if (tile[r][c]->pieceName != 'K')
                {
                exp[max++] = tile[r][c]->tileNum;
                retVal = 1;
                }
                 this->cal_threat(tile[r][c]);
                retVal = 1;
                break;
            }
        }

        r = temp->row;
        c = temp->col;
        while (r++ < 7 )
        {
            if (!tile[r][c]->piece)
            {  //north movment
                exp[max++] = tile[r][c]->tileNum;

                retVal = 1;
            }

            else if (tile[r][c]->pieceColor == temp->pieceColor )
                break;

            else if (tile[r][c]->pieceColor != temp->pieceColor)
            { //enemy in view of black peiece
                if (tile[r][c]->pieceName != 'K')
                {
                exp[max++] = tile[r][c]->tileNum;
                retVal = 1;
                }
                 this->cal_threat(tile[r][c]);

                break;
            }
        }

        r = temp->row;
        c = temp->col;
        while (c++ < 7)
        {
            if (!tile[r][c]->piece )
            { //east movement
                exp[max++] = tile[r][c]->tileNum;
                retVal = 1;
            }
            else if (tile[r][c]->pieceColor == temp->pieceColor )
                break;

            else if (tile[r][c]->pieceColor != temp->pieceColor)
            {  //****
                if (tile[r][c]->pieceName != 'K')
                {
                exp[max++] = tile[r][c]->tileNum;
                retVal = 1;
                }
                   this->cal_threat(tile[r][c]);

                break;
            }
        }

        r = temp->row;
        c = temp->col;
        while (c-- > 0 )
        {
            if (!tile[r][c]->piece )
            {  //west movement
                exp[max++] = tile[r][c]->tileNum;

                retVal = 1;
            }

            else if (tile[r][c]->pieceColor == temp->pieceColor )
                break;

            else if (tile[r][c]->pieceColor != temp->pieceColor )
            {  //****
                if (tile[r][c]->pieceName != 'K')
                {
                exp[max++] = tile[r][c]->tileNum;
                retVal = 1;
                }
                 this->cal_threat(tile[r][c]);
                break;
            }
        }
        return retVal;

}


void Rook::set_image(QString address){
img_addr = address;
}

QString Rook::get_img(){
if (color==BLACK)
{
    return ":/black/Black/b-rook.svg";
}
else if (color == WHITE)
{
    return ":/white/White/w-rook.svg";
}

}
