#include "highscore.h"
#include "ui_highscore.h"
#include "dbmanager.h"
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

void Highscore::init()
{
    QObject::connect(this, &Highscore::loadQuizName, this, &Highscore::quizNameLoading);
    QObject::connect(this, &Highscore::loadQuizId, this, &Highscore::quizIdLoading);
    QObject::connect(this, &Highscore::loadHighscore, this, &Highscore::highscoreLoading);

    QPixmap backgroundPicture("://assets/picture.jpg");
    int w = ui->label_picture->width();
    int h = ui->label_picture->height();
    ui->label_picture->setPixmap(backgroundPicture.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->comboBox_quiz->setPlaceholderText("--Vas izbor--");
    ui->comboBox_quiz->setCurrentIndex(-1);

    ui->tableView->setVisible(false);
    ui->label_2->setVisible(false);

    emit Highscore::loadQuizName();
}

void Highscore::quizNameLoading()
{
    QSqlQuery selectAllQuizesHSQuery("SELECT * FROM kviz");
    int idName = selectAllQuizesHSQuery.record().indexOf("Naziv");
    while (selectAllQuizesHSQuery.next())
    {
        ui->comboBox_quiz->addItem(selectAllQuizesHSQuery.value(idName).toString());
    }
}

void Highscore::quizIdLoading()
{
    QSqlQuery selectQuizIdQuery;
    selectQuizIdQuery.prepare("SELECT IDKviza FROM kviz WHERE Naziv = (:name)");
    selectQuizIdQuery.bindValue(":name", m_quizName);

    if (selectQuizIdQuery.exec())
    {
        if (selectQuizIdQuery.next())
        {
            m_QuizId = selectQuizIdQuery.value(0).toInt();
        }
    }

    emit Highscore::loadHighscore();
}

void Highscore::highscoreLoading()
{

    ui->tableView->setVisible(true);
    ui->label_2->setVisible(true);

    QSqlQuery selectForHighscoreQuery;
    selectForHighscoreQuery.prepare("SELECT ImeIgraca AS [Ime igraca], BrojPoena AS [Broj poena] FROM highscore WHERE IDKviza = (:quizId) ORDER BY BrojPoena DESC LIMIT 3");
    selectForHighscoreQuery.bindValue(":quizId", m_QuizId);
    selectForHighscoreQuery.exec();

    model = new QSqlQueryModel();
    model->setQuery(std::move(selectForHighscoreQuery));
    ui->tableView->setModel(model);
    QHeaderView* vheader = ui->tableView->verticalHeader();
    vheader->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView* hheader=ui->tableView->horizontalHeader();
    hheader->setSectionResizeMode(QHeaderView::Stretch);
}

void Highscore::on_pushButton_selectQuiz_clicked()
{
    if(ui->comboBox_quiz->currentIndex() != -1)
    {
        m_quizName = ui->comboBox_quiz->currentText();

        emit Highscore::loadQuizId();
    }
}

