#pragma once

#include "boost/optional.hpp"

#include "EnglishWord.h"
#include "Statistics.h"
#include "StatisticsRepositoryApi.h"

namespace glossary::statisticsRepository
{
class STATISTICS_REPOSITORY_API StatisticsRepository
{
public:
    virtual ~StatisticsRepository() = default;

    virtual boost::optional<WordStatistics> getWordStatistics(const EnglishWord&) const = 0;
    virtual Statistics getStatistics() const = 0;
    virtual void addWordStatistics(WordStatistics) = 0;
    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual void resetStatistics() = 0;
};
}
