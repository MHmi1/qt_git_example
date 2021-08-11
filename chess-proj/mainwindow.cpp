#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QtCore>
#include <QtWidgets>
#include <QTime>
#include <QDate>
#include <QTimer>
#include "board.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <cell.h>
#include <string>
#include <QVector>
#include <QStandardItemModel>
extern bool is_soldier_end;
extern std::vector<char> lost_white;
extern std::vector<char> lost_black;
extern const int is_castling_act;
extern std::map<int, int> change_coord(QString coord);
extern Tile *tile[8][8];
bool is_dual_avctive = 0;
extern std::array<int, 2> bscore;
extern std::array<int, 2> wscore;
extern const QVector<QString> b_move_list;
extern const QVector<QString> w_move_list;
extern void game_start(int flag);
extern int turn;
extern void del_piece(Tile *temp);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), watch(new Stopwatch())
{

  ui->setupUi(this);

  setStyleSheet("background-color:#dadada;");
  setAutoFillBackground(true);

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
  // int with = ui->board_label->width();
  // int height = ui->board_label->height();
  // QPixmap fitpixmap = pixmap.scaled(with, height); // full fill                                               // qpixmap fitpixmap = pixmap.scaled (with, height, qt :: keEpaspectratio, qt :: smoothtransformation); // Scalable
  // ui->board_label->setPixmap(fitpixmap);
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
          {
            MainWindow::g(p1_name->text(), p2_name->text(), game_name->text());
            window->close();
          }); //lambda experssion
}

void MainWindow::g(QString a, QString b, QString c)
{

  game_start(1);
  ui->game_label2->setText(c);
  ui->p1_negative->setText("0");
  ui->p1_positive->setText("0");
  ui->p2_negative->setText("0");
  ui->p2_positive->setText("0");
  status->setText(" ->Status : game is running ");
  ui->statusbar->addWidget(status);
  int chance = QRandomGenerator::global()->bounded(0, 2);
  if (chance == 1)
  {
    ui->p1_name->setText(a + "(white)");
    ui->p2_name->setText(b + "(black)");

    watch->start();
  }
  else if (chance == 0)
  {
    ui->p1_name->setText(a + "(black)");
    ui->p2_name->setText(b + "(white)");

    watch->start();
  }

  ui->redo_btn->setEnabled(1);
  ui->double_btn->setEnabled(1);
  ui->undo_btn->setEnabled(1);
  ui->dispen_btn->setEnabled(1);
  turn = 1;
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
  exit(0);
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
  // int total_p1 = ui->p1_positive->text().toInt() +  ui->p1_negative->text().toInt();
  // int total_p2 = ui->p2_positive->text().toInt() +  ui->p2_negative->text().toInt();
  watch->pause();
  game_start(0);
}

void MainWindow::on_double_btn_clicked()
{
  is_dual_avctive = 1;
  if (turn == 0)
  {
    int a = ui->p2_negative->text().toInt() - 30;
    ui->p2_negative->setText(QString::number(a));
  }
  if (turn == 1)
  {
    int a = ui->p1_negative->text().toInt() - 30;
    ui->p1_negative->setText(QString::number(a));
  }
}

