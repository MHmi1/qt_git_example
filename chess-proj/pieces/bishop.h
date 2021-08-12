#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"
#include "cell.h"
class Bishop : public Chessman
{
public:
    Bishop(Color);
    virtual bool isValidMove(Tile *) const override;
    ~Bishop() override = default;
    virtual void set_image(QString) override;
    virtual QString get_img() override;
    virtual void cal_threat(const Tile *)const override;
};

#endif // BISHOP_H
