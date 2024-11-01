#include "client_controlador.h"

using namespace SDL2pp;

Controlador::Controlador(Queue<char>& queue_enviador) : queue(queue_enviador) {}

void Controlador::manejar_eventos(bool& jugador_activo) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
        } else if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_d) {
                std::cout << "D" << std::endl;
                queue.try_push('D');
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_a) {
                std::cout << "A" << std::endl;
                queue.try_push('A');
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_s) {
                std::cout << "S" << std::endl;
                queue.try_push('S');
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_w) {
                std::cout << "W" << std::endl;
                queue.try_push('W');
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_SPACE) {
                std::cout << "SPACE" << std::endl;
                queue.try_push(' ');
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_j){
                std::cout << "J" << std::endl;
                queue.try_push('C');
            } else if (sdlEvent.key.keysym.sym ==
                       SDLK_k){
                std::cout << "K" << std::endl;
            }
        }
    }
}
