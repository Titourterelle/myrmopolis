#ifndef SETTINGS
#define SETTINGS

#include <unordered_map>
#include <string>

enum class Settings
        {
            Row,
            Column,
            nbAnts,
        };

const std::unordered_map<std::string, Settings> stringToSettings
{
    {"row", Settings::Row},
    {"column", Settings::Column},
    {"ants", Settings::nbAnts}
};

#endif