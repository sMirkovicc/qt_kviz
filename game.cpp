#include "game.h"
#include "ui_game.h"
#include "selection.h"
#include <QPixmap>

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::Init()
{
    QObject::connect(this, &Game::loadQuizID, this, &Game::quizIDLoading);
    QObject::connect(this, &Game::loadDatabase, this, &Game::databaseLoading);

    QPixmap picture("://database/picture.jpg");
    int w = ui->label_picture->width();
    int h = ui->label_picture->height();
    ui->label_picture->setPixmap(picture.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->pushButton_QuizSelection->setVisible(false);
    ui->comboBox_quizSelection->setVisible(false);
    ui->label_2->setVisible(false);
}

void Game::databaseLoading()
{
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

        QSqlQuery query("SELECT * FROM kviz");
        int idName = query.record().indexOf("Naziv");
        while (query.next())
        {
            ui->comboBox_quizSelection->addItem(query.value(idName).toString());
        }
        m_db.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    ui->comboBox_quizSelection->setPlaceholderText("--Izaberite zeljeni kviz--");
    ui->comboBox_quizSelection->setCurrentIndex(-1);
}

void Game::quizIDLoading()
{
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
        QSqlQuery query1;
        query1.prepare("SELECT IDKviza FROM kviz WHERE Naziv = (:name)");
        query1.bindValue(":name", m_quizName);

        if (query1.exec())
        {
            if (query1.next())
            {
                m_QuizID = query1.value(0).toInt();
            }
        }
        m_db.close();
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    Selection selection;
    selection.Init();
    selection.LoadQuizNameAndID(m_quizName, m_QuizID);
    selection.LoadName(m_name);
    selection.setModal(true);
    selection.exec();
}

void Game::on_pushButton_InsertName_clicked()
{
    if(ui->insertName->text() != "")
    {
        m_name = ui->insertName->text();

        ui->pushButton_InsertName->setDisabled(true);
        ui->pushButton_QuizSelection->setVisible(true);
        ui->comboBox_quizSelection->setVisible(true);
        ui->label_2->setVisible(true);

        emit Game::loadDatabase();
    }
}

void Game::on_pushButton_QuizSelection_clicked()
{
    if(ui->comboBox_quizSelection->currentIndex() != -1)
    {
        m_quizName = ui->comboBox_quizSelection->currentText();

        emit Game::loadQuizID();
    }
}

