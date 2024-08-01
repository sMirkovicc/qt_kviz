#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

#define NUMBER_OF_ANSWERS 4

class Question
{
private:
    int m_questionId;
    int m_quizId;
    QString m_question;
    QString m_arrayOfAnswers[NUMBER_OF_ANSWERS];
    int m_correctAnswer;
public:
    Question();

    Question(int questionId, int quizId, QString question, QString arrayOfAnswers[NUMBER_OF_ANSWERS], int correctAnswer);

    ~Question();

    Question(const Question& original);

    void setQuestionId(int& questionId);
    int getQuestionId() const;

    void setQuizId(int& quizId);
    int getQuizId() const;

    void setQuestion(QString& question);
    QString getQuestion() const;

    void setAnswer(int i, QString& answer);
    QString getAnswer(int i) const;

    bool setCorrectAnswer(int& correctAnswer);
    int getCorrectAnswer() const;
};

#endif // QUESTION_H
