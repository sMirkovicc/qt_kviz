//#include "game.h"
#include "quiz.h"
#include "question.h"
#include "highscore.h"

#ifndef SELECTION_H
#define SELECTION_H

#include <QDialog>
#include <QObject>
#include <QSignalMapper>

#define numberOfAnswers 4

namespace Ui {
class Selection;
}

class Selection : public QDialog
{
    Q_OBJECT

public:
    explicit Selection(QWidget *parent = nullptr);
    ~Selection();
    void init();
    void loadQuizNameAndId(QString quizName, int ID);
    void setName(QString name);
    void buttonVisibility();

private slots:
    void on_pushButton_finish_clicked();

    void on_pushButton_highscore_clicked();

    void on_pushButton_finishUnanswered_clicked();

    void on_pushButton_dontFinish_clicked();

    void nextStep(int);

public slots:
    void quizLoading();
    void playing();
    void print();


signals:
    void loadQuiz();
    void play();
    void finish();

private:
    Ui::Selection *ui;
    Quiz quiz;
    Highscore highscore;
    QString m_playerName;
    QString m_DBanswers[numberOfAnswers];
    std::vector<Question> m_CollectionOfQuestions;
    int m_size = 0;
    int indexOfCurrentQuestion = 0;
    std::vector<int> m_answer;
    int m_correctAnswers = 0;
    int w;
    int h;

};

#endif // SELECTION_H
