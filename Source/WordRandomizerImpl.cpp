#include "WordRandomizerImpl.h"

#include <random>
#include <stdexcept>

WordDescription WordRandomizerImpl::randomizeWord(const Words& words) const
{
    if (words.empty())
    {
        throw std::runtime_error{"Cant randomize word"};
    }

    return words.at(getRandomIndex(words.size()));
}

Words::size_type WordRandomizerImpl::getRandomIndex(Words::size_type size) const
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, int(size) - 1);
    return Words::size_type(dist(mt));
}
