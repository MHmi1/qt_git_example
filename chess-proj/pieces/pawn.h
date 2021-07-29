#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const override;
    ~Pawn() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img(Color) override;
};

#endif // PAWN_H
