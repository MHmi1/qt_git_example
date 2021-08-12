#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
#include <QMainWindow>
#include <QLabel>
#include <QLCDNumber>
#include <QTime>
#include "stopwatch.h"
#include <QDate>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
    class Tile;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

   // friend void soldier_sec_half(const Tile *t);
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void g(QString,QString,QString);
   void set_scores();
   int  a;
    ~MainWindow();

private slots:

    //--------------------------------

    void on_start_clicked();

    void on_actionAbout_us_triggered();

    void on_actionExit_triggered();

    void on_dispen_btn_clicked();

    void on_double_btn_clicked();

    void on_undo_btn_clicked();

    void on_b_lost_label_linkHovered(const QString &link);

    void on_w_lost_label_linkHovered(const QString &link);

    void on_comboBox_b_activated(int index);

    void on_comboBox_w_activated(int index);

    void on_load_btn_clicked(bool);

    void on_save_btn_clicked();

    void on_view_last_btn_clicked();

public slots:

    void startStopTimer();
    void resetTimer();
    void update();

private:
    QLabel *status = new QLabel(this);
    Stopwatch * watch;

protected:
 Ui::MainWindow *ui;

    //----------------------------------------------
};
#endif // MAINWINDOW_H
