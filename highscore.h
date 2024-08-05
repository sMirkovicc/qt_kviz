#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QWidget>
#include <QObject>
#include <QtSql>

namespace Ui {
class Highscore;
}

class Highscore : public QWidget
{
    Q_OBJECT

public:
    explicit Highscore(QWidget *parent = nullptr);
    ~Highscore();
    void init();
    void resetView();

private slots:
    void on_pushButton_selectQuiz_clicked();

    void on_pushButton_goBack_clicked();

public slots:
    void quizNameLoading();
    void quizIdLoading();
    void highscoreLoading();

signals:
    void loadQuizName();
    void loadQuizId();
    void loadHighscore();
    void goBack();

private:
    Ui::Highscore *ui;
    QString m_quizName;
    int m_QuizId;
};

#endif // HIGHSCORE_H
