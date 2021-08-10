#ifndef CHESSMAN_H
#define CHESSMAN_H
#include <QString>
#include <vector>
#include "cell.h"
using std::vector;
enum Type
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};
enum Color
{
    WHITE,
    BLACK
};
class Chessman
{
public:
    // Constructor
    Chessman(Type, Color);
    void setColor(Color color);
    void setType(Type type);
    Color getColor() const;
    Type getType() const;
   virtual void set_image(QString);
   virtual QString get_img();
    virtual bool isValidMove(Tile *) const = 0;
    virtual void cal_threat(const Tile *) const=0;
    // Destructor
    virtual ~Chessman() = default;
protected:
  QString img_addr="null";
    int score;
    Color color;
    Type type;
    int moves;
};
#endif // PIECE_H
