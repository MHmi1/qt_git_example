#include "cell.h"
#include "validation.h"
#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <list>
#include <cctype>
#include <QMediaPlayer>
#include <QFile>
#include <QStatusBar>
#include <QSpinBox>
#include <QMessageBox>


bool is_soldier_end = 0; //flag of being a soldier at the end
QVector<QString> b_move_list; // container to store balck movements
QVector<QString> w_move_list; // container to store white movements
std::vector<char> lost_white; // container to store white lost pieces
std::vector<char> lost_black; // container to store balck lost pieces
QVector<QString> w_existing_piece; // container for existing white peice
QVector<QString> b_existing_piece; // container for existing black peice
bool is_castling_act = 0; //The flag of the castleing is active
validation *valid = new validation();
//------------------------------------------------------
extern bool is_dual_avctive;
extern std::map<int, int> change_coord(QString coord);
extern double SqrtNumber(double num);
extern int bishop_threats, queen_threats, king_threats, pawn_threats, knight_threats, rook_threats; //variables for calculate threating other pieces
extern int count, turn;
extern QWidget *myWidget;
extern Tile *click1;	 // refer to tile * pinter at main.cpp
extern Tile *tile[8][8]; // refer to 2d tile array at main.cpp
extern void delay(long long int millisecondsToWait);
extern int is_w1_anpasan, is_w2_anpasan;
extern int is_b1_anpasan, is_b2_anpasan;
extern QVector<QString> possible_move;
//------------------------------------------------------
void update_exist_piece(); //update list of existing piece of each player
void validate(Tile *temp, int c);    //main function for validating movemets and clicks
void disOrange();                    // unselcet a chosen peice
bool hit_foe(const Tile *);			 // check attaking for calculate it's score
bool just_check();					 // check out for checking in chess
void check_mate();					 // check out for check-mate in chess
void soldier_sec_half(const Tile *); // check for is the soldier crossed halfway !
QString black_rand_move();			 //choose a black piece for random movement
QString white_rand_move();			 //choose a white piece for random movement                          // dual move function
void Duplicate_move(int);			 // checking for duplicate movement for each player(- score)
void end_soldier(Tile *);			 // checking for the slodier has reached the end
bool is_draw();						 // check for draw condintion of the game
void castling(const QString &, int); //  do castling of black and white player
size_t path_len(QString move);		 //calculate the lenth of each movement
int choose_cnt = 0;					 // counter for counting clicks
bool king_at_check = 0;              //The flag of the is king at check !
//------------------------------------------------------

void w_score_update(int num) //update white - or + score at database
{
    QSqlQuery q;

    QString str = "UPDATE player_score SET p2_positive = p2_positive+" + QString::number(num) + " WHERE ID = 1;";
    QString str1 = "UPDATE player_score SET p2_negative = p2_negative" + QString::number(num) + " WHERE ID = 1;";
    if (num > 0)
    {

        q.exec(str);
    }
    else if (num < 0)
    {

        q.exec(str1);
    }
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(q);
}

void b_score_update(int num) //update black - or + score at database
{
    QSqlQuery q;
    QString str = "UPDATE player_score SET p1_positive = p1_positive+" + QString::number(num) + " WHERE ID = 1;";
    QString str1 = "UPDATE player_score SET p1_negative = p1_negative" + QString::number(num) + " WHERE ID = 1;";

    if (num > 0)
    {

        q.exec(str);
    }
    else if (num < 0)
    {

        q.exec(str1);
    }
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(q);
}
//----------------------------------------------------

void Tile::mousePressEvent(QMouseEvent *event)
{
    validate(this, ++count);
}

