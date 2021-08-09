#include "mainwindow.h"
#include "board.h"
#include <QApplication>
#include <QGridLayout>
#include "cell.h"
#include <string>

int count = 0, turn = 1, exp[60], max = 0;
int wR, wC, bR, bC;
Tile *click1;
Tile *tile[8][8] = {{NULL}};

class Border
{
public:
    Border();
    void outline(QWidget *baseWidget, int xPos, int yPos, int Pos)
    {
        QLabel *outLabel = new QLabel(baseWidget);

        if (!Pos)
            outLabel->setGeometry(xPos, yPos, 552, 20); //Horizontal Borders

        else
            outLabel->setGeometry(xPos, yPos, 20, 512); //Vertical Borders

        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }
};

void accessories(QWidget *baseWidget)
{

    QLabel *moves = new QLabel(baseWidget);
    moves->setGeometry(1000, 105, 250, 550);
    moves->setStyleSheet("QLabel {background-color: white;}");
}

void chessBoard(QWidget *baseWidget, Tile *tile[8][8])
{
    int i, j, k = 0, hor, ver;
    Border *border[4] = {NULL};

    //borderDisplay
    {
        border[0]->outline(baseWidget, 330, 105, 0);
        border[1]->outline(baseWidget, 330, 637, 0);
        border[2]->outline(baseWidget, 330, 125, 1);
        border[2]->outline(baseWidget, 862, 125, 1);
    }

    //Create 64 tiles (allocating memories to the objects of Tile class)
    ver = 125;
    for (i = 0; i < 8; i++)
    {
        hor = 350;
        for (j = 0; j < 8; j++)
        {
            tile[i][j] = new Tile(baseWidget);
            tile[i][j]->tileColor = (i + j) % 2;
            tile[i][j]->piece = 0;
            tile[i][j]->row = i;
            tile[i][j]->col = j;
            tile[i][j]->tileNum = k++;
            tile[i][j]->tileDisplay();
            //tile[i][j]->display('0');
            tile[i][j]->setGeometry(hor, ver, 64, 64);
            hor += 64;
        }
        ver += 64;
    }

    //white pawns
    for (j = 0; j < 8; j++)
    {
        tile[1][j]->piece = 1;
        tile[1][j]->pieceColor = 0;
        tile[1][j]->display('P');
    }

    //black pawns
    for (j = 0; j < 8; j++)
    {
        tile[6][j]->piece = 1;
        tile[6][j]->pieceColor = 1;
        tile[6][j]->display('P');
    }

    //white and black remaining elements
    for (j = 0; j < 8; j++)
    {
        tile[0][j]->piece = 1;
        tile[0][j]->pieceColor = 0;
        tile[7][j]->piece = 1;
        tile[7][j]->pieceColor = 1;
    }

    {
        tile[0][0]->display('R');
        tile[0][1]->display('H');
        tile[0][2]->display('B');
        tile[0][3]->display('Q');
        tile[0][4]->display('K');
        tile[0][5]->display('B');
        tile[0][6]->display('H');
        tile[0][7]->display('R');
    }

    {
        tile[7][0]->display('R');
        tile[7][1]->display('H');
        tile[7][2]->display('B');
        tile[7][3]->display('Q');
        tile[7][4]->display('K');
        tile[7][5]->display('B');
        tile[7][6]->display('H');
        tile[7][7]->display('R');
    }

    //----------------------------------------
    char ch=0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            switch (j)
            {

            case 0:
                ch = 'a';
                break;

            case 1:
                ch = 'b';
                break;

            case 2:
                ch = 'c';
                break;

            case 3:
                ch = 'd';
                break;

            case 4:
                ch = 'e';
                break;

            case 5:
                ch = 'f';
                break;

            case 6:
                ch = 'g';
                break;

            case 7:
                ch = 'h';
                break;
            }

            std::string str = std::to_string(8-i);
            tile[i][j]->cordinate = QString(ch) + QString(str.c_str());
        }
    }
    //-----------------------------------------
    wR = 7;
    wC = 4;

    bR = 0;
    bC = 4;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(0, 0, 1370, 700);

    accessories(myWidget);
    chessBoard(myWidget, tile);

    myWidget->show();
/*
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            qDebug()<<"("<<i<<","<<j<<")"<<tile[i][j]->piece <<" - ";
        }
        qDebug()<<endl;
    }
*/
    return a.exec();

    /*
    MainWindow w;
  w.show();
   board www;

   int x=720;
   int y=720;
   www.setFixedSize(x,y);

   QGridLayout *Layout = new QGridLayout;
   QImage Image;
   Image.load(":/white/White/w-rook.png");
   QPixmap pixmap = QPixmap::fromImage(Image);
   QPixmap fitpixmap = pixmap.scaled(90, 90);

          // setPixmap(fitpixmap);

   www.show();

*/
}


