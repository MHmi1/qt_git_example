#include "queen.h"
extern Tile *tile[8][8];
extern int exp[60], max, wR, wC;
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
}
bool Queen::isValidMove(Tile *temp) const
{
    queen_threats = 0;

    int r, c;

    bool retVal = 0;

    r = temp->row;
    c = temp->col;
    while (r-- > 0)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r++ < 7)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (c++ < 7)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (c-- > 0)
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
            exp[max++] = tile[r][c]->tileNum;

            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r-- > 0 && c++ < 7)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r-- > 0 && c-- > 0)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r++ < 7 && c++ < 7)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
            break;
        }
    }

    r = temp->row;
    c = temp->col;
    while (r++ < 7 && c-- > 0)
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
            exp[max++] = tile[r][c]->tileNum;
            this->cal_threat(tile[r][c]);
            retVal = 1;
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
