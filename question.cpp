#include "question.h"

Question::Question() {}

Question::Question(int questionId, int quizId, QString question, QString arrayOfAnswers[NUMBER_OF_ANSWERS], int correctAnswer)
    : m_questionId(questionId), m_quizId(quizId), m_question(question), m_correctAnswer(correctAnswer)
{
    for(int i = 0; i < NUMBER_OF_ANSWERS; i++)
    {
        m_arrayOfAnswers[i] = arrayOfAnswers[i];
    }
}

Question::~Question() {}

Question::Question(const Question& original)
    : m_questionId(original.m_questionId), m_quizId(original.m_quizId), m_question(original.m_question), m_correctAnswer(original.m_correctAnswer)
{
    for(int i = 0; i < NUMBER_OF_ANSWERS; i++)
    {
        m_arrayOfAnswers[i] = original.m_arrayOfAnswers[i];
    }
}

void Question::setQuestionId(int& questionId)
{
    m_questionId = questionId;
}
int Question::getQuestionId()
{
    return m_questionId;
}

void Question::setQuizId(int& quizId)
{
    m_quizId = quizId;
}
int Question::getQuizId()
{
    return m_quizId;
}

void Question::setQuestion(QString& question)
{
    m_question = question;
}
QString Question::getQuestion()
{
    return m_question;
}

void Question::setAnswer(int i, QString& answer)
{
    m_arrayOfAnswers[i] = answer;
}
QString Question::getAnswer(int i)
{
    return m_arrayOfAnswers[i];
}

bool Question::setCorrectAnswer(int& correctAnswer)
{
    if(correctAnswer > 0 && correctAnswer < NUMBER_OF_ANSWERS + 1)
    {
        m_correctAnswer = correctAnswer;
        return true;
    }
    else
    {
        return false;
    }
}
int Question::getCorrectAnswer()
{
    return m_correctAnswer;
}
