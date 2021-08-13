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
#include <QDebug>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <cell.h>
#include <string>
#include <QVector>
#include <QStandardItemModel>

extern void b_score_update(int num);
extern void w_score_update(int num);

extern void continue_game(QString moves);
extern bool is_soldier_end;
extern std::vector<char> lost_white;
extern std::vector<char> lost_black;
extern const int is_castling_act;
extern std::map<int, int> change_coord(QString coord);
extern Tile *tile[8][8];
bool is_dual_avctive = 0;
extern std::array<int, 2> bscore;
extern std::array<int, 2> wscore;
extern QVector<QString> b_move_list;
extern QVector<QString> w_move_list;
extern void game_start_end(int flag);
extern int turn;
extern void del_piece(Tile *temp);
bool is_reveiw_act = 0;

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

    QLabel *status = new QLabel(this);
    status->setText(" ->Status : no game avilable ");
    ui->statusbar->addWidget(status);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    //-------------------------
    QString db_path = QDir::currentPath();
    //  qDebug() <<db_path<<endl;    //current path
    db_path = db_path + QString("/scores.db");

    //-----------------------------------------

    db.setDatabaseName(db_path);
    db.open();
    QSqlQuery q;

    QFile file(db_path);
    if (file.size() == 0)
    {
        QString build_db = "CREATE TABLE 'player_score' ('p2_negative'	INTEGER,'p2_positive'	INTEGER, 'p1_positive'	INTEGER,'p1_negative'	INTEGER,'id'	INTEGER,   PRIMARY KEY('id'));";
        for (int i = 0; i < build_db.size(); i++)
        {
            if (build_db.toStdString().at(i) == '\'')
            {
                build_db.toStdString().at(i) = '\"';
            }
        }
        q.exec(build_db);
        q.exec("INSERT INTO player_score (id,p2_negative,p1_negative,p2_positive,p1_positive)VALUES(1,0,0,0,0)");
        file.close();
    }
    else
    {
        QSqlQuery q;
        q.exec("DELETE FROM player_score");
        q.exec("INSERT INTO player_score (id,p2_negative,p1_negative,p2_positive,p1_positive)VALUES(1,0,0,0,0)");
        if (QFile::exists(db_path) == 1)
        {
            QLabel *status1 = new QLabel(this);
            status1->setText(" ->Status : conected to database successfully!");
            ui->statusbar->addWidget(status1);
        }
        else if (QFile::exists(db_path) == 0)
        {
            QLabel *status2 = new QLabel(this);
            status2->setText(" ->Status: Error ,database not found !");
            ui->statusbar->addWidget(status2);
        }
    }
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
                MainWindow::set_player_inf(p1_name->text(), p2_name->text(), game_name->text());
                window->close();
            }); //lambda experssion
}

void MainWindow::set_player_inf(QString a, QString b, QString c)
{

    game_start_end(1);
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
        ui->p1_name->setText("<a href='www. '>" + a + " (BLACK)" + "</a>");
        ui->p2_name->setText("<a href='www. '>" + b + " (WHITE)" + "</a>");

        watch->start();
    }
    else if (chance == 0)
    {
        ui->p1_name->setText("<a href='www. '>" + a + " (BLACK)" + "</a>");
        ui->p2_name->setText("<a href='www. '>" + b + " (WHITE)" + "</a>");
        watch->start();
    }

    QSqlQuery q;
    q.exec("DELETE FROM player_score");
    q.exec("INSERT INTO player_score (id,p2_negative,p1_negative,p2_positive,p1_positive)VALUES(1,0,0,0,0)");

    ui->redo_btn->setEnabled(1);
    ui->double_btn->setEnabled(1);
    ui->undo_btn->setEnabled(1);
    ui->dispen_btn->setEnabled(1);
    ui->save_btn->setEnabled(1);
    ui->load_btn->close();
    ui->load_btn->setEnabled(0);
    ui->view_last_btn->close();
    ui->view_last_btn->setEnabled(0);
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
    game_start_end(0);
}

