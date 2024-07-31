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

private slots:
    void on_pushButton_selectQuiz_clicked();

public slots:
    void quizNameLoading();
    void quizIdLoading();
    void highscoreLoading();

signals:
    void loadQuizName();
    void loadQuizId();
    void loadHighscore();

private:
    Ui::Highscore *ui;
    QString m_quizName;
    int m_QuizId;
    QSqlQueryModel* model;
    int highscoreIterator = 0;
};

#endif // HIGHSCORE_H
