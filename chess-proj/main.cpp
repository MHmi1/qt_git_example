#include "mainwindow.h"

#include <QApplication>
#include <QGridLayout>
#include "cell.h"
#include <string>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
<<<<<<< HEAD
extern bool is_reveiw_act;
=======
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a
=======
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a
>>>>>>> Stashed changes
extern void delay(int millisecondsToWait);
extern void del_piece(Tile *temp);
int count = 0, turn = 1, exp[60], max = 0;
int wR, wC, bR, bC;
Tile *click1;
Tile *tile[8][8] = {{NULL}};
extern std::map<int, int> change_coord(QString coord);
extern QVector<QString> b_move_list;
extern QVector<QString> w_move_list;
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

    outLabel->setStyleSheet("QLabel { background-color :rgb(128, 70, 0); color : black; }");
  }
};

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
  char ch = 0;

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

      std::string str = std::to_string(8 - i);
      tile[i][j]->coordinate = QString(ch) + QString(str.c_str());
    }
  }
  //-----------------------------------------
  wR = 7;
  wC = 4;

  bR = 0;
  bC = 4;
}

void accessories(bool flag, QWidget *baseWidget, QString w_player = "null", QString b_player = "null", QString game_name = "null")
{
  QTextEdit *txt = new QTextEdit(baseWidget);

  if (flag == 0)
  {
    txt->setGeometry(1000, 105, 250, 550);
    txt->setStyleSheet("QLabel {background-color: gray;}");
    txt->setDisabled(1);
    txt->show();
  }

  if (flag = w_player != "null" && b_player != "null" && game_name != "null")
  {
    txt->setText("<b>Review last game </b>: \n");
    txt->append("<b>Game name </b> : " + game_name + '\n');
    txt->append("<b>Player 1 name </b> : " + w_player + '\n');
    txt->append("<b>Player 2 name </b> : " + b_player + '\n');
  }
}

void game_start_end(int flag)
{
  QWidget *myWidget = new QWidget();
  myWidget->setWindowTitle("Advanced Chess Board ver Beta");
  if (flag == 1) //start game
  {
    myWidget->setGeometry(0, 0, 1370, 700);
    accessories(0, myWidget);
    chessBoard(myWidget, tile);
    myWidget->show();
  }

  if (flag == 0) //game canceled and exit
  {
    QMessageBox msgBox;
    QString win_msg, msg1;
    win_msg = (turn ? "BLACK" : "WHITE");
    msg1 = (turn ? "WHITE" : "BLACK");

    msgBox.setText(msg1 + "  Player have canceled the game ...");

    msgBox.setInformativeText(" The winner is the  " + win_msg + " player !");

    QPushButton *okbtn = msgBox.addButton(QMessageBox::Ok);

    msgBox.show();
    if (msgBox.clickedButton() == okbtn)
    {

      myWidget->close();

      exit(0);
    }
    else if (msgBox.clickedButton() != okbtn)
    {
      delay(8000);
      myWidget->close();

      exit(0);
    }
  }
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindow w;

  w.show();

  return a.exec();
}

std::string strings[4];
int len(std::string str)
{
  int length = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    length++;
  }
  return length;
}