size_t path_len(QString move)
{
    std::map<int, int> point1 = change_coord(move.fromStdString(move.toStdString().substr(1, 2)));
    std::map<int, int> point2 = change_coord(move.fromStdString(move.toStdString().substr(3, 2)));
    auto p1 = point1.begin();
    auto p2 = point2.begin();

    int x = p2->first - p1->first;
    p2->first >= p1->first ? x = p2->first - p1->first : x = p1->first - p2->first;

    int y = p2->second - p1->second;
    p2->second >= p1->second ? y = p2->second - p1->second : y = p1->second - p2->second;

    size_t len = SqrtNumber((x * x) + (y * y));
    return len;
}

void del_piece(Tile *temp) //delete a peice of board
{
    temp->piece = 1;
    temp->pieceColor = click1->pieceColor;
    temp->pieceName = click1->pieceName;
    click1->display(click1->pieceName);
    temp->display(click1->pieceName);
    click1->tileDisplay();
    temp->tileDisplay();
    temp->display('a');
    temp->piece = 0;
}

void Tile::display(char elem) //display all & one peice
{
    this->pieceName = elem;

    if (this->pieceColor && this->piece) //seting image for white peice
    {
        switch (elem)
        {
        case 'P':
        {
            Pawn white_pawn(WHITE);
            this->setPixmap(QPixmap(white_pawn.get_img()));
        }
        break;
        case 'R':
        {
            Rook white_rook(WHITE);
            this->setPixmap(QPixmap(white_rook.get_img()));
        }
        break;

        case 'H':
        {
            Knight white_knight(WHITE);
            this->setPixmap(QPixmap(white_knight.get_img()));
        }
        break;
        case 'K':
        {
            King white_king(WHITE);
            this->setPixmap(QPixmap(white_king.get_img()));
        }
        break;
        case 'Q':
        {
            Queen white_queen(WHITE);
            this->setPixmap(QPixmap(white_queen.get_img()));
        }
        break;
        case 'B':
        {
            Bishop white_bishop(WHITE);
            this->setPixmap(QPixmap(white_bishop.get_img()));
        }
        break;
        default:
        {
            this->setPixmap(QPixmap(" "));
        }
        }
    }

    else if (this->piece) //seting image for black peice
    {
        switch (elem)
        {
        case 'P':
        {
            Pawn black_pawn(BLACK);
            this->setPixmap(QPixmap(black_pawn.get_img()));
        }
        break;
        case 'R':
        {
            Rook black_rook(BLACK);
            this->setPixmap(QPixmap(black_rook.get_img()));
        }
        break;

        case 'H':
        {
            Knight black_knight(BLACK);
            this->setPixmap(QPixmap(black_knight.get_img()));
        }
        break;
        case 'K':
        {
            King black_king(BLACK);
            this->setPixmap(QPixmap(black_king.get_img()));
        }
        break;
        case 'Q':
        {
            Queen black_queen(BLACK);
            this->setPixmap(QPixmap(black_queen.get_img()));
        }
        break;
        case 'B':
        {
            Bishop black_bishop(BLACK);
            this->setPixmap(QPixmap(black_bishop.get_img()));
        }
        break;
        default:
        {
            this->setPixmap(QPixmap(" "));
        }
        }
    }
    else
        this->clear();
}

static bool last_t; //an static flag to store last turns