void MainWindow::on_undo_btn_clicked() // this function operation based on  check castling is active or not !
{
  if (turn == 1 && b_move_list.size() > 0)
  {
    if (is_castling_act == 0)
    {
      auto dest_pos = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 1).toStdString().substr(3, 2))).begin();
      del_piece(tile[dest_pos->first][dest_pos->second]);

      auto origin_pos = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 1).toStdString().substr(1, 2))).begin();
      char piece = char(b_move_list.at(b_move_list.size() - 1).toStdString().at(0));
      tile[origin_pos->first][origin_pos->second]->piece = 0;
      tile[origin_pos->first][origin_pos->second]->piece = 1;
      tile[origin_pos->first][origin_pos->second]->pieceColor = 0;
      tile[origin_pos->first][origin_pos->second]->display(piece);
      int a = ui->p2_negative->text().toInt() - 5;
      ui->p2_negative->setText(QString::number(a));
      turn = 0;
    }

    else if (is_castling_act == 1 && b_move_list.size() > 1)
    {
      auto dest_pos = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 1).toStdString().substr(3, 2))).begin();
      del_piece(tile[dest_pos->first][dest_pos->second]);

      auto origin_pos = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 1).toStdString().substr(1, 2))).begin();
      char piece = char(b_move_list.at(b_move_list.size() - 1).toStdString().at(0));
      tile[origin_pos->first][origin_pos->second]->piece = 0;
      tile[origin_pos->first][origin_pos->second]->piece = 1;
      tile[origin_pos->first][origin_pos->second]->pieceColor = 0;
      tile[origin_pos->first][origin_pos->second]->display(piece);
      //-------------------------------------------------
      auto dest_pos2 = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 2).toStdString().substr(3, 2))).begin();
      del_piece(tile[dest_pos2->first][dest_pos2->second]);

      auto origin_pos2 = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 2).toStdString().substr(1, 2))).begin();
      char piece2 = char(b_move_list.at(b_move_list.size() - 2).toStdString().at(0));
      tile[origin_pos2->first][origin_pos2->second]->piece = 0;
      tile[origin_pos2->first][origin_pos2->second]->piece = 1;
      tile[origin_pos2->first][origin_pos2->second]->pieceColor = 0;
      tile[origin_pos2->first][origin_pos2->second]->display(piece2);

      int a = ui->p2_negative->text().toInt() - 5;
      ui->p2_negative->setText(QString::number(a));
      turn = 0;
    }
  }
  else if (turn == 0 && w_move_list.size() > 0)
  {
    if (is_castling_act == 0)
    {
      auto dest_pos = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 1).toStdString().substr(3, 2))).begin();
      del_piece(tile[dest_pos->first][dest_pos->second]);

      auto origin_pos = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 1).toStdString().substr(1, 2))).begin();
      char piece = char(w_move_list.at(w_move_list.size() - 1).toStdString().at(0));
      tile[origin_pos->first][origin_pos->second]->piece = 0;
      tile[origin_pos->first][origin_pos->second]->piece = 1;
      tile[origin_pos->first][origin_pos->second]->pieceColor = 1;
      tile[origin_pos->first][origin_pos->second]->display(piece);
      int a = ui->p1_negative->text().toInt() - 5;
      ui->p1_negative->setText(QString::number(a));
      turn = 1;
    }

    else if (is_castling_act == 1 && w_move_list.size() > 0)
    {
      qDebug() << w_move_list.at(w_move_list.size() - 1) << endl
               << w_move_list.at(w_move_list.size() - 2) << endl;
      auto dest_pos = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 1).toStdString().substr(3, 2))).begin();
      del_piece(tile[dest_pos->first][dest_pos->second]);

      auto origin_pos = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 1).toStdString().substr(1, 2))).begin();
      char piece = char(w_move_list.at(w_move_list.size() - 1).toStdString().at(0));
      tile[origin_pos->first][origin_pos->second]->piece = 0;
      tile[origin_pos->first][origin_pos->second]->piece = 1;
      tile[origin_pos->first][origin_pos->second]->pieceColor = 1;
      tile[origin_pos->first][origin_pos->second]->display(piece);

      //-----------------------------------------------------------------

      auto dest_pos2 = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 2).toStdString().substr(3, 2))).begin();
      del_piece(tile[dest_pos2->first][dest_pos2->second]);

      auto origin_pos2 = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 2).toStdString().substr(1, 2))).begin();
      char piece2 = char(w_move_list.at(w_move_list.size() - 2).toStdString().at(0));
      tile[origin_pos2->first][origin_pos2->second]->piece = 0;
      tile[origin_pos2->first][origin_pos2->second]->piece = 1;
      tile[origin_pos2->first][origin_pos2->second]->pieceColor = 1;
      tile[origin_pos2->first][origin_pos2->second]->display(piece2);
      int a = ui->p1_negative->text().toInt() - 5;
      ui->p1_negative->setText(QString::number(a));
      turn = 1;
    }
  }
}

