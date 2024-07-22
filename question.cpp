#include "question.h"

Question::Question() {}

Question::Question(int QuestionID, int QuizID, QString Question, QString ArrayOfAnswers[4], int CorrectAnswer)
    : m_QuestionID(QuestionID), m_QuizID(QuizID), m_Question(Question), m_CorrectAnswer(CorrectAnswer)
{
    for(int i = 0; i < 4; i++)
    {
        m_ArrayOfAnswers[i] = ArrayOfAnswers[i];
    }
}

Question::~Question() {}

Question::Question(const Question& original)
    : m_QuestionID(original.m_QuestionID), m_QuizID(original.m_QuizID), m_Question(original.m_Question), m_CorrectAnswer(original.m_CorrectAnswer)
{
    for(int i = 0; i < 4; i++)
    {
        m_ArrayOfAnswers[i] = original.m_ArrayOfAnswers[i];
    }
}

void Question::setQuestionID(int QuestionID)
{
    m_QuestionID = QuestionID;
}
int Question::getQuestionID()
{
    return m_QuestionID;
}

void Question::setQuizID(int QuizID)
{
    m_QuizID = QuizID;
}
int Question::getQuizID()
{
    return m_QuizID;
}

void Question::setQuestion(QString Question)
{
    m_Question = Question;
}
QString Question::getQuestion()
{
    return m_Question;
}

void Question::setAnswer(int i, QString Answer)
{
    m_ArrayOfAnswers[i] = Answer;
}
QString Question::getAnswer(int i)
{
    return m_ArrayOfAnswers[i];
}

bool Question::setCorrectAnswer(int CorrectAnswer)
{
    if(CorrectAnswer > 0 && CorrectAnswer < 5)
    {
        m_CorrectAnswer = CorrectAnswer;
        return 1;
    }
    else
    {
        return 0;
    }
}
int Question::getCorrectAnswer()
{
    return m_CorrectAnswer;
}
