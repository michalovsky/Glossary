#include "DefaultWordDescriptionDownloader.h"

#include <iostream>

#include "HtmlDescriptionLinesSelector.h"
#include "webConnection/exceptions/ConnectionFailed.h"

namespace glossary::wordDescriptionDownloader
{
const std::string DefaultWordDescriptionDownloader::urlAddressToDownloadWordDescription{
    "https://www.merriam-webster.com/dictionary/"};

DefaultWordDescriptionDownloader::DefaultWordDescriptionDownloader(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit,
    std::unique_ptr<const LinesSelector> linesSelectorInit,
    std::unique_ptr<const DescriptionParser> descriptionParserInit)
    : httpHandler{std::move(httpHandlerInit)},
      linesSelector{std::move(linesSelectorInit)},
      descriptionParser{std::move(descriptionParserInit)}
{
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionDownloader::downloadWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    const auto httpContent = getHttpContent(englishWord);
    if (not httpContent)
        return boost::none;

    const auto linesWithDescription = linesSelector->selectLines(*httpContent);

    if (const auto wordDescription = descriptionParser->parse(linesWithDescription))
        return wordDescriptionRepository::WordDescription{englishWord, *wordDescription};

    return boost::none;
}

boost::optional<std::string> DefaultWordDescriptionDownloader::getHttpContent(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    try
    {
        const auto response = httpHandler->get(urlAddressToDownloadWordDescription + englishWord);
        return response.content;
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Get content from http failed: " << e.what();
        return boost::none;
    }
}
}