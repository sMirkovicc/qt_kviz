#include "game.h"
#include "quiz.h"
#include "question.h"

#ifndef SELECTION_H
#define SELECTION_H

#include <QDialog>
#include <QObject>

namespace Ui {
class Selection;
}

class Selection : public QDialog
{
    Q_OBJECT

public:
    explicit Selection(QWidget *parent = nullptr);
    ~Selection();
    void Init();
    void LoadQuizNameAndID(QString quizName, int ID);
    void LoadName(QString name);
    void ButtonVisibility();

private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

    void on_pushButton_finish_clicked();

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
    Game game;
    QString m_playerName;
    QString m_DBanswers[4];
    std::vector<Question> m_CollectionOfQuestions;
    int m_size = 0;
    int indexOfCurrentQuestion = 0;
    std::vector<int> m_answer;
    int m_correctAnswers = 0;
    int w;
    int h;
};

#endif // SELECTION_H
