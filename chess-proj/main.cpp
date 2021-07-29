#include "mainwindow.h"
#include "board.h"
#include <QApplication>
#include <QGridLayout>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
  w.show();
   board www;

   int x=720;
   int y=720;
   www.setFixedSize(x,y);
   /*
   QGridLayout *Layout = new QGridLayout;
   QImage Image;
   Image.load(":/white/White/w-rook.png");
   QPixmap pixmap = QPixmap::fromImage(Image);
   QPixmap fitpixmap = pixmap.scaled(90, 90);
  */
          // setPixmap(fitpixmap);

   www.show();

    return a.exec();
}


