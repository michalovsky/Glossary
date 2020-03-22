#include "DefaultTranslationService.h"

DefaultTranslationService::DefaultTranslationService(
    std::unique_ptr<translator::Translator> translatorInit,
    std::shared_ptr<translationRepository::TranslationRepository> repo)
    : translator{std::move(translatorInit)}, translationRepository{std::move(repo)}
{
}

boost::optional<translator::TranslatedText>
DefaultTranslationService::translate(const std::string& sourceText, translator::SourceLanguage sourceLanguage,
                                     translator::TargetLanguage targetLanguage)
{
    if (const auto translationFromDb = getTranslationFromRepository(sourceText))
    {
        return translationFromDb;
    }

    if (const auto translationFromTranslator =
            getTranslationFromTranslator(sourceText, sourceLanguage, targetLanguage))
    {
        saveTranslationInRepository(sourceText, *translationFromTranslator);
        return translationFromTranslator;
    }

    return boost::none;
}

boost::optional<translator::TranslatedText>
DefaultTranslationService::getTranslationFromRepository(const std::string& sourceText) const
{
    if (const auto translation = translationRepository->getTranslation(sourceText))
    {
        return translator::TranslatedText{translation->translatedText};
    }
    return boost::none;
}

boost::optional<translator::TranslatedText>
DefaultTranslationService::getTranslationFromTranslator(const std::string& sourceText,
                                                        translator::SourceLanguage sourceLanguage,
                                                        translator::TargetLanguage targetLanguage) const
{
    return translator->translate(sourceText, sourceLanguage, targetLanguage);
}

void DefaultTranslationService::saveTranslationInRepository(const std::string& sourceText,
                                                            const translator::TranslatedText& translatedText)
{
    const auto newTranslation = translationRepository::Translation{
        translationRepository::SourceText{sourceText}, translationRepository::TranslatedText{translatedText}};
    translationRepository->addTranslation(newTranslation);
}
