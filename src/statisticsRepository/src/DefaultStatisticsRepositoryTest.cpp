#include "gtest/gtest.h"

#include "StatisticsStorageMock.h"

#include "DefaultStatisticsRepository.h"

using namespace ::testing;
using namespace statisticsRepository;

namespace
{
const EnglishWord englishWord1{"englishWord1"};
const EnglishWord englishWord2{"englishWord2"};
const EnglishWord nonExistingWord{"nonExistingWord"};
const WordStatistics wordStats1{englishWord1, 7, 0};
const WordStatistics wordStats2{englishWord2, 8, 0};
const Statistics oneWordStatistics{wordStats1};
const Statistics twoWordsStatistics{wordStats1, wordStats2};
}

class DefaultStatisticsRepositoryTest : public Test
{
public:
    std::unique_ptr<StatisticsStorageMock> storageInit =
        std::make_unique<StrictMock<StatisticsStorageMock>>();
    StatisticsStorageMock* storage = storageInit.get();
    DefaultStatisticsRepository database{std::move(storageInit)};
};

TEST_F(DefaultStatisticsRepositoryTest, addWordStatistics)
{
    EXPECT_CALL(*storage, addWordStatistics(wordStats1));

    database.addWordStatistics(wordStats1);
}

TEST_F(DefaultStatisticsRepositoryTest, getWordStatistics)
{
    EXPECT_CALL(*storage, getWordStatistics(englishWord1)).WillOnce(Return(wordStats1));

    const auto actualWordStats = database.getWordStatistics(englishWord1);

    ASSERT_EQ(actualWordStats, wordStats1);
}

TEST_F(DefaultStatisticsRepositoryTest, getStatistics)
{
    EXPECT_CALL(*storage, getStatistics()).WillOnce(Return(twoWordsStatistics));

    const auto statistics = database.getStatistics();

    ASSERT_EQ(statistics, twoWordsStatistics);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordInStorage_shouldAddCorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*storage, addCorrectAnswer(englishWord1));

    database.addCorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordNotInStorage_shouldAddEmptyWordAndThenAddCorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*storage, addWordStatistics(WordStatistics{englishWord1, 0, 0}));
    EXPECT_CALL(*storage, addCorrectAnswer(englishWord1));

    database.addCorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordInStorage_shouldAddIncorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*storage, addIncorrectAnswer(englishWord1));

    database.addIncorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordNotInStorage_shouldAddEmptyWordAndThenAddIncorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*storage, addWordStatistics(WordStatistics{englishWord1, 0, 0}));
    EXPECT_CALL(*storage, addIncorrectAnswer(englishWord1));

    database.addIncorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, resetStatistics)
{
    EXPECT_CALL(*storage, resetStatistics());

    database.resetStatistics();
}