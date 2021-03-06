#pragma once

#include <memory>

#include "StatisticsRepository.h"
#include "utils/FileAccess.h"
#include "StatisticsRepositoryApi.h"

namespace glossary::statisticsRepository
{
class STATISTICS_REPOSITORY_API StatisticsRepositoryFactory
{
public:
    virtual ~StatisticsRepositoryFactory() = default;

    virtual std::unique_ptr<StatisticsRepository> createStatisticsRepository() const = 0;

    static std::unique_ptr<StatisticsRepositoryFactory>
    createStatisticsRepositoryFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}