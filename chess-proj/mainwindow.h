#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <QMainWindow>
#include <QLabel>
#include <QLCDNumber>
#include <QTime>
#include "stopwatch.h"
#include <QDate>
#include "board.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //std::string,std::string,std::string
    void g(QString,QString,QString);

    ~MainWindow();

private slots:

    //--------------------------------

    void on_start_clicked();

    void on_actionAbout_us_triggered();

    void on_actionExit_triggered();

    void on_dispen_btn_clicked();

public slots:
    void startStopTimer();
    void resetTimer();
    void update();

private:
    QLabel *status = new QLabel(this);
    Stopwatch * watch;
    Ui::MainWindow *ui;
    board * br=nullptr;

    //----------------------------------------------
};
#endif // MAINWINDOW_H
