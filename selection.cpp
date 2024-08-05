#include "selection.h"
#include "ui_selection.h"
#include <QPixmap>
#include <QStringList>
#include <QtSql>

Selection::Selection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Selection)
{
    ui->setupUi(this);
}

Selection::~Selection()
{
    delete ui;
    if(item != nullptr)
    {
        delete item;
    }
    if(bMapper != nullptr)
    {
        delete bMapper;
    }
}

void Selection::init()
{
    QObject::connect(this, &Selection::loadQuiz, this, &Selection::quizLoading);
    QObject::connect(this, &Selection::play, this, &Selection::playing);
    QObject::connect(this, &Selection::finish, this, &Selection::print);

    bMapper = new QSignalMapper;
    connect(bMapper, &QSignalMapper::mappedInt, this, &Selection::nextStep);
    connect(ui->pushButton_previous, &QPushButton::clicked, bMapper, qOverload<>(&QSignalMapper::map));
    bMapper->setMapping(ui->pushButton_previous, PREVIOUS_QUESTION);
    connect(ui->pushButton_next, &QPushButton::clicked, bMapper, qOverload<>(&QSignalMapper::map));
    bMapper->setMapping(ui->pushButton_next, NEXT_QUESTION);

    QPixmap backgroundPicture("://assets/picture2.jpg");
    w = ui->label_picture2->width();
    h = ui->label_picture2->height();
    ui->label_picture2->setPixmap(backgroundPicture.scaled(w, h, Qt::IgnoreAspectRatio));

    QPixmap purpleConfettiPicture("://assets/purple-confetti");
    w = ui->label_confetti->width();
    h = ui->label_confetti->height();
    ui->label_confetti->setPixmap(purpleConfettiPicture.scaled(w, h, Qt::IgnoreAspectRatio));
}

void Selection::resetView()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->label_picture2->setVisible(true);
    ui->label_confetti->setVisible(false);
    ui->label_unansweredQuestions->setVisible(false);
    ui->label_unansweredQuestions2->setVisible(false);
    ui->pushButton_finishUnanswered->setVisible(false);
    ui->pushButton_dontFinish->setVisible(false);
    ui->pushButton_finish->setVisible(true);
    ui->comboBox_answers->setDisabled(false);

    ui->comboBox_answers->setPlaceholderText("--Vas odgovor--");
    ui->comboBox_answers->setCurrentIndex(-1);
}

void Selection::loadQuizNameAndId(QString& quizName, int ID)
{
    quiz.setQuizName(quizName);
    quiz.setQuizId(ID);
    ui->label_quizName->setText(quiz.getQuizName());
    emit Selection::loadQuiz();
}

void Selection::setName(QString& name)
{
    m_playerName = name;
}

void Selection::buttonVisibility()
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
    }
    else
    {
        ui->pushButton_next->setVisible(true);
    }
}

void Selection::quizLoading()
{
    QSqlQuery selectAllQuizValuesQuery;
    selectAllQuizValuesQuery.prepare("SELECT * FROM pitanje WHERE IDKviza = (:quizId)");
    selectAllQuizValuesQuery.bindValue(":quizId", quiz.getQuizId());
    selectAllQuizValuesQuery.exec();

    while (selectAllQuizValuesQuery.next())
    {
        for(int i = 0; i < NUMBER_OF_ANSWERS; i++)
        {
            m_DBanswers[i] = selectAllQuizValuesQuery.value(i + 3).toString();
        }
        Question q(selectAllQuizValuesQuery.value(0).toInt(), selectAllQuizValuesQuery.value(1).toInt(),
                   selectAllQuizValuesQuery.value(2).toString(), m_DBanswers, selectAllQuizValuesQuery.value(NUMBER_OF_ANSWERS + 3).toInt());
        m_CollectionOfQuestions.emplace_back(q);
    }
    quiz.setCollectionOfQuestions(m_CollectionOfQuestions);
    m_size = quiz.getCollectionOfQuestions().size();
    m_answer.assign(m_size, 0);
}

