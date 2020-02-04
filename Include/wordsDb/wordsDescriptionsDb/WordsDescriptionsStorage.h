#pragma once

#include "WordsDescriptions.h"
#include "boost/optional.hpp"

namespace wordsDb::wordsDescriptionsDb
{

class WordsDescriptionsStorage
{
public:
    virtual ~WordsDescriptionsStorage() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const = 0;
    virtual WordsDescriptions getWordsDescriptions() const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
    virtual WordsDescriptions::size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual WordsDescriptions::const_iterator begin() const = 0;
    virtual WordsDescriptions::const_iterator end() const = 0;
};
}