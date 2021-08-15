#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Chessman  //inherited form chessman
{
public:
    Rook(Color);
    virtual bool isValidMove(Tile *) const override;
    ~Rook() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img() override;
    virtual void cal_threat(const Tile *)const override;
};

#endif // ROOK_H
