#ifndef SELECTION_H
#define SELECTION_H

#include "quiz.h"
#include "question.h"

#include <QDialog>
#include <QObject>
#include <QSignalMapper>
#include <QTableWidget>

#define NUMBER_OF_ANSWERS 4

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
    void resetView();
    void loadQuizNameAndId(QString& quizName, int ID);
    void setName(QString& name);
    void buttonVisibility();
    enum Step{NEXT_QUESTION, PREVIOUS_QUESTION};

private slots:
    void on_pushButton_finish_clicked();

    void on_pushButton_highscore_clicked();

    void on_pushButton_finishUnanswered_clicked();

    void on_pushButton_dontFinish_clicked();

    void nextStep(int);

    void on_pushButton_playAgain_clicked();

public slots:
    void quizLoading();
    void playing();
    void print();

signals:
    void loadQuiz();
    void play();
    void finish();
    void playAgain();
    void openHighscore();

private:
    Ui::Selection *ui;
    Quiz quiz;
    QString m_playerName;
    QString m_DBanswers[NUMBER_OF_ANSWERS];
    std::vector<Question> m_CollectionOfQuestions;
    int m_size = 0;
    int indexOfCurrentQuestion = 0;
    std::vector<int> m_answer;
    int m_correctAnswers = 0;
    QTableWidgetItem* item = nullptr;
    int w;
    int h;
};

#endif // SELECTION_H
