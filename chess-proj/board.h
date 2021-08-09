#ifndef BOARD_H
#define BOARD_H
//#include "cell.h"
#include <QMainWindow>
#include <QWidget>
#include "pieces/Piece.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include <QLabel>
enum move_err
{
    IMPOSSIBLE=1,
    DEST_FULL,
};

class board : public QWidget
{
    Q_OBJECT

public:
    void set_board();
    move_err move_piece(QString);
    board(QWidget *parent = 0);
    ~board();
    void show_board(int,int);
    void lab1click();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
        int gridW; //Grid height
         int gridH; //Grid width
         int startX; //The starting point of the board X
         int startY; //The starting point of the board Y
         //Cell * square[8][8]= {{nullptr}};
         QLabel lab[32];

        int chessX;
        int chessY; //board coordinates

private slots:
void mouse_cur_pos();
void mouse_press();
void mouse_left();
};


#endif // BOARD_H

