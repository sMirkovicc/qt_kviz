#include "rootwidget.h"
#include "qstackedwidget.h"
#include "ui_rootwidget.h"

RootWidget::RootWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RootWidget)
{
    ui->setupUi(this);
}

RootWidget::~RootWidget()
{
    delete ui;
}

void RootWidget::init()
{
    QObject::connect(this, &RootWidget::openGame, this, &RootWidget::openingGame);
    QObject::connect(&game, SIGNAL(openSelection(QString,int,QString)), this, SLOT(openingSelection(QString,int,QString)));
    QObject::connect(&selection, SIGNAL(playAgain()), this, SLOT(openingGame()));
    QObject::connect(&selection, SIGNAL(openHighscore()), this, SLOT(openingHighscore()));
    QObject::connect(this, SIGNAL(playQuiz()), &selection, SLOT(playing()));

    emit RootWidget::openGame();
}

void RootWidget::openingGame()
{
    if(gameIterator == 0)
    {
        ui->stackedWidgetR->addWidget(&game);
    }
    game.init();
    gameIterator++;
    ui->stackedWidgetR->setCurrentWidget(&game);
}

void RootWidget::openingSelection(QString quizName, int quizId, QString name)
{
    selection.init();
    selection.loadQuizNameAndId(quizName, quizId);
    selection.setName(name);
    ui->stackedWidgetR->addWidget(&selection);
    ui->stackedWidgetR->setCurrentWidget(&selection);
    emit playQuiz();
}

void RootWidget::openingHighscore()
{
    highscore.init();
    ui->stackedWidgetR->addWidget(&highscore);
    ui->stackedWidgetR->setCurrentWidget(&highscore);
}
