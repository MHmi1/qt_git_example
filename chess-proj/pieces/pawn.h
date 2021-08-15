#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Chessman //inherited form chessman
{
public:
    Pawn(Color);
    virtual bool isValidMove(Tile *) const override;
    ~Pawn() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img() override;
    virtual void cal_threat(const Tile *)const override;
};

#endif // PAWN_H
