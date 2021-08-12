#ifndef VALIDATION_H
#define VALIDATION_H
#include "cell.h"
#include "pieces/Piece.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

extern Tile *tile[8][8];
extern int exp[60],max,wR,wC;

class validation
{
    int flag,retVal;

public:
    validation();
    int chooser(Tile *temp);
    int validateBishop(Tile *temp);
    int validateQueen(Tile *temp);
    int validateKing(Tile *temp);
    int validateHorse(Tile *temp);
    int validateRook(Tile *temp);
    int validatePawn(Tile *temp);
    void orange();
    int check(Tile *temp);
};

#endif // VALIDATION_H
