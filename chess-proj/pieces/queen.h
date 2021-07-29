#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece
{
    public:
    Queen(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const override;
    ~Queen() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img(Color) override;
};

#endif // QUEEN_H
