#include <QString>

#ifndef QUESTION_H
#define QUESTION_H

class Question
{
private:
    int m_QuestionID;
    int m_QuizID;
    QString m_Question;
    QString m_ArrayOfAnswers[4];
    int m_CorrectAnswer;
public:
    Question();

    Question(int QuestionID, int QuizID, QString Question, QString ArrayOfAnswers[4], int CorrectAnswer);

    ~Question();

    Question(const Question& original);

    void setQuestionID(int QuestionID);
    int getQuestionID();

    void setQuizID(int QuizID);
    int getQuizID();

    void setQuestion(QString Question);
    QString getQuestion();

    void setAnswer(int i, QString Answer);
    QString getAnswer(int i);

    bool setCorrectAnswer(int CorrectAnswer);
    int getCorrectAnswer();
};

#endif // QUESTION_H