void MainWindow::on_b_lost_label_linkHovered(const QString &link)
{
  QString black;
  ui->comboBox_b->clear();
  for (int i = 0; i < lost_black.size(); i++)
  {
    switch (lost_black.at(i))
    {
    case 'Q':
      black += "Queen";
      break;
    case 'H':
      black += "Horse";
      break;
    case 'R':
      black += "Rook";
      break;
    case 'P':
      black += "Pawn";
      break;
    case 'B':
      black += "Bishop";
      break;
    }
    ui->comboBox_b->addItem(black);
    black = "";

    for (int i = 0; i < ui->comboBox_b->count(); i++)
    {
      if (ui->comboBox_b->itemText(i).toStdString().at(0) == 'P')
      {
        QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(ui->comboBox_b->model());
        QStandardItem *item = model->item(i, 0);
        item->setEnabled(0);
      }
    }
  }
}

void MainWindow::on_w_lost_label_linkHovered(const QString &link)
{
  QString white;
  ui->comboBox_w->clear();
  for (int i = 0; i < lost_white.size(); i++)
  {
    switch (lost_white.at(i))
    {
    case 'Q':
      white += "Queen";
      break;
    case 'H':
      white += "Horse";
      break;
    case 'R':
      white += "Rook";
      break;
    case 'P':
      white += "Pawn";
      break;
    case 'B':
      white += "Bishop";
      break;
    }
    ui->comboBox_w->addItem(white);
    white = "";

    for (int i = 0; i < ui->comboBox_w->count(); i++)
    {
      if (ui->comboBox_w->itemText(i).toStdString().at(0) == 'P')
      {
        QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(ui->comboBox_w->model());
        QStandardItem *item = model->item(i, 0);
        item->setEnabled(0);
      }
    }
  }
}

void MainWindow::on_comboBox_b_activated(int index)
{
  int cnt = 0;
  for (int i = 0; i < lost_black.size(); i++)
  {
    if (lost_black.at(i) == 'Q' || lost_black.at(i) == 'R' || lost_black.at(i) == 'B' || lost_black.at(i) == 'H')
    {
      cnt++;
    }
  }

  if (is_soldier_end == 1 && cnt > 0)
  {
    if (b_move_list.at(b_move_list.size() - 1).toStdString().at(0) == 'P')
    {
      std::map<int, int> it = change_coord(QString::fromStdString(b_move_list.at(b_move_list.size() - 1).toStdString().substr(3, 2)));
      std::map<int, int>::iterator ite = it.begin();

      del_piece(tile[ite->first][ite->second]);

      tile[ite->first][ite->second]->piece = 0;
      tile[ite->first][ite->second]->piece = 1;
      tile[ite->first][ite->second]->pieceColor = 0;
      tile[ite->first][ite->second]->display(ui->comboBox_b->itemText(index).toStdString().at(0));
    }
  }
  is_soldier_end = 0;
}

void MainWindow::on_comboBox_w_activated(int index)
{
  int cnt = 0;
  for (int i = 0; i < lost_white.size(); i++)
  {
    if (lost_white.at(i) == 'Q' || lost_white.at(i) == 'R' || lost_white.at(i) == 'B' || lost_white.at(i) == 'H')
    {
      cnt++;
    }
  }

  if (is_soldier_end == 1 && cnt > 0)
  {
    if (w_move_list.at(w_move_list.size() - 1).toStdString().at(0) == 'P')
    {
      std::map<int, int> it = change_coord(QString::fromStdString(w_move_list.at(w_move_list.size() - 1).toStdString().substr(3, 2)));
      std::map<int, int>::iterator ite = it.begin();


      del_piece(tile[ite->first][ite->second]);

      tile[ite->first][ite->second]->piece = 0;
      tile[ite->first][ite->second]->piece = 1;
      tile[ite->first][ite->second]->pieceColor = 1;
      tile[ite->first][ite->second]->display(ui->comboBox_w->itemText(index).toStdString().at(0));
    }
  }
  is_soldier_end = 0;
}
