#include "selection.h"
#include "ui_selection.h"
#include "game.h"
#include "highscore.h"
#include <QPixmap>

Selection::Selection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Selection)
{
    ui->setupUi(this);
}

Selection::~Selection()
{
    delete ui;
}

void Selection::Init()
{
    QObject::connect(this, &Selection::loadQuiz, this, &Selection::quizLoading);
    QObject::connect(this, &Selection::play, this, &Selection::playing);
    QObject::connect(this, &Selection::finish, this, &Selection::print);

    QPixmap picture2("://database/picture2.jpg");
    w = ui->label_picture2->width();
    h = ui->label_picture2->height();
    ui->label_picture2->setPixmap(picture2.scaled(w, h, Qt::IgnoreAspectRatio));
    ui->pushButton_highscore->setVisible(false);

    ui->comboBox_answers->setPlaceholderText("--Vas odgovor--");
    ui->comboBox_answers->setCurrentIndex(-1);
}

void Selection::LoadQuizNameAndID(QString quizName, int ID)
{
    quiz.setQuizName(quizName);
    quiz.setQuizID(ID);
    ui->label_quizName->setText(quiz.getQuizName());
    emit Selection::loadQuiz();
}

void Selection::LoadName(QString name)
{
    m_playerName = name;
}

void Selection::ButtonVisibility()
{
    if(indexOfCurrentQuestion == 0)
    {
        ui->pushButton_previous->setVisible(false);
    }
    else
    {
        ui->pushButton_previous->setVisible(true);
    }
    if(indexOfCurrentQuestion == m_size - 1)
    {
        ui->pushButton_next->setVisible(false);
        ui->pushButton_finish->setVisible(true);
    }
    else
    {
        ui->pushButton_next->setVisible(true);
        ui->pushButton_finish->setVisible(false);
    }
}

void Selection::quizLoading()
{
    {
        QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
        //QString dbPath = QCoreApplication::applicationDirPath() + "/kviz.db";
        //qDebug() << dbPath;
        m_db.setDatabaseName("/home/Sara/saraqt/qt_kviz/database/kviz.db");

        if (!m_db.open())
        {
            qDebug() << "Error: connection with database failed";
        }
        else
        {
            qDebug() << "Database: connection ok";
        }
        QSqlQuery query3;
        query3.prepare("SELECT * FROM pitanje WHERE IDKviza = (:quizID)");
        query3.bindValue(":quizID", quiz.getQuizID());
        query3.exec();

        while (query3.next())
        {
            m_DBanswers[0] = query3.value(3).toString();
            m_DBanswers[1] = query3.value(4).toString();
            m_DBanswers[2] = query3.value(5).toString();
            m_DBanswers[3] = query3.value(6).toString();
            Question q(query3.value(0).toInt(), query3.value(1).toInt(), query3.value(2).toString(), m_DBanswers, query3.value(7).toInt());
            m_CollectionOfQuestions.emplace_back(q);
        }
        m_db.close();
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    quiz.setCollectionOfQuestions(m_CollectionOfQuestions);
    m_size = quiz.getCollectionOfQuestions().size();
    m_answer.assign(m_size, 0);

    emit Selection::play();
}

void Selection::playing()
{
    Selection::ButtonVisibility();
    ui->comboBox_answers->clear();
    ui->label_questionNumber->setText("Pitanje " + QString::number(indexOfCurrentQuestion + 1) + ":");
    ui->label_question->setText(quiz.getCollectionOfQuestions()[indexOfCurrentQuestion].getQuestion());
    for (int j = 0; j < 4; j++)
    {
        ui->comboBox_answers->addItem(quiz.getCollectionOfQuestions()[indexOfCurrentQuestion].getAnswer(j));
    }
    ui->comboBox_answers->setCurrentIndex(m_answer[indexOfCurrentQuestion] - 1);
}

void Selection::print()
{
    for(int k = 0; k < m_size; k++)
    {
        if(m_answer[k] == quiz.getCollectionOfQuestions()[k].getCorrectAnswer())
        {
            m_correctAnswers++;
        }
    }

    ui->label_question->setText("Takmicar " + m_playerName + " je pogodio " + QString::number(m_correctAnswers) + "/"
                                + QString::number(m_size) + " pitanja.");
    ui->pushButton_highscore->setVisible(true);
    ui->label_questionNumber->setVisible(false);
    ui->comboBox_answers->setVisible(false);
    ui->pushButton_next->setVisible(false);
    ui->pushButton_previous->setVisible(false);
    ui->pushButton_finish->setVisible(false);
    ui->label_picture2->setVisible(false);
    QPixmap picture3("://database/purple-confetti");
    w = ui->label_confetti->width();
    h = ui->label_confetti->height();
    ui->label_confetti->setPixmap(picture3.scaled(w, h, Qt::IgnoreAspectRatio));

    {
        QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("/home/Sara/saraqt/qt_kviz/database/kviz.db");

        if (!m_db.open())
        {
            qDebug() << "Error: connection with database failed";
        }
        else
        {
            qDebug() << "Database: connection ok";
        }
        QSqlQuery query4;
        query4.prepare("INSERT INTO highscore VALUES ((:playerName), (:quizID), (:points))");
        query4.bindValue(":playerName", m_playerName);
        query4.bindValue(":quizID", quiz.getQuizID());
        query4.bindValue(":points", m_correctAnswers);

        query4.exec();

        m_db.close();
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

}

void Selection::on_pushButton_next_clicked()
{
    m_answer[indexOfCurrentQuestion] = ui->comboBox_answers->currentIndex() + 1;

    indexOfCurrentQuestion++;

    emit Selection::play();
}


void Selection::on_pushButton_previous_clicked()
{
    m_answer[indexOfCurrentQuestion] = ui->comboBox_answers->currentIndex() + 1;

    indexOfCurrentQuestion--;

    emit Selection::play();
}

void Selection::on_pushButton_finish_clicked()
{
    m_answer[indexOfCurrentQuestion] = ui->comboBox_answers->currentIndex() + 1;

    emit Selection::finish();
}


void Selection::on_pushButton_highscore_clicked()
{
    Highscore highscore;
    highscore.Init();
    highscore.setModal(true);
    highscore.exec();
}

