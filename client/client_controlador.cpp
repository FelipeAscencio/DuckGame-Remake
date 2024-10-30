#include "client_controlador.h"

using namespace SDL2pp;

Controlador::Controlador() {}

void Controlador::manejar_eventos(bool& jugador_activo, int& estado) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
        } else if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_d) {
                std::cout << "D" << std::endl;
                estado = 1;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_a) {
                estado = 2;
                std::cout << "A" << std::endl;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_s) {
                estado = 3;
                std::cout << "S" << std::endl;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_w) {
                estado = 4;
                std::cout << "W" << std::endl;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_SPACE) {
                estado = 5;
                std::cout << "SPACE" << std::endl;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_j){
                estado = 6;
                std::cout << "J" << std::endl;
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_k){
                estado = 7;
                std::cout << "K" << std::endl;
            }
        }
    }
}