void Selection::playing()
{
    Selection::buttonVisibility();
    ui->comboBox_answers->clear();
    ui->label_questionNumber->setText("Pitanje " + QString::number(indexOfCurrentQuestion + 1) + ":");
    ui->label_question->setText(quiz.getCollectionOfQuestions()[indexOfCurrentQuestion].getQuestion());
    for (int i = 0; i < NUMBER_OF_ANSWERS; i++)
    {
        ui->comboBox_answers->addItem(quiz.getCollectionOfQuestions()[indexOfCurrentQuestion].getAnswer(i));
    }
    ui->comboBox_answers->setCurrentIndex(m_answer[indexOfCurrentQuestion] - 1);
}

void Selection::print()
{
    for(int i = 0; i < m_size; i++)
    {
        if(m_answer[i] == quiz.getCollectionOfQuestions()[i].getCorrectAnswer())
        {
            m_correctAnswers++;
        }
    }

    ui->stackedWidget->setCurrentIndex(1);
    ui->label_correctQuestions->setText("Takmicar " + m_playerName + " je pogodio " + QString::number(m_correctAnswers) + "/"
                                + QString::number(m_size) + " pitanja.");

    ui->label_picture2->setVisible(false);
    ui->label_confetti->setVisible(true);

    ui->tableWidget->setRowCount(m_size);
    ui->tableWidget->setColumnCount(2);
    QStringList hLabels;
    hLabels << "Pitanje" << "Odgovor";
    ui->tableWidget->setHorizontalHeaderLabels(hLabels);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            item = new QTableWidgetItem;
            if(j == 0)
            {
                item->setText(quiz.getCollectionOfQuestions()[i].getQuestion());
            }
            if(j == 1)
            {
                if(m_answer[i] == quiz.getCollectionOfQuestions()[i].getCorrectAnswer())
                {
                    item->setText("Tacan");
                }
                else
                {
                    item->setText("Netacan");
                }
            }
            ui->tableWidget->setItem(i, j, item);
        }
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QSqlQuery insertIntoHighscoreQuery;
    insertIntoHighscoreQuery.prepare("INSERT INTO highscore VALUES ((:playerName), (:quizId), (:points))");
    insertIntoHighscoreQuery.bindValue(":playerName", m_playerName);
    insertIntoHighscoreQuery.bindValue(":quizId", quiz.getQuizId());
    insertIntoHighscoreQuery.bindValue(":points", m_correctAnswers);

    insertIntoHighscoreQuery.exec();
}

void Selection::nextStep(int step)
{
    Step value = static_cast<Step>(step);
    m_answer[indexOfCurrentQuestion] = ui->comboBox_answers->currentIndex() + 1;
    if(value == PREVIOUS_QUESTION)
    {
        indexOfCurrentQuestion--;
    }
    else if(value == NEXT_QUESTION)
    {
        indexOfCurrentQuestion++;
    }
    emit Selection::play();
}


void Selection::on_pushButton_finish_clicked()
{
    m_answer[indexOfCurrentQuestion] = ui->comboBox_answers->currentIndex() + 1;

    bool check = false;
    for(int i = 0; i < m_size; i++)
    {
        if(m_answer[i] == 0)
        {
            check = true;
            break;
        }
    }
    if(check)
    {
        ui->label_unansweredQuestions->setVisible(true);
        ui->label_unansweredQuestions2->setVisible(true);
        ui->pushButton_finishUnanswered->setVisible(true);
        ui->pushButton_dontFinish->setVisible(true);
        ui->pushButton_finish->setVisible(false);
        ui->pushButton_previous->setVisible(false);
        ui->pushButton_next->setVisible(false);
        ui->comboBox_answers->setDisabled(true);
    }
    else
    {
        emit Selection::finish();
    }
}


void Selection::on_pushButton_highscore_clicked()
{
    emit openHighscore();
}


void Selection::on_pushButton_finishUnanswered_clicked()
{
    emit Selection::finish();
}


void Selection::on_pushButton_dontFinish_clicked()
{
    ui->label_unansweredQuestions->setVisible(false);
    ui->label_unansweredQuestions2->setVisible(false);
    ui->pushButton_finishUnanswered->setVisible(false);
    ui->pushButton_dontFinish->setVisible(false);
    ui->pushButton_finish->setVisible(true);
    Selection::buttonVisibility();
    ui->comboBox_answers->setDisabled(false);
}


void Selection::on_pushButton_playAgain_clicked()
{
    indexOfCurrentQuestion = 0;
    m_CollectionOfQuestions.clear();
    m_correctAnswers = 0;
    emit playAgain();
}

