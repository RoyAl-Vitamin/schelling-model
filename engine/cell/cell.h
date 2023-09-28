//
// Created by alex on 15.09.2023.
//

#ifndef SCHELLING_CELL_H
#define SCHELLING_CELL_H

#include <SDL2/SDL.h>
#include "home_status.cpp"
#include "mood_status.cpp"
#include <iostream>

class Cell {

public:
    Cell();
    Cell(HomeStatus homeStatus, MoodStatus moodStatus, SDL_Color color);
    void setHomeStatus(HomeStatus homeStatus);
    HomeStatus getHomeStatus();
    void setMoodStatus(MoodStatus moodStatus);
    MoodStatus getMoodStatus();
    void setColor(SDL_Color color);
    SDL_Color getColor();

private:
    HomeStatus homeStatus;
    MoodStatus moodStatus;
    SDL_Color color;
    const SDL_Color HOME_COLOR_1 = {89, 87, 217, 255};
    const SDL_Color HOME_COLOR_2 = {84, 82, 204, 255};
    const SDL_Color EMPTY_COLOR = {255, 255, 255, 255};
};

#endif //SCHELLING_CELL_H