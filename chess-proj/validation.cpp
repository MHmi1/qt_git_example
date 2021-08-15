#include "validation.h"
#include <memory>

validation::validation()
{
    //Nothing here
}

int validation::chooser(Tile *temp)
{
    switch (temp->pieceName)
    {
    case 'P':
    {
        std::unique_ptr<Pawn> p(new Pawn(BLACK));
        flag =  p->isValidMove(temp);
        break;
     }
    case 'R':
    {
        std::unique_ptr<Rook> r(new Rook(BLACK));
        flag = r->isValidMove(temp);
        break;
}
    case 'H':
    {
         std::unique_ptr<Knight> h(new Knight(BLACK));
        flag = h->isValidMove(temp);
        break;
     }
    case 'K':
    {
         std::unique_ptr<King> k(new King(BLACK));
        flag = k->isValidMove(temp);
        break;
    }

    case 'Q':
    {
       std::unique_ptr<Queen> q (new Queen(BLACK));
        flag = q->isValidMove(temp);
        break;
      }
    case 'B':
    {
       std::unique_ptr<Bishop> b (new Bishop(BLACK));
        flag = b->isValidMove(temp);
        break;
    }
    }

    orange();
    return flag;
}

int validation::check(Tile *temp)
{
    int r, c, flag;
    retVal = 0;

    return retVal;
}

void validation::orange() //Paint possible moves of each peice
{
    int i, n;

    for (i = 0; i < max; i++)
        tile[exp[i] / 8][exp[i] % 8]->setStyleSheet("QLabel {background-color: #e4b824;}");//orange
}
