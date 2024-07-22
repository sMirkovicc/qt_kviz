#include "game.h"
#include "ui_game.h"
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

void Game::init()
{
    QObject::connect(this, &Game::loadQuizId, this, &Game::quizIdLoading);
    QObject::connect(this, &Game::loadDatabase, this, &Game::databaseLoading);

    QPixmap picture("://database/picture.jpg");
    int w = ui->label_picture->width();
    int h = ui->label_picture->height();
    ui->label_picture->setPixmap(picture.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->pushButton_quizSelection->setVisible(false);
    ui->comboBox_quizSelection->setVisible(false);
    ui->label_2->setVisible(false);
}

void Game::databaseLoading()
{
    QSqlQuery printQuizNamesQuery("SELECT * FROM kviz");
    int idName = printQuizNamesQuery.record().indexOf("Naziv");
    while (printQuizNamesQuery.next())
    {
        ui->comboBox_quizSelection->addItem(printQuizNamesQuery.value(idName).toString());
    }

    ui->comboBox_quizSelection->setPlaceholderText("--Izaberite zeljeni kviz--");
    ui->comboBox_quizSelection->setCurrentIndex(-1);
}

void Game::quizIdLoading()
{
    QSqlQuery selectQuizIdQuery;
    selectQuizIdQuery.prepare("SELECT IDKviza FROM kviz WHERE Naziv = (:name)");
    selectQuizIdQuery.bindValue(":name", m_quizName);

    if (selectQuizIdQuery.exec())
    {
        if (selectQuizIdQuery.next())
        {
            m_quizId = selectQuizIdQuery.value(0).toInt();
        }
    }

    selection.init();
    selection.loadQuizNameAndId(m_quizName, m_quizId);
    selection.setName(m_name);
    ui->stackedWidget->insertWidget(1, &selection);
    ui->stackedWidget->setCurrentIndex(1);
}

void Game::on_pushButton_insertName_clicked()
{
    if(ui->insertName->text().trimmed() != "")
    {
        m_name = ui->insertName->text();

        ui->pushButton_insertName->setDisabled(true);
        ui->pushButton_quizSelection->setVisible(true);
        ui->comboBox_quizSelection->setVisible(true);
        ui->label_2->setVisible(true);

        emit Game::loadDatabase();
    }
}

void Game::on_pushButton_quizSelection_clicked()
{
    if(ui->comboBox_quizSelection->currentIndex() != -1)
    {
        m_quizName = ui->comboBox_quizSelection->currentText();

        emit Game::loadQuizId();
    }
}