void validate(Tile *temp, int c)
{
    int retValue, i;

    if (c == 1)
    {
        if (temp->piece && (temp->pieceColor == turn))
        {

            exp[max++] = temp->tileNum;
            retValue = valid->chooser(temp);

            if (king_at_check == 1 && last_t != turn) //------check
            {
                qDebug() << (temp->pieceColor == 0 ? "white KING checked" : "black KING checked") << endl;
                if (temp->pieceColor == 0) {b_score_update(10);}
                else if (temp->pieceColor != 0) { w_score_update(10);}
            }
             king_at_check=0;

            if (retValue == 1)
            {
                click1 = new Tile();

                temp->setStyleSheet("QLabel {background-color: #0bc51d;}"); //green
                click1 = temp;
                choose_cnt++;
            }
            else
            {
                temp->setStyleSheet("QLabel {background-color: red;}");
                count = 0;
            }
        }
        else
        {
            //qDebug()<<" impossible clicking  .";
            count = 0;
        }
    }
    else
    {
        if (temp->tileNum == click1->tileNum)
        {

            click1->tileDisplay();
            disOrange();
            max = 0;
            count = 0;
        }
        for (i = 0; i < max; i++)
        {
            if (temp->tileNum == exp[i])
            {

                hit_foe(temp);

                click1->piece = 0;
                temp->piece = 1;

                temp->pieceColor = click1->pieceColor;
                temp->pieceName = click1->pieceName;

                click1->display(click1->pieceName);
                temp->display(click1->pieceName);

                click1->tileDisplay();
                temp->tileDisplay();

                retValue = valid->check(click1);
                QMediaPlayer *music = new QMediaPlayer();

                QString move = QString(temp->pieceName) + click1->get_coord() + temp->get_coord();

                if (temp->pieceColor == 1)
                {
                    w_move_list.push_back(move);
                }
                else if (temp->pieceColor == 0)
                {
                    b_move_list.push_back(move);
                }

                castling(move, temp->pieceColor);

                Duplicate_move(temp->pieceColor);

                if (retValue)
                {
                    tile[wR][wC]->setStyleSheet("QLabel {background-color: red;}");
                }

                disOrange();

                max = 0;

                soldier_sec_half(temp);
                end_soldier(temp);
                if (is_draw() == 1 )
                   {
                    QSqlQuery q;
                    q.exec("SELECT p1_positive , p1_negative FROM player_score WHERE id=1");
                      QString b_pos ;
                      QString b_neg;
                      while (q.next())
                      {
                           b_pos = q.value(0).toString();
                           b_neg = q.value(1).toString();
                      }
                      q.exec("SELECT p2_positive , p2_negative FROM player_score WHERE id=1");
                        QString w_pos ;
                        QString w_neg;
                        while (q.next())
                        {
                             w_pos = q.value(0).toString();
                             w_neg = q.value(1).toString();
                        }
                        QMessageBox * msg = new QMessageBox();
                        if (w_pos+w_neg > b_pos+b_neg)
                        {

                            msg->setInformativeText("the Game is draw , and white player's score is greater than black player .... /n white player win !! ");
                                         msg->show();
                                         delay(5000);
                                         exit(0);
                        }
                        else if (w_pos+w_neg < b_pos+b_neg)
                        {
                            msg->setInformativeText("the Game is draw , and black player's score is greater than white player .... /n black player win !! ");
                                         msg->show();
                                         delay(5000);
                                          exit(0);
                        }
                   }
                if (is_w1_anpasan > -1)
                {
                    del_piece(tile[3][is_w1_anpasan]);
                    is_w1_anpasan = -1;
                }

                else if (is_w2_anpasan > -1)
                {
                    del_piece(tile[3][is_w2_anpasan]);
                    is_w2_anpasan = -1;
                }
                //--------------------------------------------
                if (is_b1_anpasan > -1)
                {
                    del_piece(tile[4][is_b1_anpasan]);
                    is_b1_anpasan = -1;
                }

                else if (is_b2_anpasan > -1)
                {
                    del_piece(tile[4][is_b2_anpasan]);
                    is_b2_anpasan = -1;
                }

                qDebug() << "-> turn's : " << (temp->pieceColor ? "BLACK" : "WHITE") << endl;

                if (choose_cnt > 1)
                {
                    qDebug() << "1 negate score for " << (temp->pieceColor ? "WHITE" : "BLACK") << "(touch_move rule)" << endl;
                    if (temp->pieceColor == 0)
                    {
                        w_score_update(-1);
                    }
                    else if (temp->pieceColor == 1)
                    {
                        b_score_update(-1);
                    }
                }

                if (temp->pieceColor == 1)
                {
                    int total_threat = 0;
                    if (queen_threats > 0)
                    {
                        total_threat += queen_threats;
                    }
                    if (bishop_threats > 0)
                    {
                        total_threat += bishop_threats;
                    }
                    if (rook_threats > 0)
                    {
                        total_threat += rook_threats;
                    }
                    if (knight_threats > 0)
                    {
                        total_threat += knight_threats;
                    }
                    if (pawn_threats > 0)
                    {
                        total_threat += pawn_threats;
                    }
                    if (king_threats > 0)
                    {
                        total_threat += king_threats;
                    }

                   
                    qDebug() << total_threat << "total scores for threating white palyer !!" << endl;
                    w_score_update(total_threat);
                    king_threats = 0;
                    pawn_threats = 0;
                    knight_threats = 0;
                    rook_threats = 0;
                    bishop_threats = 0;
                    queen_threats = 0;
                }
                else if (temp->pieceColor == 0)
                {
                    int total_threat = 0;
                    if (queen_threats > 0)
                    {
                        total_threat += queen_threats;
                    }
                    if (bishop_threats > 0)
                    {
                        total_threat += bishop_threats;
                    }
                    if (rook_threats > 0)
                    {
                        total_threat += rook_threats;
                    }
                    if (knight_threats > 0)
                    {
                        total_threat += knight_threats;
                    }
                    if (pawn_threats > 0)
                    {
                        total_threat += pawn_threats;
                    }
                    if (king_threats > 0)
                    {
                        total_threat += king_threats;
                    }
                    qDebug() << total_threat << "total scores for threating black palyer !!" << endl;
                    b_score_update(total_threat);
                }

                last_t = turn;
                king_at_check = 0;
                music->setMedia(QUrl("qrc:/utility/move.mp3"));
                music->setVolume(85);
                music->play();

                if (is_dual_avctive == 1)
                {

                    is_dual_avctive = 0;
                }
                else
                {
                    turn = (turn + 1) % 2;
                    is_dual_avctive = 0;
                }

                count = 0;
                choose_cnt = 0;
            }

            else
                count = 1;
        }
    }
}

