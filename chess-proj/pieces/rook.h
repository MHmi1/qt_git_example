#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const override;
    ~Rook() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img(Color) override;
};

#endif // ROOK_H
