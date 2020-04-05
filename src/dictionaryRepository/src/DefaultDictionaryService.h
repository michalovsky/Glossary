#pragma once

#include <memory>

#include "DictionaryNamesRetriever.h"
#include "DictionaryService.h"
#include "DictionaryWordsRetriever.h"
#include "RandomDictionaryWordRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryService : public DictionaryService
{
public:
    DefaultDictionaryService(std::shared_ptr<DictionaryRepository>, std::unique_ptr<DictionaryNamesRetriever>,
                             std::unique_ptr<DictionaryWordsRetriever>,
                             std::unique_ptr<RandomDictionaryWordRetriever>);

    DictionaryNames getDictionaryNames() const override;
    DictionaryWords getDictionaryWords(const DictionaryName&) const override;
    boost::optional<DictionaryWord> getRandomDictionaryWord() const override;
    boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const override;
    void addDictionary(const DictionaryName&) override;
    void addDictionaryFromFile(const DictionaryName&, const std::string& filePath) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const std::string& word, const DictionaryName&) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryNamesRetriever> dictionaryNamesRetriever;
    std::unique_ptr<DictionaryWordsRetriever> dictionaryWordsRetriever;
    std::unique_ptr<RandomDictionaryWordRetriever> randomDictionaryWordRetriever;
};
}