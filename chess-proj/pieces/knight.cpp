#include "knight.h"
extern Tile *tile[8][8];
extern int exp[60],max,wR,wC;
Knight::Knight(Color c) :Chessman(KNIGHT,c)
{
score = 8;
}
int knight_threats=0;
void Knight::cal_threat(const Tile * foe) const
{
    qDebug()<<"in knight::cal_threat "<<endl;
    if  (foe->pieceName == 'Q')
    {
      knight_threats+=5;
    }
    else if  (foe->pieceName == 'H')
    {
        knight_threats+=2;
    }
   else if  (foe->pieceName == 'R')
    {
       knight_threats+=2;
    }
    else if  (foe->pieceName == 'B')
     {
          knight_threats+=2;
     }
    else if (foe->pieceName == 'P')
    {
           knight_threats+=1;
    }
}

bool Knight::isValidMove(Tile * temp) const
{
    knight_threats=0;
    int r, c;
    bool retVal = 0;

    r = temp->row;
    c = temp->col;

    if (r - 2 >= 0 && c - 1 >= 0)
    {
        if ((tile[r - 2][c - 1]->pieceColor != temp->pieceColor || !tile[r - 2][c - 1]->piece) /*  */)
        {
            exp[max++] = tile[r - 2][c - 1]->tileNum;
            retVal = 1;
            if (tile[r - 2][c - 1]->piece){this->cal_threat(tile[r-2][c-1]);}
            //qDebug()<<"there 1 "<<endl;

        }
    }

    if (r - 2 >= 0 && c + 1 <= 7)
    {
        if ((tile[r - 2][c + 1]->pieceColor != temp->pieceColor || !tile[r - 2][c + 1]->piece)&& tile[r-2][c+1]->pieceName !='K')
        {
            exp[max++] = tile[r - 2][c + 1]->tileNum;
             retVal = 1;
            if (tile[r-2][c+1]->piece){this->cal_threat(tile[r-2][c+1]);}

        }
    }

    if (r - 1 >= 0 && c - 2 >= 0)
    {
        if ((tile[r - 1][c - 2]->pieceColor != temp->pieceColor || !tile[r - 1][c - 2]->piece)&& tile[r-1][c-2]->pieceName !='K')
        {
            exp[max++] = tile[r - 1][c - 2]->tileNum;
             retVal = 1;
            if (tile[r-1][c-2]->piece) {this->cal_threat(tile[r-1][c-2]);}
            //qDebug()<<"there 2 "<<endl;

        }
    }

    if (r - 1 >= 0 && c + 2 <= 7)
    {
        if ((tile[r - 1][c + 2]->pieceColor != temp->pieceColor || !tile[r - 1][c + 2]->piece)&& tile[r-1][c+2]->pieceName !='K')
        {
            exp[max++] = tile[r - 1][c + 2]->tileNum;
            retVal = 1;
            if (tile[r-1][c+2]->piece){ this->cal_threat(tile[r-1][c+2]);}
            //qDebug()<<"there 3 "<<endl;

        }
    }

    if (r + 2 <= 7 && c + 1 <= 7)
    {
        if ((tile[r + 2][c + 1]->pieceColor != temp->pieceColor || !tile[r + 2][c + 1]->piece) && tile[r+2][c+1]->pieceName !='K')
        {
            exp[max++] = tile[r + 2][c + 1]->tileNum;
             retVal = 1;
            if (tile[r+2][c+1]->piece){this->cal_threat(tile[r+2][c+1]);}
            //qDebug()<<"there 4 "<<endl;

        }
    }

    if (r + 2 <= 7 && c - 1 >= 0)
    {
        if ((tile[r + 2][c - 1]->pieceColor != temp->pieceColor || !tile[r + 2][c - 1]->piece)&& tile[r+2][c-1]->pieceName !='K')
        {
            exp[max++] = tile[r + 2][c - 1]->tileNum;           
            //qDebug()<<"there 5 "<<endl;
            retVal = 1;
            if (tile[r+2][c-1]->piece) {this->cal_threat(tile[r+2][c-1]);}

        }
    }

    if (r + 1 <= 7 && c - 2 >= 0)
    {
        if ((tile[r + 1][c - 2]->pieceColor != temp->pieceColor || !tile[r + 1][c - 2]->piece)&& tile[r+1][c-2]->pieceName !='K')
        {
            exp[max++] = tile[r + 1][c - 2]->tileNum;

            //qDebug()<<"there 6 "<<endl;
            retVal = 1;
            if (tile[r+1][c-2]->piece) { this->cal_threat(tile[r+1][c-2]);}
        }
    }

    if (r + 1 <= 7 && c + 2 <= 7)
    {
        if ((tile[r + 1][c + 2]->pieceColor != temp->pieceColor || !tile[r + 1][c + 2]->piece)&& tile[r+1][c+2]->pieceName !='K')
        {
            exp[max++] = tile[r + 1][c + 2]->tileNum;
            retVal = 1;
            if (tile[r+1][c+2]->piece){ this->cal_threat(tile[r+1][c+2]);}
        }
    }
    return retVal;
}

void Knight::set_image(QString address){
img_addr = address;
}
QString Knight::get_img(){

    if (color==BLACK)
    {
        return ":/black/Black/b-knight.svg";
    }
    else if (color == WHITE)
    {
        return ":/white/White/w-knight.svg";
    }
}
