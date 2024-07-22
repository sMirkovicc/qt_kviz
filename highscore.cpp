#include "highscore.h"
#include "ui_highscore.h"
#include <QPixmap>

Highscore::Highscore(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Highscore)
{
    ui->setupUi(this);
}

Highscore::~Highscore()
{
    delete ui;
    delete model;
}

void Highscore::Init()
{
    QObject::connect(this, &Highscore::loadQuizName, this, &Highscore::quizNameLoading);
    QObject::connect(this, &Highscore::loadQuizID, this, &Highscore::quizIDLoading);
    QObject::connect(this, &Highscore::loadHighscore, this, &Highscore::highscoreLoading);

    QPixmap picture("://database/picture.jpg");
    int w = ui->label_picture->width();
    int h = ui->label_picture->height();
    ui->label_picture->setPixmap(picture.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->comboBox_quiz->setPlaceholderText("--Vas izbor--");
    ui->comboBox_quiz->setCurrentIndex(-1);

    ui->tableView->setVisible(false);
    ui->label_2->setVisible(false);

    emit Highscore::loadQuizName();
}

void Highscore::quizNameLoading()
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

        QSqlQuery query5("SELECT * FROM kviz");
        int idName = query5.record().indexOf("Naziv");
        while (query5.next())
        {
            ui->comboBox_quiz->addItem(query5.value(idName).toString());
        }
        m_db.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void Highscore::quizIDLoading()
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
        QSqlQuery query6;
        query6.prepare("SELECT IDKviza FROM kviz WHERE Naziv = (:name)");
        query6.bindValue(":name", m_quizName);

        if (query6.exec())
        {
            if (query6.next())
            {
                m_QuizID = query6.value(0).toInt();
            }
        }
        m_db.close();
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    emit Highscore::loadHighscore();
}

void Highscore::highscoreLoading()
{
    {
        ui->tableView->setVisible(true);
        ui->label_2->setVisible(true);

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
        QSqlQuery query7;
        query7.prepare("SELECT ImeIgraca AS [Ime igraca], BrojPoena AS [Broj poena] FROM highscore WHERE IDKviza = (:quizID) ORDER BY BrojPoena DESC LIMIT 3");
        query7.bindValue(":quizID", m_QuizID);
        query7.exec();

        model = new QSqlQueryModel();
        model->setQuery(query7);
        ui->tableView->setModel(model);

        m_db.close();
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void Highscore::on_pushButton_selectQuiz_clicked()
{
    if(ui->comboBox_quiz->currentIndex() != -1)
    {
        m_quizName = ui->comboBox_quiz->currentText();

        emit Highscore::loadQuizID();
    }
}

