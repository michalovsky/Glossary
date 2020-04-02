#pragma once

#include "boost/optional.hpp"

#include "Dictionary.h"

namespace glossary::dictionaryRepository
{
class DictionaryWordsReader
{
public:
    virtual ~DictionaryWordsReader() = default;

    virtual boost::optional<DictionaryWords> readDictionaryWords(const std::string& absolutePath) const = 0;
};
}