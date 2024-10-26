#include "client_parseador.h"

#define TAMANIO_SPRITE 32

using namespace SDL2pp;

Parseador::Parseador() {}

std::vector<SDL_Rect> Parseador::obtener_sprites_pato() {
    int xInicial = 1;
    int yInicial = 10;
    std::vector<SDL_Rect> spritesPato;
    for (int i = 0; i < 6; ++i) {
        SDL_Rect rect;
        rect.x = xInicial + i * TAMANIO_SPRITE;
        rect.y = yInicial;
        rect.w = TAMANIO_SPRITE;
        rect.h = TAMANIO_SPRITE;
        spritesPato.push_back(rect);
    }
    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect;
        rect.x = xInicial + i * TAMANIO_SPRITE;
        rect.y = yInicial + TAMANIO_SPRITE;
        rect.w = TAMANIO_SPRITE;
        rect.h = TAMANIO_SPRITE;
        spritesPato.push_back(rect);
    }
    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect;
        rect.x = xInicial + i * TAMANIO_SPRITE;
        rect.y = yInicial + 2 * TAMANIO_SPRITE;
        rect.w = TAMANIO_SPRITE;
        rect.h = TAMANIO_SPRITE;
        spritesPato.push_back(rect);
    }

    xInicial = 194;
    yInicial = 10;
    for (int i = 0; i < 6; ++i) {
        SDL_Rect rect;
        rect.x = xInicial + i * TAMANIO_SPRITE;
        rect.y = yInicial;
        rect.w = TAMANIO_SPRITE;
        rect.h = TAMANIO_SPRITE;
        spritesPato.push_back(rect);
    }
    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect;
        rect.x = xInicial + i * TAMANIO_SPRITE;
        rect.y = yInicial + TAMANIO_SPRITE;
        rect.w = TAMANIO_SPRITE;
        rect.h = TAMANIO_SPRITE;
        spritesPato.push_back(rect);
    }
    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect;
        rect.x = xInicial + i * TAMANIO_SPRITE;
        rect.y = yInicial + 2 * TAMANIO_SPRITE;
        rect.w = TAMANIO_SPRITE;
        rect.h = TAMANIO_SPRITE;
        spritesPato.push_back(rect);
    }
    

    return spritesPato;
}
