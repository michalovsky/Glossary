#pragma once

#include "WordDescriptionDownloaderFactory.h"

namespace glossary::wordDescriptionDownloader
{
class DefaultWordDescriptionDownloaderFactory : public WordDescriptionDownloaderFactory
{
public:
    explicit DefaultWordDescriptionDownloaderFactory(std::shared_ptr<const webConnection::HttpHandler>,
                                                     std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<WordDescriptionDownloader> createWordDescriptionDownloader() const override;

private:
    std::shared_ptr<const webConnection::HttpHandler> httpHandler;
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}