#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Chessman
{
public:
    King(Color);
    virtual bool isValidMove(Tile *) const override;
    ~King() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img() override;
    virtual void cal_threat(const Tile *)const override;
};

#endif // KING_H
