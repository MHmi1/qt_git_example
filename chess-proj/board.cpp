#include "board.h"
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QGridLayout>
#include <QLabel>
#include <Qdebug>
#include <memory>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>

using namespace std;

void coloring(int, int, QPainter);

void board::mouse_cur_pos()
{
    //ui->lbl_mouse_cur_pos->setText(QString("x = %1 , y=%2").arg(ui->lblmouse->x().arg(ui->lblmouse->y());
    //ui->lbl_mouse_cur_eve->setText(("mouse moving ! "));
    qDebug() << "mouse moving !" << endl;
}

void board::mouse_press()
{
    //ui->lbl_mouse_cur_eve->setText(("mouse pressed ! "));
    qDebug() << "mouse pressed !" << endl;
}

void board::mouse_left()
{
    qDebug() << "mouse left !" << endl;
}

board::board(QWidget *parent)
    : QWidget(parent)
{
    //The plural is a flag bit, which means not to draw
    chessX = -1;
    chessY = -1;
}

void board::set_board()
{

    // qDebug()<<"there 1"<<endl;
    Rook rw1(WHITE), rw2(WHITE);
    Rook rb1(BLACK), rb2(BLACK);

    Knight hw1(WHITE), hw2(WHITE);
    Knight hb1(BLACK), hb2(BLACK);

    Bishop bw1(WHITE), bw2(WHITE);
    Bishop bb1(BLACK), bb2(BLACK);

    Queen qw1(WHITE);
    Queen qb1(BLACK);

    King kw1(WHITE);
    King kb1(BLACK);

    Pawn pw1(WHITE), pw2(WHITE), pw3(WHITE), pw4(WHITE), pw5(WHITE), pw6(WHITE), pw7(WHITE), pw8(WHITE);
    Pawn pb1(BLACK), pb2(BLACK), pb3(BLACK), pb4(BLACK), pb5(BLACK), pb6(BLACK), pb7(BLACK), pb8(BLACK);
    // qDebug()<<"there 2"<<endl;
    QGraphicsRectItem *rec = new QGraphicsRectItem();
    rec->setX(0);
    rec->setY(0);
}

void board::show_board(int x, int y)
{
}

board::~board()
{
}

void board::paintEvent(QPaintEvent *event)
{
    gridH = height() / 10;
    gridW = width() / 10;

    startX = 0;
    startY = 0;

    QPainter p(this);
    p.drawPixmap(rect(), QPixmap(":/utility/board.jpg"));

    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);

    for (int i = 0; i <= 8; i++)
    {

        p.drawLine(startX, startY + i * 90, startX + 8 * 90, startY + i * 90);

        p.drawLine(startX + i * 90, startY, startX + i * 90, startY + 8 * 90);
    }

    if (chessX != -1 && chessY != -1)
    {
        p.drawPixmap(startX + chessX * 90, startY + chessY * 90,
                     90, 90,
                     QPixmap(":/utility/choice.png"));
    }

    QGridLayout *Layout = new QGridLayout;
    Layout->setSpacing(7);
    Layout->sizeConstraint();

    Layout->geometry().setX(0);
    Layout->geometry().setY(0);

    this->setLayout(Layout);
    board::set_board();
}
void board::lab1click()
{
    qDebug() << "there here" << endl;
}

void board::mousePressEvent(QMouseEvent *event)
{

    int clickXPos = event->x();

    int clickYPos = event->y();

    if (clickXPos >= startX && clickXPos <= startX + 8 * 90 && clickYPos >= startY && clickYPos <= startY + 8 * 90)
    {

        chessX = (clickXPos - startX) / 90;
        chessY = (clickYPos - startY) / 90;

        QPainter p(this);
        QPen pen;
        pen.setWidth(2); //Line width
        p.setPen(pen);

        if (chessX != -1 && chessY != -1)
        {
            show_board(chessX, chessY);
            p.drawPixmap(startX + chessX * 90, startY + chessY * 90,
                         90, 90,
                         QPixmap(":/utility/choice.png"));
        }

        qDebug() << chessX << chessY;
    }

    update();
}
