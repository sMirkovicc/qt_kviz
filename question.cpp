#include "question.h"

Question::Question() {}

Question::Question(int QuestionId, int QuizId, QString Question, QString ArrayOfAnswers[numberOfAnswers], int CorrectAnswer)
    : m_QuestionId(QuestionId), m_QuizId(QuizId), m_Question(Question), m_CorrectAnswer(CorrectAnswer)
{
    for(int i = 0; i < numberOfAnswers; i++)
    {
        m_ArrayOfAnswers[i] = ArrayOfAnswers[i];
    }
}

Question::~Question() {}

Question::Question(const Question& original)
    : m_QuestionId(original.m_QuestionId), m_QuizId(original.m_QuizId), m_Question(original.m_Question), m_CorrectAnswer(original.m_CorrectAnswer)
{
    for(int i = 0; i < numberOfAnswers; i++)
    {
        m_ArrayOfAnswers[i] = original.m_ArrayOfAnswers[i];
    }
}

void Question::setQuestionId(int QuestionId)
{
    m_QuestionId = QuestionId;
}
int Question::getQuestionId()
{
    return m_QuestionId;
}

void Question::setQuizId(int QuizId)
{
    m_QuizId = QuizId;
}
int Question::getQuizId()
{
    return m_QuizId;
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
    if(CorrectAnswer > 0 && CorrectAnswer < numberOfAnswers + 1)
    {
        m_CorrectAnswer = CorrectAnswer;
        return true;
    }
    else
    {
        return false;
    }
}
int Question::getCorrectAnswer()
{
    return m_CorrectAnswer;
}
