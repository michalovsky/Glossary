#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsMemoryStorage.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::wordsDescriptionsDb;

namespace
{
const WordDescription word1("xxx", {}, {});
const WordDescription word2("yyy", {}, {});
const WordsDescriptions words{word1, word2};
}

class WordsDescriptionsMemoryStorageTest : public Test
{
public:
    WordsDescriptionsMemoryStorage storage;
};

TEST_F(WordsDescriptionsMemoryStorageTest, givenWordAddition_shouldAddWord)
{
    storage.addWordDescription(word1);

    ASSERT_FALSE(storage.empty());
    ASSERT_EQ(storage.size(), WordsDescriptions::size_type{1});
}

TEST_F(WordsDescriptionsMemoryStorageTest,
       addTwoDifferentWords_shouldAddTwoWords)
{
    storage.addWordDescription(word1);
    storage.addWordDescription(word2);

    const auto actualWords = storage.getWordsDescriptions();

    ASSERT_EQ(actualWords, words);
}

TEST_F(WordsDescriptionsMemoryStorageTest, addTwoSameWords_shouldAddOnlyOne)
{
    storage.addWordDescription(word1);
    storage.addWordDescription(word1);

    ASSERT_EQ(storage.size(), WordsDescriptions::size_type{1});
}

TEST_F(WordsDescriptionsMemoryStorageTest,
       givenEmptyStorage_getShouldNotReturnWord)
{
    const auto result = storage.getWordDescription("someword");

    ASSERT_EQ(result, boost::none);
}

TEST_F(WordsDescriptionsMemoryStorageTest,
       givenStorageWithExactWord_shouldReturnWord)
{
    storage.addWordDescription(word1);

    const auto actualWord = storage.getWordDescription("xxx");

    ASSERT_EQ(actualWord, word1);
}

TEST_F(WordsDescriptionsMemoryStorageTest,
       givenStorageWithTwoWords_shouldReturnTwoElementsBasingOnBeginEnd)
{
    storage.addWordDescription(word1);
    storage.addWordDescription(word2);

    const auto amountOfWords = std::distance(storage.begin(), storage.end());

    ASSERT_EQ(amountOfWords, 2);
}

TEST_F(WordsDescriptionsMemoryStorageTest, givenEmptyStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}

TEST_F(WordsDescriptionsMemoryStorageTest,
       givenWordNotExistingInStorage_getShouldNotContainThisWord)
{
    ASSERT_FALSE(storage.contains("someword"));
}

TEST_F(WordsDescriptionsMemoryStorageTest,
       givenWordExistingInStorage_getShouldContainThisWord)
{
    storage.addWordDescription(word1);

    const auto contains = storage.contains(word1.englishWord);

    ASSERT_TRUE(contains);
}