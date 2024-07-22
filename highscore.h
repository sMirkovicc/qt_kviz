#include <QtSql>

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>
#include <QObject>

namespace Ui {
class Highscore;
}

class Highscore : public QDialog
{
    Q_OBJECT

public:
    explicit Highscore(QWidget *parent = nullptr);
    ~Highscore();
    void Init();

private slots:
    void on_pushButton_selectQuiz_clicked();

public slots:
    void quizNameLoading();
    void quizIDLoading();
    void highscoreLoading();

signals:
    void loadQuizName();
    void loadQuizID();
    void loadHighscore();

private:
    Ui::Highscore *ui;
    QString m_quizName;
    int m_QuizID;
    QSqlQueryModel* model;
};

#endif // HIGHSCORE_H
