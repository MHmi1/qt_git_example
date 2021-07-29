#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const override;
    ~Bishop() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img(Color) override;

};

#endif // BISHOP_H
