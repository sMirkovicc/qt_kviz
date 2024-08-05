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
    QObject::connect(&game, &Game::openSelection, this, &RootWidget::openingSelection);
    QObject::connect(&selection, &Selection::playAgain, this, &RootWidget::openingGame);
    QObject::connect(&selection, &Selection::openHighscore, this, &RootWidget::openingHighscore);
    QObject::connect(this, &RootWidget::playQuiz, &selection, &Selection::playing);
    QObject::connect(&highscore, &Highscore::goBack, this, &RootWidget::openingSelectionFromHS);

    emit RootWidget::openGame();
}

void RootWidget::openingGame()
{
    if(ui->stackedWidgetR->indexOf(&game) == -1)
    {
        ui->stackedWidgetR->addWidget(&game);
        game.init();
    }
    game.resetView();
    ui->stackedWidgetR->setCurrentWidget(&game);
}

void RootWidget::openingSelection(QString& quizName, int quizId, QString& name)
{
    if(ui->stackedWidgetR->indexOf(&selection) == -1)
    {
       ui->stackedWidgetR->addWidget(&selection);
        selection.init();
    }
    selection.resetView();
    selection.loadQuizNameAndId(quizName, quizId);
    selection.setName(name);
    ui->stackedWidgetR->setCurrentWidget(&selection);
    emit playQuiz();
}

void RootWidget::openingHighscore()
{
    if(ui->stackedWidgetR->indexOf(&highscore) == -1)
    {
        ui->stackedWidgetR->addWidget(&highscore);
        highscore.init();
    }
    highscore.resetView();
    ui->stackedWidgetR->setCurrentWidget(&highscore);
}

void RootWidget::openingSelectionFromHS()
{
    ui->stackedWidgetR->setCurrentWidget(&selection);
}
