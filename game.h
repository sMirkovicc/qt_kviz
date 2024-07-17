#include <QtSql>

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    void Init();

private slots:
    void on_pushButton_InsertName_clicked();

    void on_pushButton_QuizSelection_clicked();

public slots:
    void quizIDLoading();
    void databaseLoading();

signals:
    void loadQuizID();
    void loadDatabase();

private:
    Ui::Game *ui;
    QString m_name;
    QString m_quizName;
    int m_QuizID;

};
#endif // GAME_H
