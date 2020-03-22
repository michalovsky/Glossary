#include "DefaultTranslationRepository.h"

#include "gtest/gtest.h"

#include "TranslationsStorageMock.h"

using namespace ::testing;
using namespace translationRepository;

namespace
{
const SourceText polishWord1{"polishWord1"};
const SourceText polishWord2{"polishWord2"};
const TranslatedText englishWord1{"englishWord1"};
const TranslatedText englishWord2{"englishWord2"};
const Translation translation1{polishWord1, englishWord1};
const Translation translation2{polishWord2, englishWord2};
const Translations translations{translation1, translation2};
}

class DefaultTranslationRepositoryTest : public Test
{
public:
    std::unique_ptr<TranslationsStorageMock> storageInit =
        std::make_unique<StrictMock<TranslationsStorageMock>>();
    TranslationsStorageMock* storage = storageInit.get();
    DefaultTranslationRepository database{std::move(storageInit)};
};

TEST_F(DefaultTranslationRepositoryTest, addTranslation)
{
    EXPECT_CALL(*storage, addTranslation(translation1));

    database.addTranslation(translation1);
}

TEST_F(DefaultTranslationRepositoryTest, getTranslation)
{
    EXPECT_CALL(*storage, getTranslation(polishWord1)).WillOnce(Return(translation1));

    const auto actualTranslation = database.getTranslation(polishWord1);

    ASSERT_EQ(actualTranslation, translation1);
}