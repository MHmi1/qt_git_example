#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece
{
public:
    King(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const override;
    ~King() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img(Color) override;
};

#endif // KING_H
