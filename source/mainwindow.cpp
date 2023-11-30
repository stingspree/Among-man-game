#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("pac-man"));

    /* Initialize graphicsview and game scene */
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    QColor customColor;
    customColor.setRgb(131,161,170);
    ui->graphicsView->setBackgroundBrush(customColor);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);

    int map_height = 20, map_width = 29;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt");
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


/* Initialize UI */
void MainWindow::initLabels()
{
    score_title = new QLabel(this);
    score_title->setText("Score");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score_title->setGeometry(550, 12, 60, 26);

    highscore = new QLabel(this);
    highscore->setText("High Score");
    highscore->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 16px;}");
    highscore->setGeometry(50, 12, 100, 26);

    score = new QLabel(this);
    score->setIndent(-80);
    score->setText("0");
    score->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score->setGeometry(600, 12, 150, 26);

    hscore = new QLabel(this);
    hscore->setText("0");
    hscore->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 16px;}");
    hscore->setGeometry(135, 12, 150, 26);

    win_label = new QLabel(this);
    win_label->hide();
    win_label->setText("You win!");
    win_label->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 16px;}");
    win_label->setGeometry(310, 12, 150, 26);

    lose_label = new QLabel(this);
    lose_label->hide();
    lose_label->setText("You lose!");
    lose_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    lose_label->setGeometry(310, 12, 150, 26);


    score_timer = new QTimer(this);
    score_timer->start(25);
    connect(score_timer, SIGNAL(timeout()), this , SLOT(update_score()));
}


/* Update score UI */
void MainWindow::update_score()
{
    score->setText(QString::number(game->get_score()));
    if (game->stat == Game::Win) {
        win_label->show();
        score_timer->stop();
    } else if (game->stat == Game::Lose) {
        lose_label->show();
        score_timer->stop();
        hscore->setText(QString::number(game->get_score()));
    }
}


void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:
        game->pacman_next_direction(GameObject::Up);
        break;
    case Qt::Key_A:
        game->pacman_next_direction(GameObject::Left);
        break;
    case Qt::Key_S:
        game->pacman_next_direction(GameObject::Down);
        break;
    case Qt::Key_D:
        game->pacman_next_direction(GameObject::Right);
    case Qt::Key_Up:
        game->pacman_next_direction(GameObject::Up);
        break;
    case Qt::Key_Left:
        game->pacman_next_direction(GameObject::Left);
        break;
    case Qt::Key_Down:
        game->pacman_next_direction(GameObject::Down);
        break;
    case Qt::Key_Right:
        game->pacman_next_direction(GameObject::Right);
        break;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

