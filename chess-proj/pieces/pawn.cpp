#include "pawn.h"
extern Tile *tile[8][8];
extern int exp[60], max, wR, wC;
extern QVector<QString> w_move_list, b_move_list;
extern size_t path_len(QString);
extern bool king_at_check;
int is_w1_anpasan = -1, is_w2_anpasan = -1, is_b1_anpasan = -1, is_b2_anpasan = -1;
Pawn::Pawn(Color c) : Chessman(PAWN, c)
{
    score = 3;
}
int pawn_threats = 0;
void Pawn::cal_threat(const Tile *foe) const
{

    qDebug() << "in pawn::cal_threat " << endl;
    if (foe->pieceName == 'Q')
    {
        pawn_threats += 5;
    }
    else if (foe->pieceName == 'H')
    {
        pawn_threats += 2;
    }
    else if (foe->pieceName == 'R')
    {
        pawn_threats += 2;
    }
    else if (foe->pieceName == 'B')
    {
        pawn_threats += 2;
    }
    else if (foe->pieceName == 'P')
    {
        pawn_threats += 1;
    }
    else if (foe->pieceName == 'K')
    {
           king_at_check=1;
    }
}

bool Pawn::isValidMove(Tile *temp) const
{
    pawn_threats = 0;
    int flag=0,flag1=0;
    int row, col;
    row = temp->row;
    col = temp->col;
    bool retVal = 0;

    //White Pawn
    if (temp->pieceColor)
    {
        if (row - 1 >= 0 && !tile[row - 1][col]->piece)
        { //white straight one move
            exp[max++] = tile[row - 1][col]->tileNum;

            retVal = 1;
        }

        if (row == 6 && !tile[5][col]->piece && !tile[4][col]->piece)
        { //white straight dual move
            exp[max++] = tile[row - 2][col]->tileNum;

            retVal = 1;
        }

        if (row - 1 >= 0 && col - 1 >= 0)
        { //white orib  move
            if (tile[row - 1][col - 1]->pieceColor != temp->pieceColor && tile[row - 1][col - 1]->piece && tile[row - 1][col - 1]->pieceName != 'K')
            {
                exp[max++] = tile[row - 1][col - 1]->tileNum;
                this->cal_threat(tile[row - 1][col - 1]);
                flag=1;
                retVal = 1;
            }
        }

        if (row - 1 >= 0 && col + 1 <= 7)
        { //white orib  move
            if (tile[row - 1][col + 1]->pieceColor != temp->pieceColor && tile[row - 1][col + 1]->piece && tile[row - 1][col + 1]->pieceName != 'K')
            {
                exp[max++] = tile[row - 1][col + 1]->tileNum;
               if (flag==0){ this->cal_threat(tile[row - 1][col + 1]);}
                retVal = 1;
            }
        }

        //---------------------------------------------
        if (row - 1 >= 0 && col - 1 >= 0)
        { //white orib  move anpasan

            if ((tile[row][col - 1]->pieceName == 'P' && tile[row][col - 1]->pieceColor == 0) && tile[row][col]->row == 3 && path_len(b_move_list.at(b_move_list.size() - 1)) == 2 && b_move_list.at(b_move_list.size() - 1).at(0) == 'P')
            {
               // qDebug() <<"black sol anapasan move :"<<  b_move_list.at(b_move_list.size() - 1) << endl;
                exp[max++] = tile[row - 1][col - 1]->tileNum;
                retVal = 1;
                is_w1_anpasan = col - 1;
            }
        }
        if (row - 1 >= 0 && col + 1 <= 7)
        { //white orib  move anpasan

            if ((tile[row][col + 1]->pieceName == 'P' && tile[row][col + 1]->pieceColor == 0) && tile[row][col]->row == 3 && path_len(b_move_list.at(b_move_list.size() - 1)) == 2 && b_move_list.at(b_move_list.size() - 1).at(0) == 'P')
            {
               // qDebug() <<"black sol anapasan move : "<< b_move_list.at(b_move_list.size() - 1) << endl;
                exp[max++] = tile[row - 1][col + 1]->tileNum;
                is_w2_anpasan = col + 1;
                retVal = 1;
            }
        }
        //-------------------------------------------------
    }

    else
    {
        if (row + 1 <= 7 && !tile[row + 1][col]->piece)
        { //black straight one move
            exp[max++] = tile[row + 1][col]->tileNum;

            retVal = 1;
        }

        if (row == 1 && !tile[2][col]->piece && !tile[3][col]->piece)
        { //black straight dual move
            exp[max++] = tile[row + 2][col]->tileNum;

            retVal = 1;
        }

        if (row + 1 <= 7 && col - 1 >= 0)
        { //black orib move
            if (tile[row + 1][col - 1]->pieceColor != temp->pieceColor && tile[row + 1][col - 1]->piece && tile[row + 1][col - 1]->pieceName != 'K')
            {
                exp[max++] = tile[row + 1][col - 1]->tileNum;
                this->cal_threat(tile[row + 1][col - 1]);
                flag1=1;
                retVal = 1;
            }
        }

        if (row + 1 <= 7 && col + 1 <= 7)
        { //black orib move
            if (tile[row + 1][col + 1]->pieceColor != temp->pieceColor && tile[row + 1][col + 1]->piece && tile[row + 1][col + 1]->pieceName != 'K')
            {
                exp[max++] = tile[row + 1][col + 1]->tileNum;
                if (flag1==0){this->cal_threat(tile[row + 1][col + 1]);}
                retVal = 1;
            }
        }

        //----------------------------------------------

        if (row + 1 <= 7 && col - 1 >= 0)
        { //black orib move anpasan
            if ((tile[row][col - 1]->pieceName == 'P' && tile[row][col - 1]->pieceColor == 1) && tile[row][col]->row == 4 && path_len(w_move_list.at(w_move_list.size() - 1)) == 2 && w_move_list.at(w_move_list.size() - 1).at(0) == 'P')
            {
               // qDebug() << w_move_list.at(w_move_list.size() - 1) << endl;

                exp[max++] = tile[row + 1][col - 1]->tileNum;

                is_b1_anpasan = col - 1;
                retVal = 1;
            }
        }

        if (row + 1 <= 7 && col + 1 <= 7)
        { //black orib move anpasan
            if ((tile[row][col + 1]->pieceName == 'P' && tile[row][col + 1]->pieceColor == 1) && tile[row][col]->row == 4 && path_len(w_move_list.at(w_move_list.size() - 1)) == 2 && w_move_list.at(w_move_list.size() - 1).at(0) == 'P')
            {
               // qDebug() <<"white sol anapasan move :"<<w_move_list.at(w_move_list.size() - 1) << endl;

                exp[max++] = tile[row +1][col + 1]->tileNum;

                is_b2_anpasan = col + 1;
                retVal = 1;
            }
        }

        //-------------------------------------
    }

    return retVal;
}

void Pawn::set_image(QString address)
{
    img_addr = address;
}

QString Pawn::get_img()
{
    if (color == BLACK)
    {
        return ":/black/Black/b-pawn.svg";
    }
    else if (color == WHITE)
    {
        return ":/white/White/w-pawn.svg";
    }
}
