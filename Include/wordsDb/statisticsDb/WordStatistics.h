#pragma once

#include <ostream>

#include "EnglishWord.h"

namespace wordsDb::statisticsDb
{
struct WordStatistics
{
    void addCorrectAnswer()
    {
        correctAnswers++;
    }

    void addIncorrectAnswer()
    {
        incorrectAnswers++;
    }

    void resetAnswers()
    {
        correctAnswers = 0;
        incorrectAnswers = 0;
    }

    EnglishWord englishWord;
    int correctAnswers{0};
    int incorrectAnswers{0};
};

inline bool operator==(const WordStatistics& lhs, const WordStatistics& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.correctAnswers == rhs.correctAnswers &&
            lhs.incorrectAnswers == rhs.incorrectAnswers);
}

inline std::ostream& operator<<(std::ostream& os,
                                const WordStatistics& wordStatistics)
{
    os << wordStatistics.englishWord << " " << wordStatistics.correctAnswers
       << " " << wordStatistics.incorrectAnswers;
    return os;
}
}