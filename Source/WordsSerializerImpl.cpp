#include <iostream>
#include "WordsSerializerImpl.h"
#include "boost/algorithm/cxx11/any_of.hpp"

namespace
{
constexpr auto wordsField = "words";
constexpr auto englishWordField = "englishWord";
constexpr auto polishWordField = "polishWord";
constexpr auto wordDescriptionField = "wordDescription";
}

std::string WordsSerializerImpl::serialize(const Words& words) const
{
    nlohmann::json serialized;
    for (const auto& word : words)
    {
        serialized[wordsField].push_back(getJsonFromWord(word));
    }
    return serialized.dump();
}

Words WordsSerializerImpl::deserialize(const std::string& jsonText) const
{
    if (jsonText.empty())
    {
        return {};
    }

    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readWords(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse Words:" << e.what();
    }
    return {};
}

nlohmann::json WordsSerializerImpl::getJsonFromWord(const Word& word) const
{
    nlohmann::json val = nlohmann::json::object();
    val[englishWordField] = word.englishWord;
    val[polishWordField] = word.polishWord;
    val[wordDescriptionField] = wordDescriptionSerializer.serialize(word.wordDescription);
    return val;
}

Words WordsSerializerImpl::readWords(const nlohmann::json& json) const
{
    if (json.find(wordsField) != json.end())
    {
        return parseWords(json[wordsField]);
    }
    std::cerr << "There are no words stored\n";
    return {};
}

Words WordsSerializerImpl::parseWords(const nlohmann::json& wordsJson) const
{
    Words words;
    for (const auto& wordData : wordsJson)
    {
        if (!isWordValid(wordData))
        {
            try
            {
                const EnglishWord englishWord{wordData[englishWordField]};
                const PolishWord polishWord{wordData[polishWordField]};
                const WordDescription wordDescription{wordDescriptionSerializer.deserialize(wordData[wordDescriptionField])};
                words.push_back({englishWord, polishWord, wordDescription});
            }
            catch (const std::exception& e)
            {
                std::cerr << "Unable to read word:" << e.what() << "\n";
            }
        }
        else
        {
            std::cerr << "Word does not contain all required data\n";
        }
    }
    return words;
}

bool WordsSerializerImpl::isWordValid(const nlohmann::json& wordData) const
{
    const auto requiredFields = {englishWordField, polishWordField, wordDescriptionField};
    auto wordInvalid = boost::algorithm::any_of(
            requiredFields, [&](const auto& fieldName)
            { return wordData.find(fieldName) == wordData.end(); });
    return wordInvalid;
}


