#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const override;
    ~Knight() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img(Color) override;

};

#endif // KNIGHT_H
