#pragma once

#include <string>

namespace glossary
{
class AnswerValidator
{
public:
    virtual ~AnswerValidator() = default;

    virtual bool validateAnswer(const std::string& answer, const std::string& expectedAnswer) const = 0;
};
}