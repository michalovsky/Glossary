#pragma once

#include "DescriptionSerializer.h"
#include "WordsDescriptionsSerializer.h"
#include "nlohmann/json.hpp"

namespace wordsDb::wordsDescriptionsDb
{
class WordsDescriptionsSerializerImpl : public WordsDescriptionsSerializer
{
public:
    std::string serialize(const WordsDescriptions&) const override;
    WordsDescriptions deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWordDescription(const WordDescription&) const;
    WordsDescriptions readWordsDescriptions(const nlohmann::json&) const;
    WordsDescriptions parseWordsDescriptions(const nlohmann::json&) const;
    bool isWordDescriptionValid(const nlohmann::json&) const;

    DescriptionSerializer wordDescriptionSerializer;
};
}