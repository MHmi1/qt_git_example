#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Chessman //inherited form chessman
{
public:
    Knight(Color);
    virtual bool isValidMove(Tile *) const override;
    ~Knight() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img() override;
    virtual void cal_threat(const Tile *)const override;

};

#endif // KNIGHT_H
