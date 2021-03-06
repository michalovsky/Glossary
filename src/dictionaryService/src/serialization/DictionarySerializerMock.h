#pragma once

#include "gmock/gmock.h"

#include "DictionarySerializer.h"

namespace glossary::dictionaryService::serialization
{
class DictionarySerializerMock : public DictionarySerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const Dictionaries&));
    MOCK_CONST_METHOD1(deserialize, Dictionaries(const std::string&));
};
}