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
using namespace std;
void coloring(int, int, QPainter);

board::board(QWidget *parent)
    : QWidget(parent)
{
    //The plural is a flag bit, which means not to draw
    chessX = -1;
    chessY = -1;
}

void board::set_board()
{
     qDebug()<<"there 1"<<endl;
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
    qDebug()<<"there 2"<<endl;
/*
    square[0][0]->setPiece(std::unique_ptr<Piece> (new Rook(BLACK)) );

    qDebug()<<"there 3"<<endl;
    square[0][0]->p->set_image(":/white/White/w-rook.png");
   // square[0][1]->setPiece(&hw1);
    square[0][1]->p->set_image(":/white/White/w-knight.png");

  //  square[0][2]->setPiece(&bw1);
    square[0][2]->p->set_image(":/white/White/w-bishop.png");

   // square[0][3]->setPiece(&qw1);
    square[0][3]->p->set_image(":/white/White/w-queen.png");
 qDebug()<<"there 4"<<endl;
   // square[0][4]->setPiece(&kw1);
    square[0][4]->p->set_image(":/white/White/w-king.png");

    //square[0][5]->setPiece(&bw2);
    square[0][5]->p->set_image(":/white/White/w-bishop.png");

   // square[0][6]->setPiece(&hw2);
    square[0][6]->p->set_image(":/white/White/w-knight.png");
 qDebug()<<"there 5"<<endl;
  //  square[0][7]->setPiece(&rw2);
    square[0][7]->p->set_image(":/white/White/w-rook.png");

    for (int i=0;i<8;i++)
    {
       qDebug() << square[0][i]->getPiece()->get_img(WHITE);
    }
     qDebug()<<"there 6"<<endl;
     */
}

void board::show_board(int x,int y)
{

}

board::~board()
{


}

