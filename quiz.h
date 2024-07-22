#include "question.h"
#include <vector>

#ifndef QUIZ_H
#define QUIZ_H

class Quiz
{
private:
    int m_QuizID;
    QString m_QuizName;
    std::vector<Question> m_CollectionOfQuestions;
public:
    Quiz();

    Quiz(int QuizID, QString QuizName, std::vector<Question> CollectionOfQuestions);

    ~Quiz();

    Quiz(const Quiz& original);

    void setQuizID(int QuizID);
    int getQuizID();

    void setQuizName(QString QuizName);
    QString getQuizName();

    void setCollectionOfQuestions(std::vector<Question>& CollectionOfQuestions);
    std::vector<Question> getCollectionOfQuestions();
};

#endif // QUIZ_H
