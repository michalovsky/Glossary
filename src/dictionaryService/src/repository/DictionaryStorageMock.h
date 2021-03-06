#pragma once

#include "gmock/gmock.h"

#include "DictionaryStorage.h"

namespace glossary::dictionaryService::repository
{
class DictionaryStorageMock : public DictionaryStorage
{
public:
    MOCK_METHOD1(addDictionary, void(const DictionaryName&));
    MOCK_METHOD1(addDictionary, void(const Dictionary&));
    MOCK_METHOD2(addWordToDictionary, void(const DictionaryWord&, const DictionaryName&));
    MOCK_METHOD1(removeDictionary, void(const DictionaryName&));
    MOCK_METHOD2(removeWordFromDictionary, void(const std::string&, const DictionaryName&));
    MOCK_METHOD3(changeWordTranslationFromDictionary,
                 void(const EnglishWord&, const std::string&, const DictionaryName&));
    MOCK_CONST_METHOD1(getDictionary, boost::optional<Dictionary>(const DictionaryName&));
    MOCK_CONST_METHOD0(getDictionaries, Dictionaries());
    MOCK_CONST_METHOD1(containsDictionary, bool(const DictionaryName&));
    MOCK_CONST_METHOD0(size, Dictionaries::size_type());
    MOCK_CONST_METHOD0(empty, bool());
};
}