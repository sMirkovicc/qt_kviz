#ifndef GAME_H
#define GAME_H

#include <QtSql>
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
    void init();
    void resetView();

private slots:
    void on_pushButton_insertName_clicked();

    void on_pushButton_quizSelection_clicked();

public slots:
    void quizIdLoading();
    void databaseLoading();

signals:
    void loadQuizId();
    void loadDatabase();
    void openSelection(QString& quizName, int& quizId, QString& name);

private:
    Ui::Game *ui;
    QString m_name;
    QString m_quizName;
    int m_quizId;
};
#endif // GAME_H
