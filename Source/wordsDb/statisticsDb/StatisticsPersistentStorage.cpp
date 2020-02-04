#include "wordsDb/statisticsDb/StatisticsPersistentStorage.h"

#include <iostream>

#include "exceptions/FileNotFound.h"

namespace wordsDb::statisticsDb
{

// TODO: change filenames to be more relevant
const std::string StatisticsPersistentStorage::directory{"../database"};
const std::string StatisticsPersistentStorage::filename{
    directory + "/statistics.txt"};

StatisticsPersistentStorage::StatisticsPersistentStorage(
    std::shared_ptr<const FileAccess> fileAccessInit,
    std::shared_ptr<const StatisticsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{
                                                 std::move(serializerInit)}
{
    loadFile();
}

boost::optional<WordStatistics> StatisticsPersistentStorage::getWordStatistics(
    const EnglishWord& englishWord) const
{
    return storage.getWordStatistics(englishWord);
}

Statistics StatisticsPersistentStorage::getStatistics() const
{
    return storage.getStatistics();
}

void StatisticsPersistentStorage::addWordStatistics(
    WordStatistics wordStatistics)
{
    if (not storage.contains(wordStatistics.englishWord))
    {
        storage.addWordStatistics(std::move(wordStatistics));
        serialize();
    }
}

void StatisticsPersistentStorage::addCorrectAnswer(
    const EnglishWord& englishWord)
{
    storage.addCorrectAnswer(englishWord);
    serialize();
}

void StatisticsPersistentStorage::addIncorrectAnswer(
    const EnglishWord& englishWord)
{
    storage.addIncorrectAnswer(englishWord);
    serialize();
}

void StatisticsPersistentStorage::resetStatistics()
{
    storage.resetStatistics();
    serialize();
}

bool StatisticsPersistentStorage::contains(const EnglishWord& englishWord) const
{
    return storage.contains(englishWord);
}

Statistics::size_type StatisticsPersistentStorage::size() const
{
    return storage.size();
}

bool StatisticsPersistentStorage::empty() const
{
    return storage.empty();
}

Statistics::const_iterator StatisticsPersistentStorage::begin() const
{
    return storage.begin();
}

Statistics::const_iterator StatisticsPersistentStorage::end() const
{
    return storage.end();
}

void StatisticsPersistentStorage::loadFile()
{
    Statistics statistics;
    try
    {
        statistics = serializer->deserialize(fileAccess->readContent(filename));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
        return;
    }

    for (const auto& wordStats : statistics)
    {
        storage.addWordStatistics(wordStats);
    }
}

void StatisticsPersistentStorage::serialize() const
{
    try
    {
        fileAccess->write(filename,
                          serializer->serialize(storage.getStatistics()));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
    }
}

}