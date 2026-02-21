#include "board.hpp"
#include "configManager.hpp"

#include <string>

int main()
{
    std::string filename{"../../config.json"};
    ConfigManager CM{filename};

    Board board{CM.getSettings()};

    return 0;
}