void Tile::tileDisplay()
{
    if (this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(172, 110, 80);}:hover{background-color: rgb(86,175,185);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(200,159,136);}:hover{background-color: rgb(86,208,217);}");
}

void castling(const QString &mov, int color)
{
    if (mov.at(0) == 'K' && mov.toStdString().substr(1, 2) == "e1" && mov.toStdString().substr(3, 2) == "c1")
    {
        std::map<int, int> tempp = change_coord("d1");
        auto ite = tempp.begin();

        del_piece(tile[7][0]);
        tile[ite->first][ite->second]->piece = 0;
        tile[ite->first][ite->second]->piece = 1;
        tile[ite->first][ite->second]->pieceName = 'R';
        tile[ite->first][ite->second]->pieceColor = color;
        tile[ite->first][ite->second]->display('R');
        w_move_list.push_back("Ra1d1");
        is_castling_act = 1;
    }
    else if (mov.at(0) == 'K' && mov.toStdString().substr(1, 2) == "e1" && mov.toStdString().substr(3, 2) == "g1")
    {
        std::map<int, int> tempp = change_coord("f1");
        auto ite = tempp.begin();

        del_piece(tile[7][7]);

        tile[ite->first][ite->second]->piece = 0;
        tile[ite->first][ite->second]->piece = 1;
        tile[ite->first][ite->second]->pieceName = 'R';
        tile[ite->first][ite->second]->pieceColor = color;
        tile[ite->first][ite->second]->display('R');
        w_move_list.push_back("Rh1f1");
        is_castling_act = 1;
    }

    if (mov.at(0) == 'K' && mov.toStdString().substr(1, 2) == "e8" && mov.toStdString().substr(3, 2) == "g8")
    { //black king east castling
        std::map<int, int> tempp = change_coord("f8");
        auto ite = tempp.begin();

        del_piece(tile[0][7]);
        tile[ite->first][ite->second]->piece = 0;
        tile[ite->first][ite->second]->piece = 1;
        tile[ite->first][ite->second]->pieceName = 'R';
        tile[ite->first][ite->second]->pieceColor = color;
        tile[ite->first][ite->second]->display('R');
        b_move_list.push_back("Rh8f8");
        is_castling_act = 1;
    }

    else if (mov.at(0) == 'K' && mov.toStdString().substr(1, 2) == "e8" && mov.toStdString().substr(3, 2) == "c8")
    { //black king west castling
        std::map<int, int> tempp = change_coord("d8");
        auto ite = tempp.begin();

        del_piece(tile[0][0]);
        tile[ite->first][ite->second]->piece = 0;
        tile[ite->first][ite->second]->piece = 1;
        tile[ite->first][ite->second]->pieceName = 'R';
        tile[ite->first][ite->second]->pieceColor = color;
        tile[ite->first][ite->second]->display('R');
        b_move_list.push_back("Ra8d8");
        is_castling_act = 1;
    }
}

