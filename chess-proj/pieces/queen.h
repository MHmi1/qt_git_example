#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Chessman
{
    public:
    Queen(Color);
    virtual bool isValidMove(Tile *) const override;
    ~Queen() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img() override;
    virtual void cal_threat(const Tile *)const override;
};

#endif // QUEEN_H
