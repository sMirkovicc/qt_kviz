#ifndef QUIZ_H
#define QUIZ_H

#include "question.h"
#include <vector>

class Quiz
{
private:
    int m_quizId;
    QString m_quizName;
    std::vector<Question> m_collectionOfQuestions;
public:
    Quiz();

    Quiz(int quizId, QString quizName, std::vector<Question> collectionOfQuestions);

    ~Quiz();

    Quiz(const Quiz& original);

    void setQuizId(int& quizId);
    int getQuizId();

    void setQuizName(QString& quizName);
    QString getQuizName();

    void setCollectionOfQuestions(std::vector<Question> collectionOfQuestions);
    std::vector<Question>& getCollectionOfQuestions();
};

#endif // QUIZ_H
