#include "WordsShufflerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const WordDescription word1("computer", "komputer",
                 {{{"definition", std::string{"example"}},
                   {"definition2", std::string{"example2"}}},
                  {"sentence"}});
const WordDescription word2("tea", "herbata", {});
const WordDescription word3("headphones", "sluchawki", {});
const Words words{word1, word2, word3};
const Words wordsWithOneWord{word1};
const Words emptyWords{};
}

class WordsShufflerImplTest : public Test
{
public:
    WordsShufflerImpl shuffler;
};

TEST_F(WordsShufflerImplTest, givenNoWords_shouldReturnNoWords)
{
    const auto actualShuffledWords = shuffler.shuffle(emptyWords);

    ASSERT_TRUE(actualShuffledWords.empty());
}

TEST_F(WordsShufflerImplTest, givenWords_shouldReturnRandomizedWords)
{
    const auto actualShuffledWords = shuffler.shuffle(words);

    ASSERT_NE(actualShuffledWords, words);
}

TEST_F(WordsShufflerImplTest, givenOneWord_shouldReturnSameWord)
{
    const auto actualShuffledWords = shuffler.shuffle(wordsWithOneWord);

    ASSERT_EQ(actualShuffledWords, wordsWithOneWord);
}
