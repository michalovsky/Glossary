#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "ApiKeyFileFormatter.h"
#include "ApiKeyReader.h"
#include "utils/FileAccess.h"

namespace glossary::wordDescriptionService
{
class WordsApiKeyFileReader : public ApiKeyReader
{
public:
    explicit WordsApiKeyFileReader(std::shared_ptr<const utils::FileAccess>);

    boost::optional<std::string> readApiKey() const override;

private:
    boost::optional<std::string> readPathToFileWithApiKey() const;
    boost::optional<std::string> readApiKeyFromFile(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;
    ApiKeyFileFormatter apiKeyFileFormatter;

    static const std::string filePathContainingPathToFileWithApiKey;
};
}