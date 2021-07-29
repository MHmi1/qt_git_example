#ifndef CELL_H
#define CELL_H
#include <QString>
#include "pieces/Piece.h"
#include <memory>


class Cell
{
private:
    QString id;
    bool full;
    /*std::unique_ptr<Piece * >*/

public:
     Piece * getPiece();
  void setPiece(std::unique_ptr<Piece> piece);
    void set_id(QString);
    QString get_id();
    bool isfull();

    Cell();
    ~Cell();
    std::unique_ptr<Piece> p;
protected:

};

#endif // CELL_H
