#ifndef CHESSMAN_H
#define CHESSMAN_H
#include <QString>
#include <vector>
#include "cell.h"
using std::vector;
enum Type // enum data for detecting type of peice
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};
enum Color // enum data for detecting color of peice
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
   virtual void set_image(QString); // virtual function for set image to cell of chess board
   virtual QString get_img(); // virtual function for get image from cell of chess board
    virtual bool isValidMove(Tile *) const = 0; // pure virtual function  validating movements
    virtual void cal_threat(const Tile *) const=0; // pure virtual function to calculating threat if each peice
    // virtual Destructor
    virtual ~Chessman() = default;
protected:
  QString img_addr="null";
    int score; //peice score
    Color color;
    Type type;
    int moves;
};
#endif // PIECE_H

