#include "quiz.h"

Quiz::Quiz() {}

Quiz::Quiz(int QuizID, QString QuizName, std::vector<Question> CollectionOfQuestions)
    : m_QuizID(QuizID), m_QuizName(QuizName), m_CollectionOfQuestions(CollectionOfQuestions)
{

}

Quiz::~Quiz() {}

Quiz::Quiz(const Quiz& original)
    : m_QuizID(original.m_QuizID), m_QuizName(original.m_QuizName), m_CollectionOfQuestions(original.m_CollectionOfQuestions)
{

}

void Quiz::setQuizID(int QuizID)
{
    m_QuizID = QuizID;
}
int Quiz::getQuizID()
{
    return m_QuizID;
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