QString Tile::get_coord() const  //return checkered coordinate of a piece
{
    return coordinate;
}

void disOrange()
{
    int i;
    for (i = 0; i < max; i++)
        tile[exp[i] / 8][exp[i] % 8]->tileDisplay();
}

void Duplicate_move(int color)
{
    if (w_move_list.size() > 2 && color == 1)
    {
        if ((w_move_list.at(w_move_list.size() - 1).at(0) == w_move_list.at(w_move_list.size() - 2).at(0)) && (w_move_list.at(w_move_list.size() - 1).toStdString().substr(1, 2) == w_move_list.at(w_move_list.size() - 2).toStdString().substr(3, 2)) && (w_move_list.at(w_move_list.size() - 1).toStdString().substr(3, 2) == w_move_list.at(w_move_list.size() - 2).toStdString().substr(1, 2)))
        {
            // qDebug() << " negative score for white (Duplicate_move !)" << endl;
            w_score_update(-2);
        }
    }

    if (b_move_list.size() > 2 && color == 0)
    {

        if ((b_move_list.at(b_move_list.size() - 1).at(0) == b_move_list.at(b_move_list.size() - 2).at(0)) && (b_move_list.at(b_move_list.size() - 1).toStdString().substr(1, 2) == b_move_list.at(b_move_list.size() - 2).toStdString().substr(3, 2)) && (b_move_list.at(b_move_list.size() - 1).toStdString().substr(3, 2) == b_move_list.at(b_move_list.size() - 2).toStdString().substr(1, 2)))
        {
            // qDebug() << "negative score for black (Duplicate_move !)" << endl;
            b_score_update(-2);
        }
    }
}

void soldier_sec_half(const Tile *t) //check for reaching soldier_second_half of board
{

    //QSqlQuery q;
    if ((t->pieceColor == 1) && (t->pieceName == 'P') && (t->coordinate == "a5" || t->coordinate == "b5" || t->coordinate == "c5" || t->coordinate == "d5" || t->coordinate == "e5" || t->coordinate == "f5" || t->coordinate == "g5" || t->coordinate == "h5"))
    {
        qDebug() << "3 pos score for white (sec half)" << endl;
        w_score_update(3);
    }
    if ((t->pieceColor == 0) && (t->pieceName == 'P') && (t->coordinate == "a4" || t->coordinate == "b4" || t->coordinate == "c4" || t->coordinate == "d4" || t->coordinate == "e4" || t->coordinate == "f4" || t->coordinate == "g4" || t->coordinate == "h4"))
    {
        qDebug() << "3 pos score for black (sec half)" << endl;
        b_score_update(3);
    }
}

