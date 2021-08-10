#include <QTime>
#include <QApplication>
//This file is a place to write useful functions
#include <QTableWidget>
void delay( int millisecondsToWait )
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


