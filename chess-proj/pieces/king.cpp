#include "king.h"
extern Tile *tile[8][8];
extern int exp[60],max,wR,wC;

extern QVector<QString> b_move_list;
extern QVector<QString> w_move_list;
King::King( Color c) :Chessman(KING,c)
{
score = 0;
}
int king_threats=0;
void King::cal_threat(const Tile * foe) const
{
    qDebug()<<"in king::cal_threat "<<endl;
    if  (foe->pieceName == 'Q')
    {
      king_threats+=5;
    }
    else if  (foe->pieceName == 'H')
    {
        king_threats+=2;
    }
   else if  (foe->pieceName == 'R')
    {
       king_threats+=2;
    }
    else if  (foe->pieceName == 'B')
     {
          king_threats+=2;
     }
    else if (foe->pieceName == 'P')
    {
           king_threats+=1;
    }
}

bool castling_possibility() //check king and rook has movement before
{
    bool flag =1;
    for (int i=0;i<b_move_list.size();i++)
    {
       if ( b_move_list.at(i).at(0) == 'K' || b_move_list.at(i).at(0) == 'R' )
       {
           flag = 0;
       }
    }
    for (int i=0;i<w_move_list.size();i++)
    {
        if ( w_move_list.at(i).at(0) == 'K' || w_move_list.at(i).at(0) == 'R' )
        {
            flag = 0;

        }
    }
    return flag;
}
bool King::isValidMove(Tile * temp) const
{
    king_threats=0;
    int r, c;
    bool retVal = 0;

    r = temp->row;
    c = temp->col;

    if (r - 1 >= 0)
    {
        if (!tile[r - 1][c]->piece || tile[r - 1][c]->pieceColor != temp->pieceColor && tile[r - 1][c]->pieceName != 'K')
        {  // north movement
            exp[max++] = tile[r - 1][c]->tileNum;
             if (tile[r - 1][c]->pieceColor != temp->pieceColor){    this->cal_threat(tile[r-1][c]);}
            retVal = 1;
        }
    }

    if (r + 1 <= 7)
    {
        if (!tile[r + 1][c]->piece || tile[r + 1][c]->pieceColor != temp->pieceColor && tile[r + 1][c]->pieceName != 'K')
        { // south movement
            exp[max++] = tile[r + 1][c]->tileNum;
              if (tile[r + 1][c]->pieceColor != temp->pieceColor){ this->cal_threat(tile[r+1][c]);}
            retVal = 1;
        }
    }

    if (c - 1 >= 0)
    {
        if (!tile[r][c - 1]->piece || tile[r][c - 1]->pieceColor != temp->pieceColor && tile[r][c-1]->pieceName != 'K')
        { // west movement
            exp[max++] = tile[r][c - 1]->tileNum;
           if (tile[r ][c-1]->pieceColor != temp->pieceColor){ this->cal_threat(tile[r][c-1]);}
            retVal = 1;
        }
    }
    //----------------------------------
    c = temp->col;
    if (c - 1 >= 0) //castling  west movement
    {
        if (!tile[r][c - 1]->piece)
        {
            if (!tile[r][c - 2]->piece)
            {
                   if (!tile[r][c - 3]->piece && tile[r][c-4]->pieceName =='R' && castling_possibility() == 1)
                   {
                       exp[max++] = tile[r][c-2]->tileNum;
                       retVal = 1;
                   }
            }

        }
    }

    //----------------------------------
    c = temp->col;
    if (c + 1 <= 7) //castling  esat movement
    {
        if (!tile[r][c +1]->piece)
        {
            if (!tile[r][c +2]->piece && tile[r][c+3]->pieceName =='R' && castling_possibility() == 1)
            {
                       exp[max++] = tile[r][c+2]->tileNum;

                       retVal = 1;
            }

        }
    }
     //----------------------------------

    if (c + 1 <= 7)
    {
        if (!tile[r][c + 1]->piece || tile[r][c + 1]->pieceColor != temp->pieceColor && tile[r][c+1]->pieceName != 'K')
        { // east movement
            exp[max++] = tile[r][c + 1]->tileNum;
           if (tile[r ][c+1]->pieceColor != temp->pieceColor){  this->cal_threat(tile[r][c+1]);}
            retVal = 1;
        }
    }

    if (r - 1 >= 0 && c - 1 >= 0)
    {
        if (!tile[r - 1][c - 1]->piece || tile[r - 1][c - 1]->pieceColor != temp->pieceColor && tile[r - 1][c-1]->pieceName != 'K')
        { //  north-west movment
            exp[max++] = tile[r - 1][c - 1]->tileNum;
                if (tile[r - 1][c-1]->pieceColor != temp->pieceColor){  this->cal_threat(tile[r-1][c-1]);}
            retVal = 1;
        }
    }

    if (r - 1 >= 0 && c + 1 <= 7)
    {
        if (!tile[r - 1][c + 1]->piece || tile[r - 1][c + 1]->pieceColor != temp->pieceColor && tile[r - 1][c+1]->pieceName != 'K')
        {  // north-esat movement
            exp[max++] = tile[r - 1][c + 1]->tileNum;
           if (tile[r - 1][c+1]->pieceColor != temp->pieceColor){  this->cal_threat(tile[r-1][c+1]);}
            retVal = 1;
        }
    }

    if (r + 1 <= 7 && c - 1 >= 0)
    {
        if (!tile[r + 1][c - 1]->piece || tile[r + 1][c - 1]->pieceColor != temp->pieceColor && tile[r + 1][c-1]->pieceName != 'K')
        {   // south-west movement
            exp[max++] = tile[r + 1][c - 1]->tileNum;
            if (tile[r + 1][c-1]->pieceColor != temp->pieceColor){ this->cal_threat(tile[r+1][c-1]);}

            retVal = 1;
        }
    }

    if (r + 1 <= 7 && c + 1 <= 7)
    {
        if (!tile[r + 1][c + 1]->piece || tile[r + 1][c + 1]->pieceColor != temp->pieceColor && tile[r + 1][c + 1]->pieceName != 'K')
        { // south-east movement
            exp[max++] = tile[r + 1][c + 1]->tileNum;
            if (tile[r + 1][c+1]->pieceColor != temp->pieceColor){ this->cal_threat(tile[r+1][c+1]);}
            retVal = 1;
        }
    }

    return retVal;
}

void King::set_image(QString address){
img_addr = address;
}
QString King::get_img(){

    if (color==BLACK)
    {
        return ":/black/Black/b-king.svg";
    }
    else if (color == WHITE)
    {
        return ":/white/White/w-king.svg";
    }

}
