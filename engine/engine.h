//
// Created by alex on 15.09.2023.
//

#ifndef SCHELLING_ENGINE_H
#define SCHELLING_ENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include "cell/cell.h"

class Engine {
public:

    bool init(std::wstring wtitle, int width, int height);
    bool init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool isRunning();
    SDL_Renderer *getRender();

private:

    void renderNet();
    void renderField();
    void calcField();
    void copyField();
    void countStatistic();

    const int hCell = 8;
    const int wCell = 8;
    Cell **prevField;
    Cell **currField;
    int currentFrame;
    bool bRunning;
    int height, width;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    const SDL_Color BORDER_COLOR = {255, 255, 255, 255};
    const SDL_Color BACKGROUND_COLOR = {255, 255, 255, 255};
};

#endif //SCHELLING_ENGINE_H