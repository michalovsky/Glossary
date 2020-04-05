#pragma once

#include <memory>

#include "../csvFileReading/DictionaryWordsReader.h"
#include "DictionaryRepository.h"
#include "DictionaryStorage.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryRepository : public DictionaryRepository
{
public:
    DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage>, std::unique_ptr<DictionaryWordsReader>);

    void addDictionary(const DictionaryName&) override;
    void addDictionaryFromFile(const DictionaryName&, const std::string& dictionaryWordsPath) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const std::string& englishWord, const DictionaryName&) override;
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const DictionaryName&) const override;

private:
    std::unique_ptr<DictionaryStorage> storage;
    std::unique_ptr<DictionaryWordsReader> dictionaryWordsReader;
};
}