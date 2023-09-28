//
// Created by alex on 15.09.2023.
//

#include "engine.h"

bool Engine::init(std::wstring wtitle, int width, int height) {
    srand(static_cast <unsigned> (time(0)));

    char * title = new char[wtitle.size()];
    std::wcstombs(title, wtitle.c_str(), 11);

    Engine::prevField = new Cell * [width / Engine::wCell];
    Engine::currField = new Cell * [width / Engine::wCell];
    for (size_t i = 0; i < width / Engine::wCell; i++) {
        Engine::prevField[i] = new Cell[height / Engine::hCell];
        Engine::currField[i] = new Cell[height / Engine::hCell];
        for (size_t j = 0; j < height / Engine::hCell; j++) {
            if (((double) rand() / (RAND_MAX)) > 0.7) {
                Engine::currField[i][j].setHomeStatus(HomeStatus::COMMUNITY_1);
                Engine::currField[i][j].setMoodStatus(MoodStatus::HAPPY);
                Engine::prevField[i][j].setHomeStatus(HomeStatus::COMMUNITY_1);
                Engine::prevField[i][j].setMoodStatus(MoodStatus::HAPPY);
            } else {
                Engine::currField[i][j].setHomeStatus(HomeStatus::COMMUNITY_2);
                Engine::currField[i][j].setMoodStatus(MoodStatus::HAPPY);
                Engine::prevField[i][j].setHomeStatus(HomeStatus::COMMUNITY_2);
                Engine::prevField[i][j].setMoodStatus(MoodStatus::HAPPY);
            }
        }
    }

    return Engine::init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}

bool Engine::init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags) {
    // initialize SDL
    #ifdef __EMSCRIPTEN__
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::wcout << L"SDL2 could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // sdl could not initialize
    }
    #else
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::wcout << L"SDL2 could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // sdl could not initialize
    }
    #endif

    Engine::pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (Engine::pWindow == nullptr) {
        std::wcout << L"Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // window could not create
    }
    std::wcout << L"width = " << width << L", height = " << height << std::endl;
    Engine::width = width;
    Engine::height = height;
    // if the window creation succeeded create our renderer
    Engine::pRenderer = SDL_CreateRenderer(Engine::pWindow, -1, 0);
    if (Engine::pRenderer == nullptr) {
        std::wcout << L"Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // renderer could not initialize
    }
    std::wcout << L"renderer creation success" << std::endl;
    Engine::bRunning = true;
    return true;
}

void Engine::render() {

    SDL_SetRenderDrawColor(Engine::pRenderer, 0, 0, 0, 255);

    SDL_RenderClear(Engine::pRenderer); // clear the renderer to the draw color

    //renderNet();

    //calcField();

    renderField();

    //copyField();

    SDL_RenderPresent(Engine::pRenderer); // draw to the screen
}

void Engine::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: // Close button
                std::wcout << L"quit" << std::endl;
                Engine::bRunning = false;
                break;
            case SDL_KEYDOWN: // Press any key
                std::wcout << L"KEY DOWN" << std::endl;
                if (event.key.keysym.sym == SDLK_ESCAPE) { // press ESC
                    Engine::bRunning = false;
                    break;
                }
            case SDL_MOUSEMOTION: {
                if (event.button.button != SDL_BUTTON_LEFT) { break; }

                int x = event.motion.x, y = event.motion.y;
                std::wcout << L"Mouse coords [" << x << L", " << y << L"] == CELL [" << x / Engine::wCell << L", " << y / Engine::hCell << L"]" << std::endl;
//                int xIndex = x / Engine::wCell, yIndex = y / Engine::hCell;
//                Engine::userField[xIndex][yIndex].setStatus(Status::ALIVE);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button != SDL_BUTTON_LEFT) { break; }

                std::wcout << L"MOUSE DOWN" << std::endl;
                int x, y;
                SDL_GetMouseState( &x, &y );
                std::wcout << L"Mouse coords [" << x << L", " << y << L"] == CELL [" << x / Engine::wCell << L", " << y / Engine::hCell << L"]" << std::endl;
//                int xIndex = x / Engine::wCell, yIndex = y / Engine::hCell;
//                Engine::userField[xIndex][yIndex].setStatus(Status::ALIVE);
                break;
            }
            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_LEFT) { break; }
                std::wcout << L"MOUSE UP" << std::endl;
                break;
        }
    }
}

