#include <QTime>
#include <QApplication>
//This file is a place to write useful functions
#include <QTableWidget>

void delay( long long int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

double SqrtNumber(double num)  //function for calculate square root of number
  {
             double lower_bound=0;
             double upper_bound=num;
             double temp=0;

             int nCount = 50;

        while(nCount != 0)
        {
               temp=(lower_bound+upper_bound)/2;
               if(temp*temp==num)
               {
                       return temp;
               }
               else if(temp*temp > num)

               {
                       upper_bound = temp;
               }
               else
               {
                       lower_bound = temp;
               }
        nCount--;
     }
        return temp;
 }

std::map<int, int> change_coord(QString coord) //std::map<int, int> change_coord(QString coord); change chess coordination to x,y(or row,col)
{
   /* if (coord.at(0)!='a' || coord.at(0)!='b' || coord.at(0)!='c' || coord.at(0)!='d' || coord.at(0)!='e' || coord.at(0)!='f' || coord.at(0)!='g' ||coord.at(0)!='h')
    {
        throw  std::invalid_argument("Error ! for changing coord you must use a-g and 1-8 !! ");
    }
*/

    int ch;

    switch (coord.toStdString().at(0))
    {
    case 'a':
    {
        ch = 0;
    }
    break;

    case 'b':
    {
        ch = 1;
    }
    break;

    case 'c':
    {
        ch = 2;
    }
    break;

    case 'd':
    {
        ch = 3;
    }
    break;

    case 'e':
    {
        ch = 4;
    }
    break;

    case 'f':
    {
        ch = 5;
    }
    break;

    case 'g':
    {
        ch = 6;
    }
    break;

    case 'h':
    {
        ch = 7;
    }
    break;
    }
    char y2 = (coord.toStdString().at(1));
    int y = y2 - '0'; //trick for convert char to int
    std::map<int, int> arr{{8 - y, ch}};
    return arr;
}