<<<<<<< HEAD
//  split() function for spiliting a string with seperator
void split(std::string str, char seperator)
{
  int currIndex = 0, i = 0;
  int startIndex = 0, endIndex = 0;
  while (i <= len(str))
  {
    if (str[i] == seperator || i == len(str))
    {
      endIndex = i;
      std::string subStr = "";
      subStr.append(str, startIndex, endIndex - startIndex);
      strings[currIndex] = subStr;
      currIndex += 1;
      startIndex = endIndex + 1;
    }
    i++;
  }
=======
void accessories(bool flag,QWidget *baseWidget)
{
     QTextEdit *txt = new QTextEdit(baseWidget);

    if (flag==0)
    {
        txt->setGeometry(1000, 105, 250, 550);
        txt->setStyleSheet("QLabel {background-color: gray;}");
         txt->setDisabled(1);
          txt->show();
    }

    else if (flag==1)
    {
        if (turn ==1)
        {
            txt->setText("white player :");
            txt->append("\t #"+w_move_list.at(w_move_list.size()-1));
        }
        if (turn==0)
        {
            txt->setText("black player :");
            txt->append("\t #"+b_move_list.at(b_move_list.size()-1));
        }
    }
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a
}

<<<<<<< HEAD
void continue_game(QString moves)
{
<<<<<<< HEAD

  QWidget *myWidget = new QWidget();
  myWidget->setWindowTitle("Advanced Chess Board ver Beta");
  myWidget->setGeometry(0, 0, 1370, 700);

  std::vector<std::string> w;
  std::vector<std::string> b;

  int hash_pos = 0, star_pos = 0;

  for (int i = 0; i < moves.size(); i++)
  {
    if (moves.at(i) == '#')
    {
      hash_pos = i;
=======
=======
void accessories(bool flag,QWidget *baseWidget)
{
     QTextEdit *txt = new QTextEdit(baseWidget);

    if (flag==0)
    {
        txt->setGeometry(1000, 105, 250, 550);
        txt->setStyleSheet("QLabel {background-color: gray;}");
         txt->setDisabled(1);
          txt->show();
    }

    else if (flag==1)
    {
        if (turn ==1)
        {
            txt->setText("white player :");
            txt->append("\t #"+w_move_list.at(w_move_list.size()-1));
        }
        if (turn==0)
        {
            txt->setText("black player :");
            txt->append("\t #"+b_move_list.at(b_move_list.size()-1));
        }
    }
<<<<<<< Updated upstream
    //-----------------------------------------
    wR = 7;
    wC = 4;

    bR = 0;
    bC = 4;
}

void accessories(bool flag,QWidget *baseWidget)
{
     QTextEdit *txt = new QTextEdit(baseWidget);

    if (flag==0)
    {
        txt->setGeometry(1000, 105, 250, 550);
        txt->setStyleSheet("QLabel {background-color: gray;}");
         txt->setDisabled(1);
          txt->show();
    }

    else if (flag==1)
    {
        if (turn ==1)
        {
            txt->setText("white player :");
            txt->append("\t #"+w_move_list.at(w_move_list.size()-1));
        }
        if (turn==0)
        {
            txt->setText("black player :");
            txt->append("\t #"+b_move_list.at(b_move_list.size()-1));
        }
    }
=======
>>>>>>> Stashed changes
}

void game_start(int  flag)
{
<<<<<<< Updated upstream
=======
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a
>>>>>>> Stashed changes
    QWidget *myWidget = new QWidget();
    myWidget->setWindowTitle("Advanced Chess Board ver Beta");
    if (flag==1) //start game
    {
        myWidget->setGeometry(0, 0, 1370, 700);
        accessories(0,myWidget);
        chessBoard(myWidget, tile);
        myWidget->show();
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a
    }
  }

  for (int i = hash_pos; i < moves.size(); i++)
  {
    if (moves.at(i) == '*')
    {
      star_pos = i;
    }
  }

  for (int j = 0; j < hash_pos; j++)
  {
    if (moves.at(j) == 'W')
    {
      w.push_back(moves.toStdString().substr(j + 1, 5));
    }
  }

<<<<<<< HEAD
  for (int w = hash_pos; w < star_pos; w++)
  {
    if (moves.at(w) == 'B')
    {
      b.push_back(moves.toStdString().substr(w + 1, 5));
    }
  }
=======
        QPushButton *okbtn = msgBox.addButton(QMessageBox::Ok);

        msgBox.show();
        if (msgBox.clickedButton() == okbtn)
        {
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a

  split(moves.toStdString().substr(star_pos + 1, moves.toStdString().size() - star_pos), '-');
  accessories(0, myWidget, QString::fromStdString(strings[0]), QString::fromStdString(strings[1]), QString::fromStdString(strings[2]));
  chessBoard(myWidget, tile);
  myWidget->show();

  /*
        for (int k=0;k<w.size();k++)
        {
            qDebug()<<QString::fromStdString(w.at(k))<<endl;
        }
         qDebug()<<"----------------------------------"<<endl;
        for (int k=0;k<b.size();k++)
        {
            qDebug()<<QString::fromStdString(b.at(k))<<endl;
        }
<<<<<<< HEAD
        */

  delay(2000);

  while (w.size() != 0 || b.size() != 0)
  {

    if (w.size() != 0)
    {
      std::map<int, int> aa = change_coord(QString::fromStdString(w.at(0).substr(1, 2)));
      auto a = aa.begin();
=======
    }
}



int main(int argc, char *argv[])
{
>>>>>>> 71dd5cb6e83be13e96c41903760ea1984eea474a


      //-------------------------------------------------
      tile[a->first][a->second]->piece = 1;
      tile[a->first][a->second]->display('a');
      tile[a->first][a->second]->piece = 0;
      //----------------------------------------------------------

      std::map<int, int> ff = change_coord(QString::fromStdString(w.at(0).substr(3, 2)));
      auto f = ff.begin();
      tile[f->first][f->second]->piece = 0;
      tile[f->first][f->second]->piece = 1;
      tile[f->first][f->second]->pieceColor = 1;
      tile[f->first][f->second]->display(w.at(0).at(0));
      w.erase(w.begin());

      delay(1300);
    }

    if (b.size() != 0)
    {
      std::map<int, int> cc = change_coord(QString::fromStdString(b.at(0).substr(1, 2)));
      auto c = cc.begin();

      tile[c->first][c->second]->piece = 1;
      tile[c->first][c->second]->display('a');
      tile[c->first][c->second]->piece = 0;
      //del_piece(tile[c->first][c->second]);
      //qDebug()<<"there 4 "<<endl;

      std::map<int, int> dd = change_coord(QString::fromStdString(b.at(0).substr(3, 2)));
      auto d = dd.begin();
      tile[d->first][d->second]->piece = 0;
      tile[d->first][d->second]->piece = 1;
      tile[d->first][d->second]->pieceColor = 0;
      tile[d->first][d->second]->display(b.at(0).at(0));
      b.erase(b.begin());
      delay(1300);

    }
  }

  if (is_reveiw_act==1)
  {
      delay(4000);
       myWidget->close();
       exit(0);
  }

}
