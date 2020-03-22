#pragma once

#include <memory>

#include "WordDescriptionService.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

class DefaultWordDescriptionService : public WordDescriptionService
{
public:
    DefaultWordDescriptionService(std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
                                  std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>);

    boost::optional<wordDescriptionRepository::WordDescription>
    getWordDescription(const wordDescriptionRepository::EnglishWord&) override;

private:
    boost::optional<wordDescriptionRepository::WordDescription>
    getWordDescriptionFromRepository(const wordDescriptionRepository::EnglishWord& englishWord) const;
    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord& englishWord) const;
    void saveWordDescriptionInRepository(const wordDescriptionRepository::WordDescription&);

    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
};