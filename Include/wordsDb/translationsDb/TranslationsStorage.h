#pragma once

#include "boost/optional.hpp"
#include "wordsDb/translationsDb/Translations.h"

namespace wordsDb::translationsDb
{
class TranslationsStorage
{
public:
    virtual ~TranslationsStorage() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation>
    getTranslation(const PolishWord&) const = 0;
    virtual Translations getTranslations() const = 0;
    virtual bool contains(const PolishWord&) const = 0;
    virtual Translations::size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual Translations::const_iterator begin() const = 0;
    virtual Translations::const_iterator end() const = 0;
};
}