void MainWindow::on_double_btn_clicked()
{
    is_dual_avctive = 1;
    if (turn == 0)
    {
        int a = ui->p2_negative->text().toInt() - 20;
        //ui->p2_negative->setText(QString::number(a));
        w_score_update(-20);
    }
    if (turn == 1)
    {
        int a = ui->p1_negative->text().toInt() - 20;
        // ui->p1_negative->setText(QString::number(a));
        b_score_update(-20);
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
            // ui->p2_negative->setText(QString::number(a));
            w_score_update(-5);
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
            // ui->p2_negative->setText(QString::number(a));
            w_score_update(-5);
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
            // ui->p1_negative->setText(QString::number(a));
            b_score_update(-5);
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
            //ui->p1_negative->setText(QString::number(a));
            b_score_update(-5);
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
//--------------------------------------------------------
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
//--------------------------------------------------------
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
            QString mov = ui->comboBox_b->itemText(index).toStdString().at(0) + QString::fromStdString(b_move_list.at(b_move_list.size() - 1).toStdString().substr(3, 2) + b_move_list.at(b_move_list.size() - 1).toStdString().substr(3, 2));
            b_move_list.push_back(mov);
        }
    }
    is_soldier_end = 0;
}
//--------------------------------------------------------
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

            QString mov1 = ui->comboBox_w->itemText(index).toStdString().at(0) + QString::fromStdString(w_move_list.at(w_move_list.size() - 1).toStdString().substr(3, 2) + w_move_list.at(w_move_list.size() - 1).toStdString().substr(3, 2));
            w_move_list.push_back(mov1);
        }
    }
    is_soldier_end = 0;
}
//--------------------------------------------------------

void MainWindow::on_save_btn_clicked()
{

    QString fileName;
    fileName = "<" + ui->p1_name->text() + ">-<" + ui->p2_name->text() + ">-<" + ui->game_label2->text() + ">.acd";
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save Advanced Chess game"), "",
                                            tr("chess game (*.acd);;All Files (*)"));

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QString w_mov, b_mov;
    QTextStream out(&file);
    for (int i = 0; i < w_move_list.size(); i++)
    {
        w_mov += 'W' + w_move_list.at(i) + "-";
    }
    for (int i = 0; i < b_move_list.size(); i++)
    {
        b_mov += 'B' + b_move_list.at(i) + "-";
    }

    QString text = w_mov + '#' + b_mov + '*' + ui->p1_name->text() + '-' + ui->p2_name->text() + '-' + ui->game_label2->text();
    out << text;
    file.close();
}

QString filename1 = "";
//----------------------------------------------------------
void MainWindow::on_view_last_btn_clicked()
{
    QDir dir(".");

    QString filedir;
    QString targetStr = ".acd"; // What we search for
    QFileInfoList hitList;		// Container for matches
    QString directory = dir.absolutePath();
    QDirIterator it(directory, QDirIterator::Subdirectories);

    // Iterate through the directory using the QDirIterator
    while (it.hasNext())
    {
        QString filename = it.next();
        QFileInfo file(filename);

        if (file.isDir())
        { // Check if it's a dir
            continue;
        }
        // If the filename contains target string - put it in the hitlist
        if (file.fileName().contains(targetStr, Qt::CaseInsensitive))
        {
            hitList.append(file);
        }
    }

    foreach (QFileInfo hit, hitList)
    {

        if (QString::fromStdString(hit.absoluteFilePath().toStdString().substr(hit.absoluteFilePath().toStdString().size() - 3, 3)) == "acd")
        {
            filedir = hit.absoluteFilePath();
        }
    }
    if (filedir == "")
    {
        QMessageBox *msg = new QMessageBox();
        msg->setText("No File Find in this Directory ! Please start a game first and try again !");
        msg->show();
    }
    else if (filedir != "")
    {
        filename1 = filedir;
        MainWindow::on_load_btn_clicked(1);
    }
}
//--------------------------------------------------------
void MainWindow::on_load_btn_clicked(bool flag = 0)
{
    if (flag == 0) //continue existing game
    {

        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open chess file"), "",
                                                        tr("Advanced Chess file (*.acd);;All Files (*)"));

        QFile file(fileName);
        setWindowTitle(fileName);

        if (!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }

        QTextStream in(&file);

        QString text = in.readAll();
        qDebug() << text;
        is_reveiw_act = 0;
        continue_game(text);

        file.close();
    }
    if (flag == 1 && filename1 != "") //view last game
    {

        QFile file(filename1);
        setWindowTitle(filename1);

        if (!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }

        QTextStream in(&file);

        QString text = in.readAll();
        ::is_reveiw_act = 1;
        continue_game(text);

        file.close();
    }
}

//--------------------------------------------------------

void MainWindow::on_p1_name_linkHovered(const QString &link)
{
    QString pos, neg;
    QSqlQuery q;
    q.exec("SELECT p1_positive , p1_negative FROM player_score WHERE id=1");
    while (q.next())
    {
        pos = q.value(0).toString();
        neg = q.value(1).toString();
    }
    ui->p1_positive->setText(pos);
    ui->p1_negative->setText(neg);
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(q);
}

void MainWindow::on_p2_name_linkHovered(const QString &link)
{
    QString pos, neg;

    QSqlQuery q;
    q.exec("SELECT p2_positive , p2_negative FROM player_score WHERE id=1");
    while (q.next())
    {
        pos = q.value(0).toString();
        neg = q.value(1).toString();
    }
    ui->p2_positive->setText(pos);
    ui->p2_negative->setText(neg);
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(q);
}