void end_soldier(Tile *t) //check for reaching soldier to end of the board
{
    QMessageBox msgBox;
    if ((t->pieceColor == 1) && (t->pieceName == 'P') && (t->coordinate == "a8" || t->coordinate == "b8" || t->coordinate == "c8" || t->coordinate == "d8" || t->coordinate == "e8" || t->coordinate == "f8" || t->coordinate == "g8" || t->coordinate == "h8"))
    {
        is_soldier_end = 1;
        qDebug() << " white solier is at the end , choose a new piece !" << endl;
        if (lost_white.size() > 1)
        {
            msgBox.setText("  white solier is at the end !");
            msgBox.setInformativeText(" Please choose a new piece !");
            QPushButton *okbtn = msgBox.addButton(QMessageBox::Ok);
            msgBox.show();
            delay(5000);
        }
    }

    if ((t->pieceColor == 0) && (t->pieceName == 'P') && (t->coordinate == "a1" || t->coordinate == "b1" || t->coordinate == "c1" || t->coordinate == "d1" || t->coordinate == "e1" || t->coordinate == "f1" || t->coordinate == "g1" || t->coordinate == "h1"))
    {
        is_soldier_end = 1;
        qDebug() << "black solier is at the end , choose a new piece !" << endl;

        if (lost_black.size() > 1)
        {
            msgBox.setText("  black solier is at the end !");
            msgBox.setInformativeText(" Please choose a new piece !");
            QPushButton *okbtn = msgBox.addButton(QMessageBox::Ok);
            msgBox.show();
            delay(5000);
        }
    }
}

bool is_draw()  //draw mean Equality
{
    update_exist_piece();

    // TWO KING LEFT
    if (b_existing_piece.size() == 1 && w_existing_piece.size() == 1)
    {
        if (b_existing_piece.at(0).at(0) == 'K' && w_existing_piece.at(0).at(0) == 'K')
            qDebug() << " game is equal (TWO KING LEFT)" << endl;
        // qDebug()<<"there 1 "<<endl;
        return 1;
    }

    //-----------------------------------------

    else if (b_existing_piece.size() == 3 && w_existing_piece.size() == 1)
    { // TWO KNIGHT LEFT  lead to a draw by insufficient material
        int knight_cnt = 0;
        for (int i = 0; i < b_existing_piece.size(); i++)
        {
            if (b_existing_piece.at(i).at(0) == 'H')
                knight_cnt++;
        }
        if (knight_cnt == 2 && w_existing_piece.at(0).at(0) == 'K')
        {
            qDebug() << " game is equal (TWO KNIGHT LEFT) " << endl;

            return 1;
        }
    }
    //-----------------------------------------
    else if (b_existing_piece.size() == 1 && w_existing_piece.size() == 3)
    { // TWO KNIGHT LEFT lead to a draw by insufficient material
        int knight_cnt = 0;
        for (int i = 0; i < w_existing_piece.size(); i++)
        {
            if (w_existing_piece.at(i).at(0) == 'H')
                knight_cnt++;
        }
        if (knight_cnt == 2 && b_existing_piece.at(0).at(0) == 'K')
        {
            qDebug() << " game is equal (TWO KNIGHT LEFT)" << endl;

            return 1;
        }
    }
    //-----------------------------------------
    else if (w_move_list.size() > 51 && lost_white.size() == 0)
    { //Fifty-move_rule  for white player
        int cnt = 0;
        for (int i = 0; i < w_move_list.size(); i++)
        {
            if (w_move_list.at(i).at(0) == 'P')
                cnt++;
        }
        if (cnt == 0)
        {
            qDebug() << " game is equal (Fifty-move_rule) " << endl;

            return 1;
        }
    }
    //-----------------------------------------
    else if (b_move_list.size() > 51 && lost_black.size() == 0)
    { //Fifty-move_rule  for black player
        int cnt = 0;
        for (int i = 0; i < b_move_list.size(); i++)
        {
            if (b_move_list.at(i).at(0) == 'P')
                cnt++;
        }
        if (cnt == 0)
        {
            qDebug() << " game is equal (Fifty-move_rule)" << endl;

            return 1;
        }
    }
    return 0;
}

