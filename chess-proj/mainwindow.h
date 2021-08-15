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

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void set_player_inf(QString,QString,QString);

    ~MainWindow();

private slots:

    //--------------------------------

    void on_start_clicked(); //start new game button

    void on_actionAbout_us_triggered(); //button of about us window

    void on_actionExit_triggered(); //button of exit the game

    void on_dispen_btn_clicked();  //button of dispensing(or resign) the game

    void on_double_btn_clicked(); //button of dual movement

    void on_undo_btn_clicked(); //button of undo action

    void on_b_lost_label_linkHovered(const QString &link);

    void on_w_lost_label_linkHovered(const QString &link);

    void on_comboBox_b_activated(int index);

    void on_comboBox_w_activated(int index);

    void on_load_btn_clicked(bool); // button of load a new game to continue

    void on_save_btn_clicked(); // button of save the game action

    void on_view_last_btn_clicked(); // button of veiw last game

    void on_p1_name_linkHovered(const QString &link);// an event for update black player scores

    void on_p2_name_linkHovered(const QString &link); // an event for update white player scores

public slots:

    void startStopTimer();
    void resetTimer();
    void update();

private:
    QLabel *status = new QLabel(this); //status bar of mainwindow
    Stopwatch * watch;

protected:
 Ui::MainWindow *ui;

    //----------------------------------------------
};
#endif // MAINWINDOW_H
