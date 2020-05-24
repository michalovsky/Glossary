#pragma once

#include "gmock/gmock.h"

#include "TranslatorConnectionChecker.h"

namespace glossary::translationService
{
class TranslatorConnectionCheckerMock : public TranslatorConnectionChecker
{
public:
    MOCK_METHOD1(connectionToTranslatorWithApiKeyIsAvailable,
                 TranslationApiStatus(const std::string& apiKey));
};
}