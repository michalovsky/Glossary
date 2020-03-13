#include "DictionaryReaderImpl.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/exceptions/FileNotFound.h"
#include "boost/assign/list_of.hpp"

using namespace ::testing;
using namespace utils;

namespace
{
const std::string baseDictionaryName{"base"};
const std::string dictionaryFilePath{"database/input.txt"};
const std::string content{"car samochod\n"
                          "air powietrze\n"};
const std::string contentWithTwoWordsAndOneIncorrect{"car samochod\n"
                                                     "     powietrze\n"};
const Dictionary baseDictionaryWithOneWord{{"samochod", "car"}};
const std::string emptyContent{};
const Dictionary baseDictionary{{"samochod", "car"}, {"powietrze", "air"}};
const Dictionaries baseDictionaries1 =
    boost::assign::map_list_of(baseDictionaryName, baseDictionaryWithOneWord);
const Dictionaries baseDictionaries2 =
    boost::assign::map_list_of(baseDictionaryName, baseDictionary);
}

class DictionaryReaderImplTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<StrictMock<FileAccessMock>>();
    DictionaryReaderImpl reader{fileAccess};
};

TEST_F(DictionaryReaderImplTest, givenEmptyDictionaryContent_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(emptyContent));

    const auto actualDictionaries = reader.readDictionaries();

    EXPECT_TRUE(actualDictionaries.count(baseDictionaryName));
    EXPECT_TRUE(actualDictionaries.at(baseDictionaryName).empty());
}

TEST_F(DictionaryReaderImplTest,
       givenyDictionaryContentWithTwoWordsAndOneOfThemIsIncorrect_shouldReturnDictWithOneWord)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath))
        .WillOnce(Return(contentWithTwoWordsAndOneIncorrect));

    const auto actualDictionaries = reader.readDictionaries();

    EXPECT_EQ(actualDictionaries, baseDictionaries1);
}

TEST_F(DictionaryReaderImplTest, givenDictionaryContent_shouldReadDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(content));

    const auto actualDictionary = reader.readDictionaries();

    EXPECT_EQ(actualDictionary, baseDictionaries2);
}

TEST_F(DictionaryReaderImplTest, givenInvalidFile_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath))
        .WillOnce(Throw(utils::exceptions::FileNotFound{""}));

    const auto dictionary = reader.readDictionaries();

    EXPECT_TRUE(dictionary.empty());
}
