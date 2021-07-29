#ifndef PIECE_H
#define PIECE_H
#include <QString>
#include <vector>
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

class Piece
{
public:
    // Constructor
    Piece(Type, Color);
    void setColor(Color color);
    void setType(Type type);
    Color getColor() const;
    Type getType() const;
   virtual void set_image(QString);
   virtual QString get_img(Color);
    virtual bool isValidMove(/*const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords*/) const = 0;


    // Destructor
    virtual ~Piece() = default;
protected:
  QString img_addr="null";
    int score;
    Color color;
    Type type;
    int moves;
    char typeToChar(Type type) const;
    char colorToChar(Color color) const;
    vector<QString> movelist;
};

#endif // PIECE_H
