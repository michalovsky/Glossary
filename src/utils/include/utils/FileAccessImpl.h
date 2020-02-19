#pragma once

#include "FileAccess.h"

namespace utils
{
class FileAccessImpl : public FileAccess
{
public:
    void write(const std::string& path,
               const std::string& content) const override;
    void append(const std::string& path,
                const std::string& content) const override;
    std::string readContent(const std::string& path) const override;
};
}