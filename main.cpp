//
// Created by alex on 15.09.2023.
//

#include <locale>
#include <cstdlib>
#include "engine/engine.h"
#include <SDL2/SDL.h>


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

const int WIDTH = 640;
const int HEIGHT = 480;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

#ifdef __EMSCRIPTEN__
void mainLoopEmcc(void *arg) {
    if (!arg) {
        std::wcout << L"engine not init!" << std::endl;
        emscripten_cancel_main_loop();
    }

    std::unique_ptr<Engine> pEngine((Engine *) arg);
    if (!pEngine->isRunning()) {
        std::wcout << L"engine not running!" << std::endl;
        pEngine->clean();
        emscripten_cancel_main_loop();
        return;
    }

    pEngine->handleEvents();
    pEngine->update();
    pEngine->render();

    pEngine.release();
}
#endif

int main1(int argc, char* argv[]) {
    unsigned int frameStart, frameTime;
    auto pEngine = std::make_unique<Engine>();

    pEngine->init(L"Shelling's model", WIDTH, HEIGHT); // 50 * 80 = 4000 cell

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(mainLoopEmcc, pEngine.release(), FPS, 1);
    #else
    while(pEngine->isRunning()) {
        frameStart = SDL_GetTicks();

        pEngine->handleEvents();
        //pEngine->update();
        pEngine->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) {
            SDL_Delay((int) (DELAY_TIME - frameTime));
        }
    }
    pEngine->clean();
    #endif

    return 0;
}

int main(int argc, char* argv[]) {
    unsigned int frameStart, frameTime;
    auto pEngine = std::make_unique<Engine>();

    pEngine->init(L"Shelling's model", WIDTH, HEIGHT); // 50 * 80 = 4000 cell

    SDL_SetRenderDrawColor(pEngine->getRender(), 0, 0, 0, 255);
    SDL_RenderClear(pEngine->getRender());
    SDL_RenderPresent(pEngine->getRender());
    SDL_Delay(5000);
    SDL_Quit();

    return 0;
}