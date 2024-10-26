#include "client_parseador.h"

#define CERO 0
#define UNO 1
#define TRES 3
#define BORDE_FINO_SPRITESHEET 1
#define BORDE_GRUESO_SPRITESHEET 10
#define TIRA_COMPLETA_SPRITES 6
#define MEDIA_TIRA_SPRITES 3
#define TIRA_COMPLETA_CAJAS 4
#define TAMANIO_SPRITE_GRANDE 32
#define TAMANIO_SPRITE_MEDIANO 16
#define TAMANIO_SPRITE_CHICO 8
#define INICIO_PATO_QUACK_X 194
#define INICIO_AK_47_Y 19
#define INICIO_CAJA_X 183
#define INICIO_CAJA_Y 20
#define INICIO_ARMADURA_X 387
#define INICIO_ARMADURA_Y 13

using namespace SDL2pp;

Parseador::Parseador() {}

void Parseador::iterador_de_parseo(std::vector<SDL_Rect>& sprites, int cantidad_sprites, int x,
                                   int y, int tamanio_sprite) {
    for (int i = CERO; i < cantidad_sprites; ++i) {
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
    xInicial = INICIO_PATO_QUACK_X;
    yInicial = BORDE_GRUESO_SPRITESHEET;
    iterador_de_parseo(spritesPato, TIRA_COMPLETA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesPato, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesPato, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);

    return spritesPato;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_ak() {
    std::vector<SDL_Rect> spritesAK;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    int xInicial = BORDE_FINO_SPRITESHEET;
    int yInicial = INICIO_AK_47_Y;
    iterador_de_parseo(spritesAK, UNO, xInicial, yInicial, tamanio_sprite);

    return spritesAK;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_caja() {
    std::vector<SDL_Rect> spritesCaja;
    int tamanio_sprite = TAMANIO_SPRITE_MEDIANO;

    int xInicial = INICIO_CAJA_X;
    int yInicial = INICIO_CAJA_Y;
    iterador_de_parseo(spritesCaja, TIRA_COMPLETA_CAJAS, xInicial, yInicial, tamanio_sprite);

    return spritesCaja;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_armadura() {
    std::vector<SDL_Rect> spritesArmadura;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;
    int xInicial = INICIO_ARMADURA_X;
    int yInicial = INICIO_ARMADURA_Y;

    // Correccion porque el 'sprite' de la tira esta mal en relacion a la posicion del Pato.
    iterador_de_parseo(spritesArmadura, UNO, xInicial + (TAMANIO_SPRITE_GRANDE * TRES), yInicial,
                       tamanio_sprite);

    iterador_de_parseo(spritesArmadura, TIRA_COMPLETA_SPRITES - UNO,
                       xInicial + TAMANIO_SPRITE_GRANDE, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesArmadura, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);
    yInicial += tamanio_sprite;
    iterador_de_parseo(spritesArmadura, MEDIA_TIRA_SPRITES, xInicial, yInicial, tamanio_sprite);

    return spritesArmadura;
}
