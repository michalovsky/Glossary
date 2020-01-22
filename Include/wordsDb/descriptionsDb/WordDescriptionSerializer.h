#pragma once

#include "Description.h"
#include "nlohmann/json.hpp"

class WordDescriptionSerializer
{
public:
    nlohmann::json serialize(const Description&) const;
    Description deserialize(const nlohmann::json&) const;
};
