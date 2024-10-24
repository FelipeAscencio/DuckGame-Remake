#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#define EXITO 0
#define FALLA 1
#define MENOS_UNO -1
#define WIDTH_MIN 640
#define HEIGHT_MIN 480
#define DUCK_GAME_STR "Duck Game"

using namespace SDL2pp;

int main() try {
    SDL sdl(SDL_INIT_VIDEO);
    Window window(DUCK_GAME_STR, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH_MIN,
                  HEIGHT_MIN, SDL_WINDOW_RESIZABLE);
    Renderer renderer(window, MENOS_UNO, SDL_RENDERER_ACCELERATED);
    Texture mapa(renderer, DATA_PATH "/mapa1.png");
    bool running = true;
    SDL_Event sdlEvent;
    while (running) {
        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.Clear();
        renderer.Copy(mapa);
        renderer.Present();
    }

    return EXITO;
} catch (std::exception& error) {
    std::cerr << error.what() << std::endl;
    return FALLA;
}
