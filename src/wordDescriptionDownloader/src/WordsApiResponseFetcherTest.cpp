#include "WordsApiResponseFetcher.h"

#include "gtest/gtest.h"

#include "webConnection/HttpHandlerMock.h"

#include "exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"
#include <boost/optional/optional_io.hpp>

using namespace glossary::wordDescriptionDownloader;
using namespace ::testing;

namespace
{
const std::string englishWord{"herbal"};
const std::string apiKey{"topSecretKey"};
const std::vector<std::string> headers{"x-rapidapi-host: wordsapiv1.p.rapidapi.com",
                                       "x-rapidapi-key: " + apiKey};
const std::string wordsApiDefinitionsUrl{"https://wordsapiv1.p.rapidapi.com/words/herbal/definitions"};
const std::string wordsApiExamplesUrl{"https://wordsapiv1.p.rapidapi.com/words/herbal/examples"};
const std::string wordsApiSynonymsUrl{"https://wordsapiv1.p.rapidapi.com/words/herbal/synonyms"};
const webConnection::Response response{200, "content"};
const webConnection::Response unauthorizedResponse{401, ""};
}

class WordsApiResponseFetcherTest : public Test
{
public:
    std::shared_ptr<webConnection::HttpHandlerMock> httpHandler =
        std::make_shared<StrictMock<webConnection::HttpHandlerMock>>();
    WordsApiResponseFetcher wordsApiResponseFetcher{httpHandler};
};

TEST_F(WordsApiResponseFetcherTest,
       getDefinitions_httpHandlerThrowConnectionFailed_shouldThrowConnectionFailed)
{
    EXPECT_CALL(*httpHandler, get(wordsApiDefinitionsUrl, headers))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordDefinitionsResponse(englishWord, apiKey),
                 webConnection::exceptions::ConnectionFailed);
}

TEST_F(WordsApiResponseFetcherTest,
       getDefinitions_httpResponseReturnsUnautorizedCode_shouldThrowInvalidApiKey)
{
    EXPECT_CALL(*httpHandler, get(wordsApiDefinitionsUrl, headers)).WillOnce(Return(unauthorizedResponse));

    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordDefinitionsResponse(englishWord, apiKey),
                 exceptions::InvalidApiKey);
}

TEST_F(WordsApiResponseFetcherTest, getDefinitions_shouldInvokeHttpResponseWithDefinitionsUrl)
{
    EXPECT_CALL(*httpHandler, get(wordsApiDefinitionsUrl, headers)).WillOnce(Return(response));

    const auto actualResponse = wordsApiResponseFetcher.tryGetWordDefinitionsResponse(englishWord, apiKey);

    ASSERT_EQ(actualResponse, response);
}

TEST_F(WordsApiResponseFetcherTest, getExamples_httpHandlerThrowConnectionFailed_shouldThrowConnectionFailed)
{
    EXPECT_CALL(*httpHandler, get(wordsApiExamplesUrl, headers))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordExamplesResponse(englishWord, apiKey),
                 webConnection::exceptions::ConnectionFailed);
}

TEST_F(WordsApiResponseFetcherTest, getExamples_httpResponseReturnsUnautorizedCode_shouldThrowInvalidApiKey)
{
    EXPECT_CALL(*httpHandler, get(wordsApiExamplesUrl, headers)).WillOnce(Return(unauthorizedResponse));

    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordExamplesResponse(englishWord, apiKey),
                 exceptions::InvalidApiKey);
}

TEST_F(WordsApiResponseFetcherTest, getExamples_shouldInvokeHttpResponseWithExamplesUrl)
{
    EXPECT_CALL(*httpHandler, get(wordsApiExamplesUrl, headers)).WillOnce(Return(response));

    const auto actualResponse = wordsApiResponseFetcher.tryGetWordExamplesResponse(englishWord, apiKey);

    ASSERT_EQ(actualResponse, response);
}

TEST_F(WordsApiResponseFetcherTest, getSynonyms_httpHandlerThrowConnectionFailed_shouldThrowConnectionFailed)
{
    EXPECT_CALL(*httpHandler, get(wordsApiSynonymsUrl, headers))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordSynonymsResponse(englishWord, apiKey),
                 webConnection::exceptions::ConnectionFailed);
}

TEST_F(WordsApiResponseFetcherTest, getSynonyms_httpResponseReturnsUnautorizedCode_shouldThrowInvalidApiKey)
{
    EXPECT_CALL(*httpHandler, get(wordsApiSynonymsUrl, headers)).WillOnce(Return(unauthorizedResponse));

    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordSynonymsResponse(englishWord, apiKey),
                 exceptions::InvalidApiKey);
}

TEST_F(WordsApiResponseFetcherTest, getSynonyms_shouldInvokeHttpResponseWithSynonymsUrl)
{
    EXPECT_CALL(*httpHandler, get(wordsApiSynonymsUrl, headers)).WillOnce(Return(response));

    const auto actualResponse = wordsApiResponseFetcher.tryGetWordSynonymsResponse(englishWord, apiKey);

    ASSERT_EQ(actualResponse, response);
}