void Engine::update() {
    currentFrame = int(((SDL_GetTicks() / 100) % 6));
    // Update the surface
    SDL_UpdateWindowSurface(Engine::pWindow);
}

void Engine::clean() {
    if (Engine::prevField != nullptr) {
        for (size_t i = 0; i < Engine::width / Engine::wCell; i++) {
            delete [] Engine::prevField[i];
        }
        delete [] Engine::prevField;
    }

    if (Engine::currField != nullptr) {
        for (size_t i = 0; i < Engine::width / Engine::wCell; i++) {
            delete [] Engine::currField[i];
        }
        delete [] Engine::currField;
    }

    std::wcout << L"Cleaning game" << std::endl;
    // Destroy window
    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    // Quit SDL subsystems
    SDL_Quit();
}

bool Engine::isRunning() { return Engine::bRunning; }

SDL_Renderer * Engine::getRender() {
    return this->pRenderer;
}

void Engine::renderNet() {
    SDL_SetRenderDrawColor(Engine::pRenderer, Engine::BACKGROUND_COLOR.r, Engine::BACKGROUND_COLOR.g, Engine::BACKGROUND_COLOR.b, Engine::BACKGROUND_COLOR.a);

    for (size_t i = 0; i <= Engine::width; i += Engine::wCell) {
        SDL_RenderDrawLine(Engine::pRenderer, i, 0, i, Engine::height - 1);
        SDL_RenderDrawLine(Engine::pRenderer, i + wCell - 1, 0, i + wCell - 1, Engine::height - 1);
    }
    for (size_t j = 0; j < Engine::height; j += Engine::hCell) {
        SDL_RenderDrawLine(Engine::pRenderer, 0, j, Engine::width - 1, j);
        SDL_RenderDrawLine(Engine::pRenderer, 0, j + hCell - 1, Engine::width - 1, j + hCell - 1);
    }
}

void Engine::renderField() {
    int count = 0;

    for (size_t i = 0; i < Engine::width / Engine::wCell; i++) {
        for (size_t j = 0; j < Engine::height / Engine::hCell; j++) {
            if (Engine::currField[i][j].getHomeStatus() != HomeStatus::EMPTY) {
                count++;
            }
        }
    }
    std::wcout << L"Count not an empty house  == " << count << std::endl;

    SDL_Rect * rects = new SDL_Rect[count];
    count = 0;
    for (size_t i = 0; i < Engine::width / Engine::wCell; i++) {
        for (size_t j = 0; j < Engine::height / Engine::hCell; j++) {
            if (Engine::currField[i][j].getHomeStatus() == HomeStatus::COMMUNITY_1) {
                rects[count].x = i * Engine::wCell + 1;
                rects[count].y = j * Engine::hCell + 1;
                rects[count].w = Engine::wCell - 2;
                rects[count].h = Engine::hCell - 2;
                
                SDL_Color color = Engine::currField[i][j].getColor();
                SDL_SetRenderDrawColor(Engine::pRenderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(Engine::pRenderer, &rects[count]);
                count++;
            }
        }
    }
    //SDL_RenderFillRects(Engine::pRenderer, rects, count);
    delete[] rects;
}

/*
 *  |-|---------|-|
 *  |1|    2    |3|
 *  |-|---------|-|
 *  | |         | |
 *  |4|    5    |6|
 *  | |         | |
 *  |-|---------|-|
 *  |7|    8    |9|
 *  |-|---------|-|
 */
void Engine::calcField() {

}

void Engine::copyField() {
    for (unsigned int i = 0; i < Engine::width / Engine::wCell; i++) {
        for (unsigned int j = 0; j < Engine::height / Engine::hCell; j++) {
            Engine::prevField[i][j].setHomeStatus(Engine::currField[i][j].getHomeStatus());
            Engine::prevField[i][j].setMoodStatus(Engine::currField[i][j].getMoodStatus());
        }
    }
}

void Engine::countStatistic() {
    size_t moodHappyCount = 0;

    for (size_t i = 0; i < Engine::width / Engine::wCell; i++) {
        for (size_t j = 0; j < Engine::height / Engine::hCell; j++) {
            if (Engine::currField[i][j].getMoodStatus() == MoodStatus::HAPPY) {
                moodHappyCount++;
            }
        }
    }
    std::wcout << L"Count HAPPY status == " << moodHappyCount << std::endl;
}