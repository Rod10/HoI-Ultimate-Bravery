#pragma once
#include <iostream>
#include <cstdlib>
#include <stdio.h> 
#include <vector>
class Constant
{
public:
    enum Position {
        LEFT = 000,
        MIDDLE = 500,
        RIGHT = 1000,
    };    
    enum TextPos {
        TITLE_HEIGHT = 24,
        TANK_NAME_HEIGHT = 63,
        TANK_ROLE_HEIGHT = 106,
        TANK_MODULE_HEIGHT = 155,
        TANK_MODULE_HEIGHT_2 = 455,
        BASE_STATS_POS = 720,
        COMBAT_STATS_POS = 895,
        MISC_STATS_POS = 910,
    };

    static const std::vector<std::string> DLC;
};

