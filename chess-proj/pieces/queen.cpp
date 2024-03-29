#include "queen.h"
extern Tile *tile[8][8];
extern int exp[60], max, wR, wC;
extern bool king_at_check;
Queen::Queen(Color c) : Chessman(QUEEN, c)
{
    score = 15;
}
int queen_threats = 0;

void Queen::cal_threat(const Tile *foe) const
{
    qDebug() << "in Queen::cal_threat " << endl;
    if (foe->pieceName == 'Q')
    {
        queen_threats += 5;
    }
    else if (foe->pieceName == 'H')
    {
        queen_threats += 2;
    }
    else if (foe->pieceName == 'R')
    {
        queen_threats += 2;
    }
    else if (foe->pieceName == 'B')
    {
        queen_threats += 2;
    }
    else if (foe->pieceName == 'P')
    {
        queen_threats += 1;
    }
    else if (foe->pieceName == 'K')
    {
           king_at_check=1;
    }
}
bool Queen::isValidMove(Tile *temp) const
{
    queen_threats = 0;

    int r, c;

    bool retVal = 0;

    r = temp->row;
    c = temp->col;
    while (r-- > 0) //south  movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }
            this->cal_threat(tile[r][c]);

            break;
        }
    }
    r = temp->row;
    c = temp->col;
    while (r++ < 7) //north movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }
            this->cal_threat(tile[r][c]);            
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (c++ < 7) //east movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }
            this->cal_threat(tile[r][c]);


            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (c-- > 0) //west movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }

            this->cal_threat(tile[r][c]);


            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r-- > 0 && c++ < 7) // south-east movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }
            this->cal_threat(tile[r][c]);


            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r-- > 0 && c-- > 0) // south-west movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }
            this->cal_threat(tile[r][c]);



            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r++ < 7 && c++ < 7) // north_east movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }

            this->cal_threat(tile[r][c]);


            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r++ < 7 && c-- > 0) // south-west movement
    {
        if (!tile[r][c]->piece)
        {
            exp[max++] = tile[r][c]->tileNum;
            retVal = 1;
        }

        else if (tile[r][c]->pieceColor == temp->pieceColor)
            break;

        else if (tile[r][c]->pieceColor != temp->pieceColor)
        {
            if (tile[r][c]->pieceName!='K')
            {
                retVal = 1;
                exp[max++] = tile[r][c]->tileNum;
            }

            this->cal_threat(tile[r][c]);           
            break;
        }
    }

    return retVal;
}

void Queen::set_image(QString address)
{
    img_addr = address;
}
QString Queen::get_img()
{

    if (color == BLACK)
    {
        return ":/black/Black/b-queen.svg";
    }
    else if (color == WHITE)
    {
        return ":/white/White/w-queen.svg";
    }
}
