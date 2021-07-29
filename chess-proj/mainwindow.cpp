#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QImage"
#include <QPixmap>
#include <QWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QtGui>
#include <QLabel>
#include <QtCore>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QTime>
#include <QDate>
#include <QTimer>
#include "board.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), watch(new Stopwatch())
{

  ui->setupUi(this);

  QObject::connect(ui->startStopButton, &QPushButton::clicked,
                   this, &MainWindow::startStopTimer);
  QObject::connect(ui->resetButton, &QPushButton::clicked,
                   this, &MainWindow::resetTimer);
  //signal
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(10);

  QImage Image;
  Image.load(":/utility/board.png");
  QPixmap pixmap = QPixmap::fromImage(Image);
  int with = ui->board_label->width();
  int height = ui->board_label->height();
  QPixmap fitpixmap = pixmap.scaled(with, height); // full fill
                                                   // qpixmap fitpixmap = pixmap.scaled (with, height, qt :: keEpaspectratio, qt :: smoothtransformation); // Scalable
  ui->board_label->setPixmap(fitpixmap);

  // qpixmap fitpixmap = pixmap.scaled (with, height, qt :: keEpaspectratio, qt :: smoothtransformation); // Scalable

  QLabel *status = new QLabel(this);
  status->setText(" ->Status : no game avilable ");
  ui->statusbar->addWidget(status);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_start_clicked()
{

  QWidget *window = new QWidget;
  window->setWindowTitle("set a new game");
  QGridLayout *Layout = new QGridLayout;
  QLabel *label1 = new QLabel("Enter Player 1 Full Name :");
  QLineEdit *p1_name = new QLineEdit;
  QLabel *label2 = new QLabel("Enter Player 2 Full Name :");
  QLineEdit *p2_name = new QLineEdit;

  QLabel *label3 = new QLabel("Enter the Game name:");
  QLineEdit *game_name = new QLineEdit;
  QPushButton *button = new QPushButton("start game");

  Layout->addWidget(label1, 0, 0);
  Layout->addWidget(p1_name, 0, 1);
  Layout->addWidget(label2, 1, 0);
  Layout->addWidget(p2_name, 1, 1);
  Layout->addWidget(label3, 2, 0);
  Layout->addWidget(game_name, 2, 1);
  Layout->addWidget(button, 3, 0, 1, 2);
  window->setLayout(Layout);
  window->setFixedSize(400, 400);

  window->show();



  connect(button, &QPushButton::clicked, this, [=]()
          { MainWindow::g(p1_name->text(), p2_name->text(), game_name->text()); }); //lambda experssion
}

void MainWindow::g(QString a, QString b, QString c)
{
  ui->game_label2->setText(c);

  ui->p1_negative->setText("0");
  ui->p1_positive->setText("0");
  ui->p2_negative->setText("0");
  ui->p2_positive->setText("0");
  status->setText(" ->Status : game is running ");
  ui->statusbar->addWidget(status);
  int chance = QRandomGenerator::global()->bounded(0,2);
 qDebug()<< chance<<endl;
  if (chance ==1)
  {
      ui->p1_name->setText(a+"(white)");
      ui->p2_name->setText(b+"(black)");
  }
  else if (chance ==0)
  {
      ui->p1_name->setText(a+"(black)");
      ui->p2_name->setText(b+"(white)");
  }
  watch->start();
}

void MainWindow::on_actionAbout_us_triggered()
{
  QMessageBox msgBox;
  msgBox.setText("<b><p> Welcome to ' Advanced Chess game ' Ver BETA </p><p>  Designers & Programers : </p><p>  + Ali Hemati  </p>+Mohsen Hami </b>");
  msgBox.exec();
}

void MainWindow::on_actionExit_triggered()
{
  window()->close();
}

//---------------------------------------

void MainWindow::startStopTimer()
{
  if (watch->isRunning())
  {
    ui->startStopButton->setText("Restart");
    watch->pause();
  }
  else
  {
    ui->startStopButton->setText("Pause");
    watch->start();
  }
}

// Triggers when the "Reset" button is clicked
// Stops the watch, if it is running,
// and resets the "Pause"/"Restart" to "Start"
void MainWindow::resetTimer()
{
  ui->startStopButton->setText("Start");
  ui->hundredthsText->setText("00");
  ui->secondsText->setText("00");
  ui->minutesText->setText("00");
  watch->reset();
}

// Triggers every 10 milliseconds (every hundredth of a second)
// Updates the time displayed on the stopwatch.
void MainWindow::update()
{
  if (watch->isRunning())
  {
    qint64 time = watch->getTime();
    int h = time / 1000 / 60 / 60;
    int m = (time / 1000 / 60) - (h * 60);
    int s = (time / 1000) - (m * 60);
    int ms = time - (s + (m + (h * 60)) * 60) * 1000;
    int ms_dis = ms / 10;
    if (ms_dis < 10)
    {
      ui->hundredthsText->setText(QStringLiteral("0%1").arg(ms_dis));
    }
    else
    {
      ui->hundredthsText->setText(QStringLiteral("%1").arg(ms_dis));
    }
    if (s < 10)
    {
      ui->secondsText->setText(QStringLiteral("0%1").arg(s));
    }
    else
    {
      ui->secondsText->setText(QStringLiteral("%1").arg(s));
    }
    if (m < 10)
    {
      ui->minutesText->setText(QStringLiteral("0%1").arg(m));
    }
    else
    {
      ui->minutesText->setText(QStringLiteral("%1").arg(m));
    }
  }
}
//---------------------------------------

void MainWindow::on_dispen_btn_clicked()
{
  watch->pause();
}
