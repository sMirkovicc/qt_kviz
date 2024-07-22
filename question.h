#include <QString>

#ifndef QUESTION_H
#define QUESTION_H

#define numberOfAnswers 4

class Question
{
private:
    int m_QuestionId;
    int m_QuizId;
    QString m_Question;
    QString m_ArrayOfAnswers[numberOfAnswers];
    int m_CorrectAnswer;
public:
    Question();

    Question(int QuestionId, int QuizId, QString Question, QString ArrayOfAnswers[numberOfAnswers], int CorrectAnswer);

    ~Question();

    Question(const Question& original);

    void setQuestionId(int QuestionId);
    int getQuestionId();

    void setQuizId(int QuizId);
    int getQuizId();

    void setQuestion(QString Question);
    QString getQuestion();

    void setAnswer(int i, QString Answer);
    QString getAnswer(int i);

    bool setCorrectAnswer(int CorrectAnswer);
    int getCorrectAnswer();
};

#endif // QUESTION_H
