#include "../include/board.hpp"
#include "../include/configManager.hpp"

#include <string>

int main()
{
    std::string filename{"config.ant"};
    ConfigManager CM{filename};

    Board board{CM.getSettings()};

    return 0;
}