#pragma once
#include <iostream>
#include <cstdlib>
#include <stdio.h> 
#include <vector>
class Constant
{
public:
    enum Position {
        LEFT = 25,
        MIDDLE = 500,
        RIGHT = 1000,
    };    
    enum TextPos {
        TITLE_HEIGHT = 24,
        TANK_NAME_HEIGHT = 75,
        TANK_NAME_WIDTH = 30,
        TANK_ROLE_HEIGHT = 120,
        TANK_MODULE_HEIGHT = 170,
        TANK_MODULE_HEIGHT_2 = 470,
        BASE_STATS_POS = 615,
        COMBAT_STATS_POS = 780,
        MISC_STATS_POS = 935,
    };

    static const int MIN_COMBAT_WIDTH;
    static const int MAX_COMBAT_WIDTH;

    static const std::vector<std::string> DLC;
};

