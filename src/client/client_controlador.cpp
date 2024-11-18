#include "client_controlador.h"

#define COMANDO_EXIT 'X'
#define COMANDO_DERECHA 'D'
#define COMANDO_IZQUIERDA 'A'
#define COMANDO_AGACHAR 'S'
#define COMANDO_MIRAR_ARRIBA 'W'
#define COMANDO_SALTAR ' '
#define COMANDO_DISPARAR 'J'
#define COMANDO_AGARRAR 'K'
#define COMANDO_CUACK 'C'
#define COMANDO_CHEAT_AK '1'
#define COMANDO_CHEAT_SHOTGUN '2'
#define COMANDO_CHEAT_MAGNUM '3'
#define COMANDO_CHEAT_LASER '4'
#define COMANDO_CHEAT_SNIPER '5'
#define COMANDO_CHEAT_INMORTALIDAD 'I'
#define COMANDO_CHEAT_ARMADURA 'L'
#define COMANDO_CHEAT_CASCO 'P'
#define COMANDO_CHEAT_RECARGAR 'R'

using namespace SDL2pp;

Controlador::Controlador(Queue<char>& cola_enviador): cola_eventos(cola_enviador) {}

void Controlador::manejar_eventos(bool& jugador_activo) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            jugador_activo = false;
            cola_eventos.try_push(COMANDO_EXIT);
        } else if (sdlEvent.type == SDL_KEYDOWN) {
            if (sdlEvent.key.keysym.sym == SDLK_d) {
                cola_eventos.try_push(COMANDO_DERECHA);
            } else if (sdlEvent.key.keysym.sym == SDLK_a) {
                cola_eventos.try_push(COMANDO_IZQUIERDA);
            } else if (sdlEvent.key.keysym.sym == SDLK_s) {
                cola_eventos.try_push(COMANDO_AGACHAR);
            } else if (sdlEvent.key.keysym.sym == SDLK_w) {
                cola_eventos.try_push(COMANDO_MIRAR_ARRIBA);
            } else if (sdlEvent.key.keysym.sym == SDLK_SPACE) {
                cola_eventos.try_push(COMANDO_SALTAR);
            } else if (sdlEvent.key.keysym.sym == SDLK_j) {
                cola_eventos.try_push(COMANDO_DISPARAR);
            } else if (sdlEvent.key.keysym.sym == SDLK_k) {
                cola_eventos.try_push(COMANDO_AGARRAR);
            } else if (sdlEvent.key.keysym.sym == SDLK_r) {
                cola_eventos.try_push(COMANDO_CHEAT_RECARGAR);
            } else if (sdlEvent.key.keysym.sym == SDLK_l) {
                cola_eventos.try_push(COMANDO_CHEAT_ARMADURA);
            } else if (sdlEvent.key.keysym.sym == SDLK_c) {
                cola_eventos.try_push(COMANDO_CUACK);
            } else if (sdlEvent.key.keysym.sym == SDLK_p) {
                cola_eventos.try_push(COMANDO_CHEAT_CASCO);
            } else if (sdlEvent.key.keysym.sym == SDLK_i) {
                cola_eventos.try_push(COMANDO_CHEAT_INMORTALIDAD);
            } else if (sdlEvent.key.keysym.sym == SDLK_1) {
                cola_eventos.try_push(COMANDO_CHEAT_AK);
            } else if (sdlEvent.key.keysym.sym == SDLK_2) {
                cola_eventos.try_push(COMANDO_CHEAT_SHOTGUN);
            } else if (sdlEvent.key.keysym.sym == SDLK_3) {
                cola_eventos.try_push(COMANDO_CHEAT_MAGNUM);
            // CHEATS PARA LAS ARMAS QUE FALTAN POR IMPLEMENTAR.
            //} else if (sdlEvent.key.keysym.sym == SDLK_4) {
            //    cola_eventos.try_push(COMANDO_CHEAT_LASER);
            //} else if (sdlEvent.key.keysym.sym == SDLK_5) {
            //    cola_eventos.try_push(COMANDO_CHEAT_SNIPER);
            }
        }
    }
}
