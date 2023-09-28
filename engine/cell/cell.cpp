//
// Created by alex on 15.09.2023.
//

#include "cell.h"

Cell::Cell() {
}

Cell::Cell(HomeStatus homeStatus, MoodStatus moodStatus, SDL_Color color) {
    this->homeStatus = homeStatus;
    this->moodStatus = moodStatus;
    this->color = color;
}

void Cell::setHomeStatus(HomeStatus homeStatus) {
    this->homeStatus = homeStatus;
}

HomeStatus Cell::getHomeStatus() {
    return this->homeStatus;
}

void Cell::setMoodStatus(MoodStatus moodStatus) {
    this->moodStatus = moodStatus;
}
MoodStatus Cell::getMoodStatus() {
    return this->moodStatus;
}

void Cell::setColor(SDL_Color color) {
    this->color = color;
}

SDL_Color Cell::getColor() {
    return this->color;
}