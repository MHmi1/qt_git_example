#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Tile: public QLabel
{
public:
    //public Fields
    int tileColor,piece,pieceColor,row,col,tileNum; //
    char pieceName;
    QString coordinate;

    //Constructors
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};

    //public Methods
    void mousePressEvent(QMouseEvent *event);
    void display(char elem); //fuction to show peice on the chess board
    void tileDisplay();  //show and paint  cells
    QString get_coord() const;
};

#endif // TILE_H
