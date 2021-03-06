#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordAccumulator.h"
#include "DictionaryWordRandomizer.h"
#include "RandomDictionaryWordRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultRandomDictionaryWordRetriever : public RandomDictionaryWordRetriever
{
public:
    DefaultRandomDictionaryWordRetriever(std::shared_ptr<repository::DictionaryRepository>,
                                         std::unique_ptr<DictionaryWordRandomizer>);

    boost::optional<DictionaryWord> getRandomDictionaryWord() const override;
    boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const override;

private:
    boost::optional<DictionaryWord> randomizeDictionaryWord(const DictionaryWords&) const;

    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryWordRandomizer> dictionaryWordRandomizer;
    DictionaryWordAccumulator dictionaryWordAccumulator;
    DictionaryFinder dictionaryFinder;
};
}
