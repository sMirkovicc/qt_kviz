#include "quiz.h"

Quiz::Quiz() {}

Quiz::Quiz(int quizId, QString quizName, std::vector<Question> collectionOfQuestions)
    : m_quizId(quizId), m_quizName(quizName), m_collectionOfQuestions(collectionOfQuestions)
{

}

Quiz::~Quiz() {}

Quiz::Quiz(const Quiz& original)
    : m_quizId(original.m_quizId), m_quizName(original.m_quizName), m_collectionOfQuestions(original.m_collectionOfQuestions)
{

}

void Quiz::setQuizId(int& quizId)
{
    m_quizId = quizId;
}
int Quiz::getQuizId() const
{
    return m_quizId;
}

void Quiz::setQuizName(QString& quizName)
{
    m_quizName = quizName;
}
QString Quiz::getQuizName() const
{
    return m_quizName;
}

void Quiz::setCollectionOfQuestions(std::vector<Question>& collectionOfQuestions)
{
    m_collectionOfQuestions = collectionOfQuestions;
}
std::vector<Question> Quiz::getCollectionOfQuestions() const
{
    return m_collectionOfQuestions;
}
