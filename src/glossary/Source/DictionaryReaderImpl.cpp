#include "DictionaryReaderImpl.h"

#include <utility>

#include "plog/Log.h"

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

const std::string DictionaryReaderImpl::fileDirectory{"database/"};
const std::string DictionaryReaderImpl::fileName{"translations.txt"};
const std::string DictionaryReaderImpl::filePath{fileDirectory + fileName};

DictionaryReaderImpl::DictionaryReaderImpl(std::shared_ptr<const utils::FileAccess> access)
    : fileAccess{std::move(access)}
{
}

std::vector<translationsDb::Translation> DictionaryReaderImpl::read() const
{
    LOG_DEBUG << "Reading translations from file";

    std::string dictionaryContent;
    try
    {
        dictionaryContent = fileAccess->readContent(filePath);
    }
    catch (const utils::exceptions::FileNotFound& e)
    {
        LOG_WARNING << "Error while reading translations from file: " << e.what();
        return {};
    }

    return processDictionaryContent(dictionaryContent);
}

std::vector<translationsDb::Translation>
DictionaryReaderImpl::processDictionaryContent(const std::string& dictionaryContent) const
{
    std::vector<translationsDb::Translation> wordsWithTranslation;
    for (const auto& line : utils::getSplitLines(dictionaryContent))
    {
        if (not line.empty())
        {
            if (const auto wordWithTranslation = getWordWithTranslation(line))
            {
                wordsWithTranslation.push_back(*wordWithTranslation);
            }
        }
    }
    return wordsWithTranslation;
}

boost::optional<translationsDb::Translation>
DictionaryReaderImpl::getWordWithTranslation(const std::string& line) const
{
    std::stringstream lineStream{line};
    translationsDb::TranslatedText englishWord;
    translationsDb::SourceText polishWord;
    lineStream >> englishWord >> polishWord;
    if (!englishWord.empty() && !polishWord.empty())
    {
        return translationsDb::Translation{polishWord, englishWord};
        // TODO: add strong typedefs
    }
    return boost::none;
}
