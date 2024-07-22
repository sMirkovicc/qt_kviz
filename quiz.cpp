#include "quiz.h"

Quiz::Quiz() {}

Quiz::Quiz(int QuizId, QString QuizName, std::vector<Question> CollectionOfQuestions)
    : m_QuizId(QuizId), m_QuizName(QuizName), m_CollectionOfQuestions(CollectionOfQuestions)
{

}

Quiz::~Quiz() {}

Quiz::Quiz(const Quiz& original)
    : m_QuizId(original.m_QuizId), m_QuizName(original.m_QuizName), m_CollectionOfQuestions(original.m_CollectionOfQuestions)
{

}

void Quiz::setQuizId(int QuizId)
{
    m_QuizId = QuizId;
}
int Quiz::getQuizId()
{
    return m_QuizId;
}

void Quiz::setQuizName(QString QuizName)
{
    m_QuizName = QuizName;
}
QString Quiz::getQuizName()
{
    return m_QuizName;
}

void Quiz::setCollectionOfQuestions(std::vector<Question>& CollectionOfQuestions)
{
    m_CollectionOfQuestions = CollectionOfQuestions;
}
std::vector<Question> Quiz::getCollectionOfQuestions()
{
    return m_CollectionOfQuestions;
}
