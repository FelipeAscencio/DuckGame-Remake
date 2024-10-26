#include "client_parseador.h"

#define CERO 0
#define BORDE_FINO_SPRITESHEET 1
#define BORDE_GRUESO_SPRITESHEET 10
#define TIRA_COMPLETA_SPRITES 6
#define MEDIA_TIRA_SPRITES 3
#define TAMANIO_SPRITE_GRANDE 32
#define INICIO_PATO_QUACK 194

using namespace SDL2pp;

Parseador::Parseador() {}

void Parseador::iterador_de_parseo(std::vector<SDL_Rect>& sprites, int cantidad_sprites, int x, int y, int tamanio_sprite){
    for (int i = CERO; i < cantidad_sprites; ++i){
        SDL_Rect rect;
        rect.x = x + i * tamanio_sprite;
        rect.y = y;
        rect.w = tamanio_sprite;
        rect.h = tamanio_sprite;
        sprites.push_back(rect);
    }
}

std::vector<SDL_Rect> Parseador::obtener_sprites_pato() {
    std::vector<SDL_Rect> spritesPato;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;
    
    // Parseo de los sprites del pato base.
    int xInicial = BORDE_FINO_SPRITESHEET;
    int yInicial = BORDE_GRUESO_SPRITESHEET;
    iterador_de_parseo(spritesPato, TIRA_COMPLETA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesPato, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesPato, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);

    // Parseo de los sprites del pato haciendo 'quack'.
    xInicial = INICIO_PATO_QUACK;
    yInicial = BORDE_GRUESO_SPRITESHEET;
    iterador_de_parseo(spritesPato, TIRA_COMPLETA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesPato, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesPato, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);  

    return spritesPato;
}