void update_exist_piece()
{
    w_existing_piece.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tile[i][j]->piece && tile[i][j]->pieceColor == 1)
            {
                w_existing_piece.push_back(tile[i][j]->pieceName + tile[i][j]->get_coord());
            }
        }
    }

    b_existing_piece.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tile[i][j]->piece && tile[i][j]->pieceColor == 0)
            {
                b_existing_piece.push_back(tile[i][j]->pieceName + tile[i][j]->get_coord());
            }
        }
    }
}

QString black_rand_move()
{
    update_exist_piece();
    /*
    std::default_random_engine eng( static_cast<unsigned int>(time(NULL)));
    std::uniform_int_distribution <unsigned int> myran(0,existing_piece.size() );
    return existing_piece.at(myran(eng));
    */
    srand(static_cast<unsigned int>(time(NULL)));
    int randomNumber;
    randomNumber = (rand() % b_existing_piece.size()) + 1;
    return b_existing_piece.at(randomNumber);
}

QString white_rand_move()
{
    srand(static_cast<unsigned int>(time(NULL)));
    update_exist_piece();
    int randomNumber;
    randomNumber = (rand() % w_existing_piece.size()) + 1;
    return w_existing_piece.at(randomNumber);
}

bool hit_foe(const Tile *temp) // register score to DB  for atacking
{
    std::map<int, int> t = change_coord(temp->get_coord());
    int score = 0;
    switch (temp->pieceName)
    {
    case 'P':
        score = 3;
        break;
    case 'B':
        score = 8;
        break;
    case 'H':
        score = 8;
        break;
    case 'R':
        score = 8;
        break;
    case 'Q':
        score = 15;
        break;
    default:
        score = 0;
        break;
    }
    for (const auto &ite : t)
    {
        if (tile[ite.first][ite.second]->piece && temp->pieceColor == 1)
        {
            b_score_update(score);
            qDebug() << score << "pos score for attacking black " << endl;
            lost_white.push_back(tile[ite.first][ite.second]->pieceName);
            return true;
        }
        if (tile[ite.first][ite.second]->piece && temp->pieceColor == 0)
        {
            w_score_update(score);
            qDebug() << score << "pos score for attacking white " << endl;
            lost_black.push_back(tile[ite.first][ite.second]->pieceName);
            return true;
        }
    }
    return false;
}

/*
    if (is_b_rand == 1 || is_w_rand == 1)
    {
        if (1)
        {
            srand(static_cast<unsigned int>(time(NULL)));
            int randomNumber=0;

           QString piece_pos =  QString::fromStdString(black_rand_move().toStdString().substr(1,2));
           std::map<int,int>  map1 = change_coord(piece_pos);
           auto mapp = map1.begin();

             int retValue = valid->chooser(tile[mapp->first][mapp->second]);

            qDebug()<<mapp->first<<" * " << mapp->second<<" * " <<max <<endl;
            if (possible_move.size() != 0)
            {
                for (int i=0;i<possible_move.size();i++)
            {
                qDebug()<<"possible " << possible_move.at(i)<<endl;

            }
                std::sort(possible_move.begin(), possible_move.end());
                  possible_move.erase(std::unique(possible_move.begin(), possible_move.end()), possible_move.end());

            char p_name = tile[mapp->first][mapp->second]->pieceName;
                 // del_piece(tile[mapp->first][mapp->second]);
             tile[mapp->first][mapp->second]->piece=0;
             tile[mapp->first][mapp->second]->piece=1;

            randomNumber = (rand() % possible_move.size()-1) + 1;
            std::map<int,int> ma = change_coord(possible_move.at(randomNumber));

            auto ite = ma.begin();
             qDebug ()<< "chosed chance : "<<ite->first<<ite->second<<endl;
          //  tile[ite->first][ite->second]->piece=0;
            tile[ite->first][ite->second]->piece=1;
            tile[ite->first][ite->second]->pieceColor=0;
            tile[ite->first][ite->second]->display(p_name);
              tile[ite->first][ite->second]->show();

            }
            possible_move.clear();
        }
        */
