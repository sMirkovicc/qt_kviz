#ifndef ROOTWIDGET_H
#define ROOTWIDGET_H

#include <QDialog>
#include <QObject>
#include "game.h"
#include "selection.h"
#include "highscore.h"

namespace Ui {
class RootWidget;
}

class RootWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RootWidget(QWidget *parent = nullptr);
    ~RootWidget();
    void init();

private slots:
    void openingGame();
    void openingSelection(QString& quizName, int quizId, QString& name);
    void openingHighscore();
    void openingSelectionFromHS();

signals:
    void openGame();
    void playQuiz();

private:
    Ui::RootWidget *ui;
    Game game;
    Selection selection;
    Highscore highscore;
};

#endif // ROOTWIDGET_H