void board::paintEvent(QPaintEvent *event)
{
    gridH = height() / 10;
    gridW = width() / 10;

    //The starting point of the chessboard
    startX = 0;
    startY = 0;

    QPainter p(this); //Set Qpainter, associate the current window
    p.drawPixmap(rect(), QPixmap(":/utility/board.jpg"));

    //Set the brush
    QPen pen;
    pen.setWidth(2); //Line width
    p.setPen(pen);

    //Take the middle 8 to draw the chessboard
    for (int i = 0; i <= 8; i++)
    {
        //Horizontal line
        p.drawLine(startX, startY + i * 90, startX + 8 * 90, startY + i * 90);
        //Vertical line
        p.drawLine(startX + i * 90, startY, startX + i * 90, startY + 8 * 90);
    }

    //Draw chess pieces
    if (chessX != -1 && chessY != -1)
    {
        p.drawPixmap(startX + chessX * 90, startY + chessY * 90,
                     90, 90,
                     QPixmap(":/utility/choice.png"));
    }

    QGridLayout *Layout = new QGridLayout;
    Layout->geometry().setX(0);
    Layout->geometry().setY(0);
    /*
    QImage Image;

    Image.load(":/white/White/w-rook.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    QPixmap fitpixmap = pixmap.scaled(90, 90);
    QLabel *lab = new QLabel(this);
    lab->setPixmap(fitpixmap);
    Layout->setRowStretch(0, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab, 0, 0);

    //----------------------------

    QLabel *lab1 = new QLabel(this);
    Image.load(":/white/White/w-knight.png");
    QPixmap pixmap1 = QPixmap::fromImage(Image);
    QPixmap fitpixmap1 = pixmap1.scaled(90, 90);
    lab1->setPixmap(fitpixmap1);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab1, 0, 1);

    //--------------------------------

    QLabel *lab2 = new QLabel(this);
    Image.load(":/white/White/w-bishop.png");
    QPixmap pixmap2 = QPixmap::fromImage(Image);
    QPixmap fitpixmap2 = pixmap2.scaled(90, 90);
    lab2->setPixmap(fitpixmap2);
    Layout->setRowStretch(2, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab2, 0, 2);
    //------------------------------------
    QLabel *lab3 = new QLabel(this);
    Image.load(":/white/White/w-queen.png");
    QPixmap pixmap3 = QPixmap::fromImage(Image);
    QPixmap fitpixmap3 = pixmap3.scaled(90, 90);
    lab3->setPixmap(fitpixmap3);
    Layout->setRowStretch(3, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab3, 0, 3);
    //------------------------------------------
    QLabel *lab4 = new QLabel(this);
    Image.load(":/white/White/w-king.png");
    QPixmap pixmap4 = QPixmap::fromImage(Image);
    QPixmap fitpixmap4 = pixmap4.scaled(90, 90);
    lab4->setPixmap(fitpixmap4);
    Layout->setRowStretch(4, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab4, 0, 4);

    //-------------------------------------
    QLabel *lab5 = new QLabel(this);
    Image.load(":/white/White/w-bishop.png");
    QPixmap pixmap5 = QPixmap::fromImage(Image);
    QPixmap fitpixmap5 = pixmap5.scaled(90, 90);
    lab5->setPixmap(fitpixmap5);
    Layout->setRowStretch(5, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab5, 0, 5);
    //---------------------------------------
    QLabel *lab6 = new QLabel(this);
    Image.load(":/white/White/w-knight.png");
    QPixmap pixmap6 = QPixmap::fromImage(Image);
    QPixmap fitpixmap6 = pixmap6.scaled(90, 90);
    lab6->setPixmap(fitpixmap6);
    Layout->setRowStretch(6, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab6, 0, 6);

    //--------------------------------------

    Image.load(":/white/White/w-rook.png");
    QPixmap pixmap7 = QPixmap::fromImage(Image);
    QPixmap fitpixmap7 = pixmap7.scaled(90, 90);
    QLabel *lab7 = new QLabel(this);
    lab7->setPixmap(fitpixmap7);
    Layout->setRowStretch(7, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab7, 0, 7);

    //------------------------------------------
    QImage img;
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap8 = QPixmap::fromImage(img);
    QPixmap fitpixmap8 = pixmap8.scaled(90, 90);
    QLabel *lab8 = new QLabel(this);
    lab8->setPixmap(fitpixmap8);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(0, 70);
    Layout->addWidget(lab8, 1, 0);
    //--------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap9 = QPixmap::fromImage(img);
    QPixmap fitpixmap9 = pixmap9.scaled(90, 90);
    QLabel *lab9 = new QLabel(this);
    lab9->setPixmap(fitpixmap9);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(1, 70);
    Layout->addWidget(lab9, 1, 1);

    //-------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap10 = QPixmap::fromImage(img);
    QPixmap fitpixmap10 = pixmap10.scaled(90, 90);
    QLabel *lab10 = new QLabel(this);
    lab10->setPixmap(fitpixmap10);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(2, 70);
    Layout->addWidget(lab10, 1, 2);
    //------------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap11 = QPixmap::fromImage(img);
    QPixmap fitpixmap11 = pixmap11.scaled(90, 90);
    QLabel *lab11 = new QLabel(this);
    lab11->setPixmap(fitpixmap11);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(3, 70);
    Layout->addWidget(lab11, 1, 3);
    //------------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap12 = QPixmap::fromImage(img);
    QPixmap fitpixmap12 = pixmap12.scaled(90, 90);
    QLabel *lab12 = new QLabel(this);
    lab12->setPixmap(fitpixmap12);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(4, 70);
    Layout->addWidget(lab12, 1, 4);
    //------------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap13 = QPixmap::fromImage(img);
    QPixmap fitpixmap13 = pixmap13.scaled(90, 90);
    QLabel *lab13 = new QLabel(this);
    lab13->setPixmap(fitpixmap13);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(5, 70);
    Layout->addWidget(lab13, 1, 5);
    //------------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap14 = QPixmap::fromImage(img);
    QPixmap fitpixmap14 = pixmap14.scaled(90, 90);
    QLabel *lab14 = new QLabel(this);
    lab14->setPixmap(fitpixmap14);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(6, 70);
    Layout->addWidget(lab14, 1, 6);
    //------------------------------------------
    img.load(":/white/White/w-pawn.png");
    QPixmap pixmap15 = QPixmap::fromImage(img);
    QPixmap fitpixmap15 = pixmap15.scaled(90, 90);
    QLabel *lab15 = new QLabel(this);
    lab15->setPixmap(fitpixmap15);
    Layout->setRowStretch(1, 70);
    Layout->setColumnStretch(7, 70);
    Layout->addWidget(lab15, 1, 7);
    //------------------------------------------
*/
    this->setLayout(Layout);
     board::set_board();
}

void board::mousePressEvent(QMouseEvent *event)
{
    //Get the clicked coordinates
    int clickXPos = event->x();

    int clickYPos = event->y();

    //Ensure that the click is within the range of the board
    if (clickXPos >= startX && clickXPos <= startX + 8 * 90 && clickYPos >= startY && clickYPos <= startY + 8 * 90)
    {
        //The board position is converted to the array coordinate value
        chessX = (clickXPos - startX) / 90;
        chessY = (clickYPos - startY) / 90;

        QPainter p(this);
        QPen pen;
        pen.setWidth(2); //Line width
        p.setPen(pen);

        if (chessX != -1 && chessY != -1)
        {
                  show_board(chessX,chessY);
            p.drawPixmap(startX + chessX * 90, startY + chessY * 90,
                         90, 90,
                         QPixmap(":/utility/choice.png"));
        }

        qDebug() << chessX << chessY;
    }
    //Update the window, indirectly call paintEvent
    update();
}

move_err board::move_piece(QString cmnd)
{
    if (cmnd.at(0) == 'K')
    {
    }
    //------------------------
    if (cmnd.at(0) == 'Q')
    {
    }
    //------------------------
    if (cmnd.at(0) == 'R')
    {
    }
    //------------------------
    if (cmnd.at(0) == 'B')
    {
    }
    //------------------------
    if (cmnd.at(0) == 'H')
    {
    }
    //------------------------
    if (cmnd.at(0) == 'P')
    {
    }
    //------------------------
}

void coloring(int row, int col, QPainter &p)
{
    /*
    if (row != -1 && col != -1)
    {
        p.drawPixmap (row * 90,col * 90,90, 90,QPixmap(":/utility/choice.png"));
    }
*/
}
